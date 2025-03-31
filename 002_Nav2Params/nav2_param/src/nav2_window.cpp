#include "nav2_window.h"
#include <QPushButton>
#include <QMessageBox>

Nav2Window::Nav2Window(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Scrollable area for buttons
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollWidget = new QWidget(this);
    nodeButtonLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(nodeButtonLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    paramTreeWidget = new QTreeWidget(this);
    paramTreeWidget->setColumnCount(2);
    paramTreeWidget->setHeaderLabels({"Key", "Value"});

    QPushButton *loadButton = new QPushButton("Load YAML", this);
    QPushButton *saveButton = new QPushButton("Save YAML", this);

    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(paramTreeWidget);
    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(saveButton);

    yamlHandler = new YamlHandler("/home/mr_robot/Desktop/nav2_params.yaml");

    connect(loadButton, &QPushButton::clicked, this, &Nav2Window::loadYaml);
    connect(saveButton, &QPushButton::clicked, this, &Nav2Window::saveYaml);
    connect(paramTreeWidget, &QTreeWidget::itemChanged, this, &Nav2Window::validateData);
}

void Nav2Window::loadYaml() {
    // Clear UI elements
    paramTreeWidget->clear();
    while (QLayoutItem *item = nodeButtonLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Load YAML data
    YAML::Node rootNode = yamlHandler->loadYaml();
    yamlData.clear();

    // Create buttons for each node
    for (const auto &it : rootNode) {
        QString nodeName = QString::fromStdString(it.first.as<std::string>());
        yamlData[nodeName] = it.second;

        QPushButton *nodeButton = new QPushButton(nodeName, this);
        nodeButtonLayout->addWidget(nodeButton);

        connect(nodeButton, &QPushButton::clicked, this, [this, nodeName]() {
            showNodeParams(nodeName);
        });
    }
}

void Nav2Window::showNodeParams(const QString &nodeName) {
    currentNode = nodeName;
    paramTreeWidget->clear();

    YAML::Node node = yamlData[nodeName];

    // key to skip
    static const QSet<QString> keysToSkip = {
        "ros__parameters", "local_costmap", "global_costmap", "qos",
        "GridBased", "simple_smoother", "spin", "backup", "wait",
        "assistant_teleop", "wait_at_waypoint", "PolygonStop", "PolygonSlow",
        "FootprintApproach", "scan", "pointcloud", "drive_on_heading", "assisted_teleop",
        "navigate_to_pose", "navigate_through_poses", "plugin_lib_names", "progress_checker",
        "general_goal_checker", "FollowPath", "obstacle_layer", "static_layer", "inflation_layer",
        "voxel_layer", "static_layer", "simple_smoother", "wait_at_waypoint"
    };

    for (const auto &it : node) 
    {
        QString key = QString::fromStdString(it.first.as<std::string>());
        QString value;
        if (keysToSkip.contains(key)) 
        {
            // Skip this key
            continue;
        } 
        else if (it.second.IsScalar()) 
        {
            value = QString::fromStdString(it.second.as<std::string>());
        } 
        else if (it.second.IsSequence()) 
        {
            value = "[";
            for (const auto &seqItem : it.second) 
            {
                value += QString::fromStdString(seqItem.as<std::string>()) + ", ";
            }
            value.chop(2); // Remove last comma and space
            value += "]";
        } 
        else if (it.second.IsMap()) 
        {
            value = "{";
            for (const auto &mapItem : it.second) 
            {
                value += QString::fromStdString(mapItem.first.as<std::string>()) + ": " +
                         QString::fromStdString(mapItem.second.as<std::string>()) + ", ";
            }
            value.chop(2); // Remove last comma and space
            value += "}";
        }
        else 
        {
            value = "Unsupported type";
        }
        QTreeWidgetItem *item = new QTreeWidgetItem(paramTreeWidget);
        item->setText(0, key);
        item->setText(1, value);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void Nav2Window::saveYaml() {
    if (currentNode.isEmpty()) return;

    YAML::Node updatedNode = buildYaml(currentNode);
    yamlData[currentNode] = updatedNode;

    YAML::Node finalYaml;
    for (auto it = yamlData.begin(); it != yamlData.end(); ++it) {
        finalYaml[it.key().toStdString()] = it.value();
    }

    yamlHandler->saveYaml(finalYaml);
}

YAML::Node Nav2Window::buildYaml(const QString &nodeName) {
    YAML::Node node;
    for (int i = 0; i < paramTreeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = paramTreeWidget->topLevelItem(i);
        QString key = item->text(0);
        QString value = item->text(1);
        node[key.toStdString()] = value.toStdString();
    }
    return node;
}

void Nav2Window::validateData(QTreeWidgetItem *item, int column) {
    if (column != 1) return;

    QString value = item->text(1);
    if (value.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Value cannot be empty!");
        item->setText(1, "0");
    }
}

void Nav2Window::parseYaml(const YAML::Node &node, const QString &parentKey) {
    static const QSet<QString> keysToSkip = {
        "ros__parameters", "local_costmap", "global_costmap", "qos",
        "GridBased", "simple_smoother", "spin", "backup", "wait",
        "assistant_teleop", "wait_at_waypoint", "PolygonStop", "PolygonSlow",
        "FootprintApproach", "scan", "pointcloud"
    };

    for (const auto &it : node) {
        QString key = QString::fromStdString(it.first.as<std::string>());
        
        if (keysToSkip.contains(key)) {
            // Dive into subkeys instead of treating this as a node
            parseYaml(it.second, parentKey);
        } else {
            QString nodeName = parentKey.isEmpty() ? key : parentKey + "/" + key;
            yamlData[nodeName] = it.second;

            QPushButton *nodeButton = new QPushButton(nodeName, this);
            nodeButtonLayout->addWidget(nodeButton);

            connect(nodeButton, &QPushButton::clicked, this, [this, nodeName]() {
                showNodeParams(nodeName);
            });
        }
    }
}

Nav2Window::~Nav2Window()
{
    //delete ui;
}