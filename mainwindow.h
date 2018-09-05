#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawwidget.h"
#include <QMainWindow>
#include <QToolBar>
#include <QPoint>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
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

    void on_animation_triggered();

    void on_changeEdgeValue_triggered();

private:
//    void initToolBar();
    void setStatusBar();

    QLabel *statusLabel[2];

    QLineEdit *inputBeg;

    Ui::MainWindow *ui;
    drawWidget *draw;

    int mode = 0;
};

#endif // MAINWINDOW_H
