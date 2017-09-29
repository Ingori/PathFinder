#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("PathFinder");

    graph = new Graph(ui->widthScreen->value(), ui->highScreen->value());

    scene = new GraphicsScene(ui->widthScreen->value(), ui->highScreen->value(), this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refresh_clicked()
{
    scene->clear();

    int width = ui->widthScreen->value();
    int height = ui->highScreen->value();
    if(graph->width() != width || graph->height() != height)
    {
        graph->setWidthHeight(width, height);
        scene->setWidthHeight(width, height);
    }

    graph->randomFillGraph(ui->countEl->value());

    fillScene();
}

void MainWindow::fillScene()
{
    int left, top, width, height;
    left = top = 0;
    width = height = ui->sizeEl->value();
    for(int i = 0; i < graph->height(); i++)
    {
        for(int j = 0; j < graph->width(); j++)
        {
            if(!graph->isFree(QPoint(j, i)))
                scene->addItem(new Rect(QRect(left, top, width, height)));
            left += width;
        }
        left = 0;
        top += height;
    }
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

//void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{

//}



bool GraphicsScene::setWidthHeight(int width, int height/*, int sizeBlock*/)
{
    width_ = width;
    height_ = height;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pointF(event->scenePos());

    int x = pointF.x()/width_;
    int y = pointF.y()/height_;

    qDebug()<<"x == "<<x<<"; y == "<<y<<";";

    emit clicked(QPoint(x, y));
}
