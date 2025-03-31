#include "nav2_window.h"
#include "nav2_window.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>

//#include "./ui_nav2_window.h"

//nav2_window::nav2_window(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::nav2_window)
//{
//    ui->setupUi(this);
//}



Nav2Window::Nav2Window(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Key", "Value"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *loadButton = new QPushButton("Load YAML", this);
    QPushButton *saveButton = new QPushButton("Save YAML", this);

    layout->addWidget(table);
    layout->addWidget(loadButton);
    layout->addWidget(saveButton);

    yamlHandler = new YamlHandler("/home/mr_robot/Desktop/blabla.yaml");

    connect(loadButton, &QPushButton::clicked, this, &Nav2Window::loadYaml);
    connect(saveButton, &QPushButton::clicked, this, &Nav2Window::saveYaml);
}

void Nav2Window::loadYaml() {
    table->setRowCount(0);
    QMap<QString, QVariant> data = yamlHandler->loadYaml();
    int row = 0;
    for (auto it = data.begin(); it != data.end(); ++it, ++row) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(it.key()));
        table->setItem(row, 1, new QTableWidgetItem(it.value().toString()));
    }
}

void Nav2Window::saveYaml() {
    QMap<QString, QVariant> data;
    for (int row = 0; row < table->rowCount(); ++row) {
        QString key = table->item(row, 0)->text();
        QString value = table->item(row, 1)->text();
        data[key] = value;
    }
    yamlHandler->saveYaml(data);
}

Nav2Window::~Nav2Window()
{
    //delete ui;
}
