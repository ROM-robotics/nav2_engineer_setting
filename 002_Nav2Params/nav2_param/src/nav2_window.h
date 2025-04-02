#ifndef NAV2_WINDOW_H
#define NAV2_WINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QLineEdit>
#include <QDockWidget>

class Nav2MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Nav2MainWindow(QWidget *parent = nullptr);
    ~Nav2MainWindow();

private slots:
    void openFile();
    void saveFile();
    void newFile();
    void searchText();
    void replaceText();
    void searchNext();
    void replaceNext();
    void searchPrevious();

private:
    QTextEdit *textEdit;
    QAction *openAction;
    QAction *saveAction;
    QAction *newAction;
    QAction *searchAction;
    QAction *replaceAction;
    QAction *searchNextAction;
    QAction *replaceNextAction;
    QAction *searchPreviousAction;

    QDockWidget *searchDockWidget;  // Dock widget for search input
    QLineEdit *searchLineEdit;
    QLineEdit *replaceLineEdit;

    void createActions();
    void createMenu();
    void createSearchReplaceUI();
    void highlightSearchResults(const QString &searchTerm);
};

#endif // NAV2_WINDOW_H
