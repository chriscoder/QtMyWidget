#include "qtmovewidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMoveWidget w;
    w.show();
    return a.exec();
}
