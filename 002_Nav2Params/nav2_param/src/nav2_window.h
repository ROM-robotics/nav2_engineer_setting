#ifndef NAV2_WINDOW_H
#define NAV2_WINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "yaml_handler.h"

#include <QTreeWidget>
#include <QVBoxLayout>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class Nav2Window; }
QT_END_NAMESPACE

class Nav2Window : public QMainWindow {
    Q_OBJECT
public:
    explicit Nav2Window(QWidget *parent = nullptr);
    ~Nav2Window();
private slots:
    void loadYaml();
    void saveYaml();
    void showNodeParams(const QString &nodeName);
    void validateData(QTreeWidgetItem *item, int column);

private:
    void parseYaml(const YAML::Node &node, const QString &parentKey);
    YAML::Node buildYaml(const QString &nodeName);

    QWidget *nodeButtonContainer;
    QVBoxLayout *nodeButtonLayout;
    QTreeWidget *paramTreeWidget;
    QMap<QString, YAML::Node> yamlData;
    YamlHandler *yamlHandler;
    QString currentNode;

    QTableWidget *table;
    //Ui::Nav2Window *ui;
};

#endif // NAV2_WINDOW_H

