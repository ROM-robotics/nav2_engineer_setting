#include "yaml_handler.h"
#include <QFile>
#include <QDebug>
#include <fstream>

YamlHandler::YamlHandler(const QString &filePath) : yamlFile(filePath) {}

YAML::Node YamlHandler::loadYaml() 
{
    try 
    {
        return YAML::LoadFile(yamlFile.toStdString());
    } catch (const YAML::Exception &e) {
        qWarning() << "Error loading YAML:" << e.what();
        return YAML::Node();
    }
}

bool YamlHandler::saveYaml(const YAML::Node &data) 
{
    try 
    {
        std::ofstream fout(yamlFile.toStdString());
        fout << data;
        return true;
    } catch (...) {
        qWarning() << "Error saving YAML";
        return false;
    }
}