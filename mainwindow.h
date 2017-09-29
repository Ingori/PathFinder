#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QRect>
#include <QPoint>
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

    void fillScene();
    GraphicsScene *scene;
//    Rect *rect;
    int width_, height;

    Graph *graph;
};



class Rect : public QGraphicsItem
{
public:
    Rect(const QRect &rect, QGraphicsItem *parent = 0) : QGraphicsItem(parent), rec(rect) {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRect rec;
};



class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(int width, int height, QObject *parent = 0) :
        QGraphicsScene(parent), width_(width), height_(height) { }

    bool setWidthHeight(int width, int height/*, int sizeBlock*/);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected: signals:
    void clicked(const QPoint &point);

private:
    int width_, height_;
};

#endif // MAINWINDOW_H
