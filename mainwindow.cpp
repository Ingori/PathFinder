#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>

MainWindow::MainWindow(Keeper *keeper, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), keeper_(keeper)
{
    ui->setupUi(this);

    setWindowTitle("PathFinder");

    writeToKeeper();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    /**/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateView()
{
//все перерисовываем на основании данных из keeper
}

void MainWindow::on_refresh_clicked()
{
    writeToKeeper();
    emit refreshBlocks();
}

void MainWindow::on_pathFinder_clicked()
{
//    keeper_->setStartEndWay(start, end);
    emit refreshWay();
}

void MainWindow::writeToKeeper()
{
    keeper_->setRectField(ui->graphicsView->rect());
    keeper_->setCountBlocks(ui->countEl->value());
    keeper_->setRectBlocks(QRect(0, 0, ui->widthEl->value(), ui->highEl->value()));
}
