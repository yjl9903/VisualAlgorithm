#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawwidget.h"
#include <QMainWindow>
#include <QToolBar>
#include <QSlider>
#include <QPushButton>
#include <QAction>
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

    void on_load1_triggered();

    void on_load2_triggered();

    void on_load3_triggered();

    void on_load4_triggered();

    void on_load5_triggered();

    void on_load6_triggered();

    void on_load7_triggered();

    void on_actiondfs_triggered();

    void on_actionbfs_triggered();

    void on_showDraw_triggered();

    void on_clearDraw_triggered();

    void on_withdrawDraw_triggered();

    void on_changeBoard_triggered();

private:
//    void initToolBar();
    void setStatusBar();
    void setToolBar(int);

    QLabel *statusLabel[2], *space[5];

    QLineEdit *inputBeg;

    Ui::MainWindow *ui;
    drawWidget *draw;

    int mode = 0;
    QString running;
    bool isRunning, isShowEdgeValue, isShowBoard;
};

#endif // MAINWINDOW_H
