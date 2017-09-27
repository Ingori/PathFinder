#include "mainclass.h"

MainClass::MainClass()
{
    //хранит текущее состояние(расположение препятствий и маршрут)
    keeper = new Keeper(this);

    //пользовательский интерфейс
    mainWindow = new MainWindow(keeper);

    //генератор препятствий
    creatorRec = new CreatorRec(keeper, this);

    //поисковик
    finder = new Finder(keeper, this);

    //отобразить пользовательский интерфейс
    mainWindow->show();
}

MainClass::~MainClass()
{
//    delete keeper;
//    delete creatorRec;
//    delete finder;
}
