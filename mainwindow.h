#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QRect>
#include <QPoint>
#include <QSize>
//#include <QLine>
#include "graph.h"

class GraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;
    GraphicsScene *scene;
    Graph *graph;
};



class Item : public QGraphicsItem
{
public:
    Item(const QRect &rect, const QColor &color, QGraphicsItem *parent = 0)
        : QGraphicsItem(parent), rec(rect), color_(color) {}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setColor(const QColor &color) { color_ = color; update(); }

private:
    QRect rec;
    QColor color_;
};



class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(Graph *graph, QObject *parent = 0);

    bool setSizeSceneBlock(const QSize &sizeScene, const QSize &sizeBlock);
    int setCountBlocks(int count);

//public slots:
//    void updateField();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void updateField();
    void messageCantFind();

private:
    void createItem(const QRect &rect, const QColor &color);

    QSize sizeS, sizeB, sizeField;
    int countBlocks;
    Graph *graph_;
};

#endif // MAINWINDOW_H
