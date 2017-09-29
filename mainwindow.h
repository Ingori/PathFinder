#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRect>
#include <QPoint>
//#include <QLine>
#include "graph.h"

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
    QGraphicsScene *scene;

    Graph *graph;
};

#endif // MAINWINDOW_H
