#include "yamlEditor.h"
#include <QFileDialog>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <sstream>
#include <QVBoxLayout>

YamlEditor::YamlEditor(QWidget* parent)
    : QWidget(parent), textEdit(new QTextEdit(this)), loadButton(new QPushButton("Load YAML", this)),
      saveButton(new QPushButton("Save YAML", this)) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    layout->addWidget(loadButton);
    layout->addWidget(saveButton);

    connect(loadButton, &QPushButton::clicked, this, &YamlEditor::loadYaml);
    connect(saveButton, &QPushButton::clicked, this, &YamlEditor::saveYaml);
}

void YamlEditor::loadYaml() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open YAML File", "", "YAML Files (*.yaml *.yml)");
    if (!fileName.isEmpty()) {
        try {
            YAML::Node config = YAML::LoadFile(fileName.toStdString());
            std::stringstream ss;
            ss << config;
            textEdit->setText(QString::fromStdString(ss.str()));
        } catch (const YAML::Exception& e) {
            // Handle error
        }
    }
}

void YamlEditor::saveYaml() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save YAML File", "", "YAML Files (*.yaml *.yml)");
    if (!fileName.isEmpty()) {
        try {
            YAML::Node config = YAML::Load(textEdit->toPlainText().toStdString());
            YAML::Emitter out;
            out << config;
            std::ofstream file(fileName.toStdString());
            file << out.c_str();
        } catch (const YAML::Exception& e) {
            // Handle error
        }
    }
}
