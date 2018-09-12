#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include "drawwidget.h"
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFont>
#include <QPair>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QMouseEvent>
#include <QPaintEvent>

#include <QEventLoop>
#include <QTimer>

const int defaultLeft = 100;
const int defaultButtom = 650;

class sortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit sortWidget(QWidget *parent = nullptr);
    ~sortWidget();

    void clear();
    void withdraw();
    void repaint(int a = -1, int b = -1);

//    void drawRect(QRect, int, QColor);
    void drawRect(int, QColor, int isTemp = 0);
    void drawRectText(QRect, QString, QPainter *);
    void swapRect(int, int);

    void loadArray(int);
    void addRect(int);

    void algorithm(QString);
    void setListWidget(QString);
    bool setShowBoard();

    void bubbleSort();
    void selectSort();
    void quickSort(int, int);

    void paintEvent(QPaintEvent *);

private:
    QListWidget *list;
    QListWidgetItem* item[11];

    QPixmap *pix, *pixTemp1, *pixTemp2;

    int left, buttom, speed;

    bool isRun, isShowBoard;

    Array *arr;

signals:

public slots:
    void setSpeed(int);

};

#endif // SORTWIDGET_H
