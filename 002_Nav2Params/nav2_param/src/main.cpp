#include "nav2_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Nav2MainWindow w;
    w.show();

    return app.exec();
}
