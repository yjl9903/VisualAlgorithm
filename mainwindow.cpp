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
    statusLabel[0]->setText("画板");
    statusBar()->addWidget(statusLabel[0]);

    statusLabel[1] = new QLabel(this);
    statusLabel[1]->setText("顶点");
    statusBar()->addWidget(statusLabel[1]);

    inputBeg = new QLineEdit(this);
    inputBeg->setMaximumWidth(200);
    inputBeg->setText("0");
    ui->mainToolBar->addWidget(inputBeg);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(50);
    slider->setMaximumWidth(200);
    ui->mainToolBar->addWidget(slider);
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
    statusLabel[0]->setText("画板");
    statusBar()->addWidget(statusLabel[0]);

    statusLabel[1] = new QLabel(this);
    if (mode == 0)
        statusLabel[1]->setText("顶点");
    else if (mode == 1)
        statusLabel[1]->setText("边");
    else if (mode == 2)
        statusLabel[1]->setText("动画");
    statusBar()->addWidget(statusLabel[1]);
}

void MainWindow::on_createVertex_triggered()
{
    mode = 0;
    if (draw->setMode(0)){
        setStatusBar();
    }
}

void MainWindow::on_createEdge_triggered()
{
    mode = 1;
    if (draw->setMode(1)){
        setStatusBar();
    }
}

void MainWindow::on_animation_triggered()
{
    mode = 2;

    draw->setMode(2);
    setStatusBar();

    draw->algorithm("dfs", inputBeg->text().toInt());
}

void MainWindow::on_changeEdgeValue_triggered()
{
    draw->setShowEdgeValue();
}
