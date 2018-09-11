#include "mainwindow.h"
#include "ui_mainwindow.h"

void showMsg(QString str)
{
    QMessageBox *msg = new QMessageBox(
        "Error", str,
        QMessageBox::Critical,
        QMessageBox::Ok | QMessageBox::Default,
        QMessageBox::Escape, 0
    );
    msg->show();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    draw = new drawWidget;
    sort = new sortWidget;
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

    mode = 0;
    algorithmMode = 0;
    isRunning = isShowEdgeValue = 0;
    isShowBoard = 1;
}

MainWindow::~MainWindow()
{
    delete draw;
    delete ui;
}

void MainWindow::setStatusBar()
{
    delete statusLabel[0];
    delete statusLabel[1];

    if (algorithmMode == 0){
        statusLabel[0] = new QLabel(this);
        statusLabel[0]->setText("画板  ");
        statusBar()->addWidget(statusLabel[0]);

        statusLabel[1] = new QLabel(this);
        if (mode == 0)
            statusLabel[1]->setText("顶点  ");
        else if (mode == 1)
            statusLabel[1]->setText("边  ");
        else if (mode == 2){
            if (running == "dfs") statusLabel[1]->setText("深度优先搜索  ");
            else if (running == "bfs") statusLabel[1]->setText("宽度优先搜索  ");
        }
        statusBar()->addWidget(statusLabel[1]);
    }
    if (algorithmMode == 1){
        statusLabel[0] = new QLabel(this);
        statusLabel[0]->setText("排序   ");
        statusBar()->addWidget(statusLabel[0]);

        statusLabel[1] = new QLabel(this);
        statusLabel[1]->setText("  ");

        if (running == "bubble") statusLabel[1]->setText("冒泡排序  ");
        else if (running == "quick") statusLabel[1]->setText("快速排序  ");

        statusBar()->addWidget(statusLabel[1]);
    }
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

    if (type == 2){
        QLabel *hint = new QLabel(this);

//        space[0]->setFixedWidth(10);
//        ui->mainToolBar->addWidget(space[0]);

        ui->mainToolBar->addAction(ui->randomRect);
        ui->mainToolBar->addWidget(space[0]);

        hint->setText("高度:  ");
        ui->mainToolBar->addWidget(hint);

        inputRect = new QLineEdit(this);
        inputRect->setMaximumWidth(100);
        inputRect->setText("1");
        ui->mainToolBar->addWidget(inputRect);

        ui->mainToolBar->addWidget(space[1]);

        ui->mainToolBar->addAction(ui->createRect);

        ui->mainToolBar->addWidget(space[3]);
        ui->mainToolBar->addAction(ui->withdrawDraw);
        ui->mainToolBar->addWidget(space[4]);
        ui->mainToolBar->addAction(ui->clearDraw);
    }

    if (type == 3){
//        space[0]->setFixedWidth(10);

        ui->mainToolBar->addAction(ui->showSort);

        ui->mainToolBar->addWidget(space[1]);

        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(100);
        slider->setValue(50);
        slider->setMaximumWidth(200);
        ui->mainToolBar->addWidget(slider);

        connect(slider, SIGNAL(valueChanged(int)), sort, SLOT(setSpeed(int)));

        ui->mainToolBar->addWidget(space[2]);

        ui->animation->setText("Let's " + running + " sort!");
        ui->mainToolBar->addAction(ui->animation);
    }
}

void MainWindow::on_changeAlgorithmMode_triggered()
{
    if (isRunning) return;

    algorithmMode ^= 1;

    if (algorithmMode){
//        delete draw;
        takeCentralWidget();
        setCentralWidget(sort);
        ui->changeAlgorithmMode->setText("画板模式");

        isRunning = 0;
        isShowBoard = 1;

        ui->menuLoad->setTitle(" 数组 ");

        ui->menuAlgo->removeAction(ui->actiondfs);
        ui->menuAlgo->removeAction(ui->actionbfs);
        ui->menuSet->removeAction(ui->changeEdgeValue);

        ui->menuAlgo->addAction(ui->actionBubble);
        ui->menuAlgo->addAction(ui->actionQuick);

        setStatusBar();
        setToolBar(2);
    }
    else{
//        delete sort;
//        draw = new drawWidget;
        takeCentralWidget();
        setCentralWidget(draw);
        ui->changeAlgorithmMode->setText("排序模式");
        isRunning = isShowEdgeValue = 0;
        isShowBoard = 1;

        ui->menuLoad->setTitle("  图  ");

        ui->menuAlgo->addAction(ui->actiondfs);
        ui->menuAlgo->addAction(ui->actionbfs);

        ui->menuSet->removeAction(ui->changeBoard);
        ui->menuSet->removeAction(ui->changeAlgorithmMode);
        ui->menuSet->addAction(ui->changeEdgeValue);
        ui->menuSet->addAction(ui->changeBoard);
        ui->menuSet->addAction(ui->changeAlgorithmMode);

        ui->menuAlgo->removeAction(ui->actionBubble);
        ui->menuAlgo->removeAction(ui->actionQuick);

        setStatusBar();
        setToolBar(0);
    }
}

