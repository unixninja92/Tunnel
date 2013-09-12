#include "tunnelw.h"
#include <QApplication>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TunnelW w;
    w.show();

    return a.exec();
}

