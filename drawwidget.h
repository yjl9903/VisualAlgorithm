#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include "canvas.h"
#include "graph.h"
#include <cmath>
#include <QWidget>
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

const QColor backgroundColor = QColor(255, 239, 219);
const int defaultFontSize = 12;

class drawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit drawWidget(QWidget *parent = nullptr);

    ~drawWidget();

    void clear();
    void setMode(int);

    void drawText(QPoint, QString, QPainter&);
    void drawLineText(QPoint, QPoint, QString, QPainter&);
    void drawCircle(Circle, QColor color = Qt::yellow, int size = defaultSize);
    void drawLine(int k, QPoint, QPoint, QColor = Qt::black, int width = 3);
    void drawArrowLine(QPoint, QPoint, QPainter&, QColor color = Qt::black, double size = 10.0);
    void drawLine(QPoint);
    void paintEvent(QPaintEvent *);

private:
    QPixmap *pixTemp, *pixLine, *pixCircle;

    int mode = 0;
    bool isDrawLine;

    QPoint beginPos, endPos;

    // Container container;
    Graph graph;

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // DRAWWIDGET_H
