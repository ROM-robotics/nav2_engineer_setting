#ifndef YAMLHANDLER_H
#define YAMLHANDLER_H

#include <yaml-cpp/yaml.h>
#include <QString>
#include <QMap>
#include <QVariant>

class YamlHandler {
public:
    explicit YamlHandler(const QString &filePath);
    YAML::Node loadYaml();
    bool saveYaml(const YAML::Node &data);

private:
    QString yamlFile;
};

#endif // YAMLHANDLER_H
