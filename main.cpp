#include "LoaferWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoaferWidget w;
    w.showFullScreen();
    return a.exec();
}
