#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
    ui->countEl->setValue(scene->setCountBlocks(ui->countEl->value()));
}



QRectF Item::boundingRect() const
{
    return QRectF(rec);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->setBrush(QBrush(color_));
    painter->drawRoundedRect(rec, 0, 0);
}



GraphicsScene::GraphicsScene(Graph *graph, QObject *parent) :
    QGraphicsScene(parent), graph_(graph)
{
    connect(graph_, &Graph::dataChanged, this, &GraphicsScene::updateField);
    connect(graph_, &Graph::cantFindPath, this, &GraphicsScene::messageCantFind);
}

bool GraphicsScene::setSizeSceneBlock(const QSize &sizeScene, const QSize &sizeBlock)
{
    /**/
    sizeS = sizeScene;
    sizeB = sizeBlock;
    sizeField = QSize(sizeScene.width()/sizeBlock.width(), sizeScene.height()/sizeBlock.height());
    graph_->setSizeField(sizeField);
}

int GraphicsScene::setCountBlocks(int count)
{
    return countBlocks = graph_->setCountBlocks(count);
}

void GraphicsScene::updateField()
{
    clear();

    int left, top, width, height;
    left = top = 0;
    width = sizeB.width();
    height = sizeB.height();
    sizeField = graph_->size();

    addRect(QRectF(QPoint(0, 0), sizeS), QPen(QColor(Qt::black)));

    for(int i = 0; i < sizeField.height(); i++)
    {
        for(int j = 0; j < sizeField.width(); j++)
        {
            if(graph_->status(QPoint(j, i)) == block)
                createItem(QRect(left, top, width, height), QColor(Qt::black));
            else if(graph_->status(QPoint(j, i)) == way)
                createItem(QRect(left, top, width, height), QColor(Qt::green));
            else if(graph_->status(QPoint(j, i)) == strend)
                createItem(QRect(left, top, width, height), QColor(Qt::red));
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

void GraphicsScene::messageCantFind()
{
    QMessageBox::information(nullptr, QString(), tr("Путь не найден."));
}

void GraphicsScene::createItem(const QRect &rect, const QColor &color)
{
    Item *item = new Item(rect, color);
    addItem(item);
}
