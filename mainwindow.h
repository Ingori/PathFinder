#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_refresh_clicked();

    void on_pathFinder_clicked();

private:
    Ui::MainWindow *ui;
    Keeper *keeper_;
};

#endif // MAINWINDOW_H
