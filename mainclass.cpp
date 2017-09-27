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


    //генерируем препятствия и находи путь по сигналам из mainWindow
    connect(mainWindow, &MainWindow::refreshBlocks, creatorRec, &CreatorRec::generateBlocks);
    connect(mainWindow, &MainWindow::refreshWay,    finder,     &Finder::findWay);

    //по завершении генерации препятствий и пути обновляем интерфейс
    connect(creatorRec, &CreatorRec::endWork, mainWindow, &MainWindow::updateView);
    connect(finder,     &Finder::endWork,     mainWindow, &MainWindow::updateView);


    //отобразить пользовательский интерфейс
    mainWindow->show();
}

MainClass::~MainClass()
{
//    delete keeper;
//    delete creatorRec;
//    delete finder;
}
