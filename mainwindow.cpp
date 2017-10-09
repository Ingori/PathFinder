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

    scene = new GraphicsScene(graph);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete graph;
}

void MainWindow::on_refresh_clicked()
{
    scene->setSizeSceneBlock(QSize(ui->widthScreen->value(), ui->heightScreen->value()),
                        QSize(ui->sizeEl->value(), ui->sizeEl->value()));
    scene->setCountBlocks(ui->countEl->value());
}



QRectF Item::boundingRect() const
{
//    qreal penWidth = 1;
//    return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
//                  diameter + penWidth, diameter + penWidth);
    return QRectF(rec);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setBrush(QBrush(color_));
    painter->drawRoundedRect(rec, 0, 0);
}

//void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    emit clicked(this);
//}



GraphicsScene::GraphicsScene(Graph *graph, QObject *parent) :
    QGraphicsScene(parent), graph_(graph)
{
    connect(graph_, &Graph::dataChanged, this, &GraphicsScene::updateField);
}

bool GraphicsScene::setSizeSceneBlock(const QSize &sizeScene, const QSize &sizeBlock)
{
    /**/
    sizeS = sizeScene;
    sizeB = sizeBlock;
    sizeField = QSize(sizeScene.width()/sizeBlock.width(), sizeScene.height()/sizeBlock.height());
    graph_->setSizeField(sizeField);
}

bool GraphicsScene::setCountBlocks(int count)
{
    /**/
    countBlocks = count;
    graph_->setCountBlocks(countBlocks);
}

void GraphicsScene::updateField()
{
    clear();

    int left, top, width, height;
    left = top = 0;
    width = sizeB.width();
    height = sizeB.height();
    sizeField = graph_->size();

    for(int i = 0; i < sizeField.height(); i++)
    {
        for(int j = 0; j < sizeField.width(); j++)
        {
            if(graph_->status(QPoint(j, i)) == block)
                createItem(QRect(left, top, width, height), QColor(Qt::black));
            else if(graph_->status(QPoint(j, i)) == way)
                createItem(QRect(left, top, width, height), QColor(Qt::gray));
            else if(graph_->status(QPoint(j, i)) == free_)
                createItem(QRect(left, top, width, height), QColor(Qt::white));
//            else if(graph_->status(QPoint(j, i)) == deployed)
//                createItem(QRect(left, top, width, height), QColor(Qt::green));
            left += width;
        }
        left = 0;
        top += height;
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pointF(event->scenePos());
    double xD = pointF.x();
    double yD = pointF.y();

    if(xD < 0 || yD < 0)
        return;

    int x = xD/sizeB.width();
    int y = yD/sizeB.height();

    if(x >= sizeField.width() || y >= sizeField.height())
        return;

    graph_->setPoint(QPoint(x, y));
}

void GraphicsScene::createItem(const QRect &rect, const QColor &color)
{
    Item *item = new Item(rect, color);
    addItem(item);
}
