#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRect>
#include <QPoint>
//#include <QLine>

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

    void on_pathFinder_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};



class Rect : public QGraphicsItem
{
public:
    Rect(const QRect &rect, QGraphicsItem *parent = 0) : QGraphicsItem(parent), rec(rect) {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRect rec;
};

#endif // MAINWINDOW_H
