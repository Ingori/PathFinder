#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Keeper *keeper, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), keeper_(keeper)
{
    ui->setupUi(this);

    setWindowTitle("PathFinder");

//    ui->graphicsView->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateView()
{

}

void MainWindow::on_refresh_clicked()
{

}

void MainWindow::on_pathFinder_clicked()
{

}
