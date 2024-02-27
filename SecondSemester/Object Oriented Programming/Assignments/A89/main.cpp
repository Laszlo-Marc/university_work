#include "QtWidgetsApplicationFor89.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplicationFor89 w;
    w.show();
    return a.exec();
}
