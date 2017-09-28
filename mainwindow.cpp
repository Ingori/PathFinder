#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("PathFinder");

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    /**/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refresh_clicked()
{

}

void MainWindow::on_pathFinder_clicked()
{

}



QRectF Rect::boundingRect() const
{
//    qreal penWidth = 1;
//    return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
//                  diameter + penWidth, diameter + penWidth);
    return QRectF(rec);
}

void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawRoundedRect(rec, 0, 0);
}
