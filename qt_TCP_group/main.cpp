#include "serverwidget.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();
    ClientWidget w1;
    w1.show();
    ClientWidget w2;
    w2.show();
    ClientWidget w3;
    w3.show();

    return a.exec();
}
