#include "mainclass.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainClass s;

    return a.exec();
}
