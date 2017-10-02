#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PathFinder");

    graph = new Graph();

    scene = new GraphicsScene(graph, this);
    ui->graphicsView->setScene(scene);

    connect(scene, &GraphicsScene::changeSizeField, graph, &Graph::setSizeField);
    connect(scene, &GraphicsScene::changeCountBlocks, graph, &Graph::setCountBlocks);
    connect(scene, &GraphicsScene::changeStartEnd, graph, &Graph::setStartEnd);
    connect(graph, &Graph::dataChanged, scene, &GraphicsScene::updateData);
}

MainWindow::~MainWindow()
{
    delete ui;
    /**/
}

void MainWindow::on_refresh_clicked()
{
    scene->setSizeSceneBlock(QSize(ui->widthScreen->value(), ui->heightScreen->value()),
                        QSize(ui->sizeEl->value(), ui->sizeEl->value()));
    scene->setCountBlocks(ui->countEl->value());
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
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRoundedRect(rec, 0, 0);
}



GraphicsScene::GraphicsScene(const Graph *graph, QObject *parent) :
    QGraphicsScene(parent), graph_(graph)
{
    start_ = QPoint(-1, -1);
    end_ = QPoint(-1, -1);
}

bool GraphicsScene::setSizeSceneBlock(const QSize &sizeScene, const QSize &sizeBlock)
{
    /**/
    sizeS = sizeScene;
    sizeB = sizeBlock;
    sizeField = QSize(sizeScene.width()/sizeBlock.width(), sizeScene.height()/sizeBlock.height());
    emit changeSizeField(sizeField);
}

bool GraphicsScene::setCountBlocks(int count)
{
    /**/
    countBlocks = count;
    emit changeCountBlocks(countBlocks);
}

void GraphicsScene::updateData()
{
    int left, top, width, height;
    left = top = 0;
    width = sizeB.width();
    height = sizeB.height();
    sizeField = graph_->size();

    for(int i = 0; i < sizeField.height(); i++)
    {
        for(int j = 0; j < sizeField.width(); j++)
        {
            if(graph_->status(QPoint(j, i)) != free_)
                addItem(new Rect(QRect(left, top, width, height)));
            left += width;
        }
        left = 0;
        top += height;
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pointF(event->scenePos());

    int x = pointF.x()/sizeB.width();
    int y = pointF.y()/sizeB.height();

//    emit clicked(QPoint(x, y));
    qDebug()<<x<<y;
}
