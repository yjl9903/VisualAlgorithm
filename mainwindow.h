#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawwidget.h"
#include <QMainWindow>
#include <QToolBar>
#include <QPoint>
#include <QVector>
#include <QLabel>
#include <ctime>
#include <cstdlib>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createVertex_triggered();

    void on_createEdge_triggered();

private:
//    void initToolBar();
    void setStatusBar();

    QLabel* statusLabel[2];

    Ui::MainWindow *ui;
    drawWidget *draw;

    int mode = 0;
};

#endif // MAINWINDOW_H