void MainWindow::on_createVertex_triggered()
{
    if (algorithmMode) return;
    if (draw->setMode(0)){
        mode = 0;
        setStatusBar();
    }
}

void MainWindow::on_createEdge_triggered()
{
    if (algorithmMode) return;
    if (draw->setMode(1)){
        mode = 1;
        setStatusBar();
    }
}

void MainWindow::on_animation_triggered()
{
//    mode = 2;
    if (isRunning) return;

    if (algorithmMode == 0){
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

    if (algorithmMode == 1){
        isRunning = 1;

        sort->algorithm(running);

        isRunning = 0;
    }
}

void MainWindow::on_changeEdgeValue_triggered()
{
    if (algorithmMode) return;
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
//    if (!isRunning) return;
    isShowBoard ^= 1;
    if (isShowBoard){
        ui->changeBoard->setText("关闭伪代码");
    }
    else {
        ui->changeBoard->setText("开启伪代码");
    }
    draw->setShowBoard();
    sort->setShowBoard();
}

void MainWindow::on_load1_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(1);
    else if (algorithmMode == 1) sort->loadArray(1);
}

void MainWindow::on_load2_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(2);
    else if (algorithmMode == 1) sort->loadArray(2);
}

void MainWindow::on_load3_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(3);
    else if (algorithmMode == 1) sort->loadArray(3);
}

void MainWindow::on_load4_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(4);
    else if (algorithmMode == 1) sort->loadArray(4);
}

void MainWindow::on_load5_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(5);
    else if (algorithmMode == 1) sort->loadArray(5);
}

void MainWindow::on_load6_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(6);
    else if (algorithmMode == 1) sort->loadArray(6);
}

void MainWindow::on_load7_triggered()
{
    if (algorithmMode == 0) draw->loadGraph(7);
    else if (algorithmMode == 1) sort->loadArray(7);
}

void MainWindow::on_actiondfs_triggered()
{
    if (algorithmMode) return;
    if (isRunning) return;
    running = "dfs";
    mode = 2;
    draw->setSpeed(50);
    setStatusBar();
    setToolBar(1);

}

void MainWindow::on_actionbfs_triggered()
{
    if (algorithmMode) return;
    if (isRunning) return;
    running = "bfs";
    mode = 2;
    draw->setSpeed(50);
    setStatusBar();
    setToolBar(1);
}


void MainWindow::on_actionBubble_triggered()
{
//    sort->swapRect(0, 3);
    if (!algorithmMode) return;
    if (isRunning) return;
    running = "bubble";
    sort->setSpeed(50);
    setStatusBar();
    setToolBar(3);
}

void MainWindow::on_actionQuick_triggered()
{
    if (!algorithmMode) return;
    if (isRunning) return;
    running = "quick";
    sort->setSpeed(50);
    setStatusBar();
    setToolBar(3);
}

void MainWindow::on_showDraw_triggered()
{
    if (algorithmMode) return;
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

void MainWindow::on_showSort_triggered()
{
    if (!algorithmMode) return;
    if (isRunning) return;

    sort->repaint();

    setToolBar(2);
    setStatusBar();
}

void MainWindow::on_clearDraw_triggered()
{
    if (algorithmMode == 0)
        draw->clear();
    else if (algorithmMode == 1)
        sort->clear();
}

void MainWindow::on_withdrawDraw_triggered()
{
    if (algorithmMode == 0)
        draw->withdraw();
    else if (algorithmMode == 1)
        sort->withdraw();
}

void MainWindow::on_createRect_triggered()
{
    QString str = inputRect->text();
    inputRect->setText("1");
    bool ok;
    int x = str.toInt(&ok);
    if (!ok || x > 12 || x < -3) {
        showMsg("您输入的高度有误！");
        return;
    }
    sort->addRect(x);
}

void MainWindow::on_randomRect_triggered()
{
    int x = rand() % 16 - 4;
    sort->addRect(x);
}
