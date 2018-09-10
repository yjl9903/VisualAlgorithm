#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    draw = new drawWidget;
    setCentralWidget(draw);

    statusLabel[0] = new QLabel(this);
    statusLabel[0]->setText("画板  ");
    statusBar()->addWidget(statusLabel[0]);

    statusLabel[1] = new QLabel(this);
    statusLabel[1]->setText("顶点  ");
    statusBar()->addWidget(statusLabel[1]);
    setAttribute(Qt::WA_QuitOnClose);

//    space[0]->setFixedWidth(10);
    setToolBar(0);

    isRunning = isShowEdgeValue = 0;
    isShowBoard = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatusBar()
{
    delete statusLabel[0];
    delete statusLabel[1];

    statusLabel[0] = new QLabel(this);
    statusLabel[0]->setText("画板  ");
    statusBar()->addWidget(statusLabel[0]);

    statusLabel[1] = new QLabel(this);
    if (mode == 0)
        statusLabel[1]->setText("顶点  ");
    else if (mode == 1)
        statusLabel[1]->setText("边  ");
    else if (mode == 2)
        statusLabel[1]->setText(running + "  ");
    statusBar()->addWidget(statusLabel[1]);
}

void MainWindow::setToolBar(int type)
{
    ui->mainToolBar->clear();

//    ui->mainToolBar->addAction(ui->createVertex);
//    ui->mainToolBar->addAction(ui->createEdge);

    QLabel *space[5];
    for (int i = 0; i < 5; i++)
        space[i] = new QLabel(this), space[i]->setFixedWidth(20);

    if (type == 0){
        ui->mainToolBar->addAction(ui->createVertex);
        ui->mainToolBar->addWidget(space[0]);
        ui->mainToolBar->addAction(ui->createEdge);
        ui->mainToolBar->addWidget(space[1]);
        ui->mainToolBar->addAction(ui->withdrawDraw);
        ui->mainToolBar->addWidget(space[2]);
        ui->mainToolBar->addAction(ui->clearDraw);
    }

    if (type == 1){
        QLabel *start = new QLabel(this);

        // ui->mainToolBar->addWidget(space[0]);

        ui->mainToolBar->addAction(ui->showDraw);
        ui->mainToolBar->addWidget(space[3]);

        start->setText("起点:  ");
        ui->mainToolBar->addWidget(start);

        inputBeg = new QLineEdit(this);
        inputBeg->setMaximumWidth(200);
        inputBeg->setText("0");
        ui->mainToolBar->addWidget(inputBeg);

        ui->mainToolBar->addWidget(space[1]);

        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(100);
        slider->setValue(50);
        slider->setMaximumWidth(200);
        ui->mainToolBar->addWidget(slider);

        connect(slider, SIGNAL(valueChanged(int)), draw, SLOT(setSpeed(int)));

        ui->mainToolBar->addWidget(space[2]);

        ui->animation->setText("Let's " + running + "!");
        ui->mainToolBar->addAction(ui->animation);
    }
}

void MainWindow::on_createVertex_triggered()
{
    if (draw->setMode(0)){
        mode = 0;
        setStatusBar();
    }
}

void MainWindow::on_createEdge_triggered()
{
    if (draw->setMode(1)){
        mode = 1;
        setStatusBar();
    }
}

void MainWindow::on_animation_triggered()
{
//    mode = 2;
    if (isRunning) return;
    isRunning = 1;
    draw->setMode(2);
//    setStatusBar();

    bool ok;
    inputBeg->text().toInt(&ok);
    if (ok) draw->algorithm(running, inputBeg->text().toInt());

    isRunning = 0;
//    ui->mainToolBar->clear();

//    ui->mainToolBar->addAction(ui->createVertex);
//    ui->mainToolBar->addAction(ui->createEdge);
}

void MainWindow::on_changeEdgeValue_triggered()
{
    if (draw->setShowEdgeValue()){
        isShowEdgeValue ^= 1;
        if (isShowEdgeValue){
            ui->changeEdgeValue->setText("关闭边权");
        }
        else{
            ui->changeEdgeValue->setText("显示边权");
        }
    }
}

void MainWindow::on_changeBoard_triggered()
{
    if (!isRunning) return;
    isShowBoard ^= 1;
    if (isShowBoard){
        ui->changeBoard->setText("关闭伪代码");
    }
    else {
        ui->changeBoard->setText("开启伪代码");
    }
    draw->setShowBoard();
}

void MainWindow::on_load1_triggered()
{
    draw->loadGraph(1);
}

void MainWindow::on_load2_triggered()
{
    draw->loadGraph(2);
}

void MainWindow::on_load3_triggered()
{
    draw->loadGraph(3);
}

void MainWindow::on_load4_triggered()
{
    draw->loadGraph(4);
}

void MainWindow::on_load5_triggered()
{
    draw->loadGraph(5);
}

void MainWindow::on_load6_triggered()
{
    draw->loadGraph(6);
}

void MainWindow::on_load7_triggered()
{
    draw->loadGraph(7);
}

void MainWindow::on_actiondfs_triggered()
{
    if (isRunning) return;
    running = "dfs";
    mode = 2;
    draw->setSpeed(50);
    setStatusBar();
    setToolBar(1);

}

void MainWindow::on_actionbfs_triggered()
{
    if (isRunning) return;
    running = "bfs";
    mode = 2;
    draw->setSpeed(50);
    setStatusBar();
    setToolBar(1);
}


void MainWindow::on_showDraw_triggered()
{
    if (draw->setMode(0)){
        mode = 0;

        draw->repaint();

        setToolBar(0);
//        ui->mainToolBar->clear();

//        ui->mainToolBar->addAction(ui->createVertex);
//        ui->mainToolBar->addAction(ui->createEdge);
//        ui->mainToolBar->addAction(ui->withdrawDraw);
//        ui->mainToolBar->addAction(ui->clearDraw);

        setStatusBar();
    }
}

void MainWindow::on_clearDraw_triggered()
{
    draw->clear();
}

void MainWindow::on_withdrawDraw_triggered()
{
    draw->withdraw();
}

