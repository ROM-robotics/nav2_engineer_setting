#ifndef YAML_EDITOR_H
#define YAML_EDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

class YamlEditor : public QWidget {
 Q_OBJECT

public:
 explicit YamlEditor(QWidget* parent = nullptr);

private slots:
 void loadYaml();
 void saveYaml();

private:
 QTextEdit* textEdit;
 QPushButton* loadButton;
 QPushButton* saveButton;
};

#endif // YAML_EDITOR_H
