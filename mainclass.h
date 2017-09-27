#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include "mainwindow.h"
#include "finder.h"

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass();
    ~MainClass();

private:
    Keeper *keeper;
    MainWindow *mainWindow;
    CreatorRec *creatorRec;
    Finder *finder;
};

#endif // MAINCLASS_H
