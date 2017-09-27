#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "finder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Keeper *keeper, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateView();

protected: signals:
    void refreshBlocks();
    void refreshWay();

private slots:
    void on_refresh_clicked();

    void on_pathFinder_clicked();

private:
    void writeToKeeper();

    Ui::MainWindow *ui;
    Keeper *const keeper_;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
