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



class Rect : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Rect(const QRect &rect, QGraphicsItem *parent = 0) : QGraphicsItem(parent), rec(rect) {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRect rec;
};



class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(const Graph *graph, QObject *parent = 0);

    bool setSizeSceneBlock(const QSize &sizeScene, const QSize &sizeBlock);
    bool setCountBlocks(int count);

public slots:
    void updateData();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected: signals:
    void changeSizeField(const QSize &size);
    void changeCountBlocks(int count);
    void changeStartEnd(const QPoint &start, const QPoint &end);

private:
    QSize sizeS, sizeB, sizeField;
    int countBlocks;
    QPoint start_, end_;

    const Graph *graph_;
};

#endif // MAINWINDOW_H
