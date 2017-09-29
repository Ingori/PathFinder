#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("PathFinder");

    graph = new Graph(ui->widthScreen->value(), ui->highScreen->value());

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refresh_clicked()
{
    scene->clear();
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
                scene->addRect(left, top, width, height, QPen(), QBrush(QColor(Qt::black)));
            left += width;
        }
        left = 0;
        top += height;
    }
}
