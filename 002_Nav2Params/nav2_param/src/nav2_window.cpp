#include "nav2_window.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextCursor>
#include <QDockWidget>

Nav2MainWindow::Nav2MainWindow(QWidget *parent)
    : QMainWindow(parent), textEdit(new QTextEdit(this)), searchDockWidget(new QDockWidget(this))
{
    setCentralWidget(textEdit);

    createActions();
    createMenu();
    createSearchReplaceUI();
}

Nav2MainWindow::~Nav2MainWindow() {}

void Nav2MainWindow::createActions()
{
    openAction = new QAction("Open", this);
    connect(openAction, &QAction::triggered, this, &Nav2MainWindow::openFile);

    saveAction = new QAction("Save", this);
    connect(saveAction, &QAction::triggered, this, &Nav2MainWindow::saveFile);

    newAction = new QAction("New", this);
    connect(newAction, &QAction::triggered, this, &Nav2MainWindow::newFile);

    searchAction = new QAction("Search", this);
    connect(searchAction, &QAction::triggered, this, &Nav2MainWindow::searchText);

    replaceAction = new QAction("Replace", this);
    connect(replaceAction, &QAction::triggered, this, &Nav2MainWindow::replaceText);

    searchNextAction = new QAction("Search Next", this);
    connect(searchNextAction, &QAction::triggered, this, &Nav2MainWindow::searchNext);

    replaceNextAction = new QAction("Replace Next", this);
    connect(replaceNextAction, &QAction::triggered, this, &Nav2MainWindow::replaceNext);

    searchPreviousAction = new QAction("Search Previous", this);
    connect(searchPreviousAction, &QAction::triggered, this, &Nav2MainWindow::searchPrevious);

    // Shortcuts for search and replace
    searchAction->setShortcut(QKeySequence("Ctrl+F"));
    replaceAction->setShortcut(QKeySequence("Ctrl+R"));
    searchNextAction->setShortcut(QKeySequence("F3"));
    replaceNextAction->setShortcut(QKeySequence("Ctrl+Shift+R"));
}

void Nav2MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    QMenu *editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(searchAction);
    editMenu->addAction(replaceAction);
    editMenu->addAction(searchNextAction);
    editMenu->addAction(replaceNextAction);
    editMenu->addAction(searchPreviousAction);
}

void Nav2MainWindow::createSearchReplaceUI()
{
    // Create search and replace inputs in the dock widget
    QWidget *searchWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(searchWidget);
    searchLineEdit = new QLineEdit(this);
    replaceLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Search"));
    layout->addWidget(searchLineEdit);
    layout->addWidget(new QLabel("Replace"));
    layout->addWidget(replaceLineEdit);

    searchDockWidget->setWidget(searchWidget);
    searchDockWidget->setWindowTitle("Search/Replace");

    // Initially hide the dock widget
    searchDockWidget->hide();
    addDockWidget(Qt::TopDockWidgetArea, searchDockWidget);  // Dock it at the top of the window
}

void Nav2MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Could not open file");
        }
    }
}

void Nav2MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Could not save file");
        }
    }
}

void Nav2MainWindow::newFile()
{
    textEdit->clear();
}

void Nav2MainWindow::searchText()
{
    // Show the dock widget for search and replace
    searchDockWidget->show();
}

void Nav2MainWindow::replaceText()
{
    // Show the dock widget for replace
    searchDockWidget->show();
}

void Nav2MainWindow::searchNext()
{
    // Implement search next functionality here
}

void Nav2MainWindow::replaceNext()
{
    // Implement replace next functionality here
}

void Nav2MainWindow::searchPrevious()
{
    // Implement search previous functionality here
}

void Nav2MainWindow::highlightSearchResults(const QString &searchTerm)
{
    // Implement highlight functionality here
}
