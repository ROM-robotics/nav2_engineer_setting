#include "nav2_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nav2Window w;
    w.show();
    return a.exec();
}
