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

// #include <QTimeLine>
// #include <QThread>
#include <QTimer>
#include <QEventLoop>

const QColor backgroundColor = QColor(255, 239, 219);
const QColor lineAnimeColor = QColor(250, 128, 114);
const int defaultFontSize = 12;
const int defaultLineSize = 3;

inline void sleep(int time)
{
    QEventLoop loop;
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}

class drawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit drawWidget(QWidget *parent = nullptr);

    ~drawWidget();

    void clear();
    void setMode(int);
    void setShowEdgeValue();

    void repaint();

    void drawText(QPoint, QString, QPainter&);
    void drawLineText(QPoint, QPoint, QString, QPainter&);
    void drawCircle(Circle, QColor color = Qt::yellow);
    void drawLine(int k, QPoint, QPoint, QColor = Qt::black, int width = defaultLineSize);
    void drawArrowLine(QPoint, QPoint, QPainter&, QColor color = Qt::black, double size = 10.0);
    void drawLine(QPoint);

    void drawLineAnimation(Line, QColor);
    void algorithm(QString, int);

    void dfs(int);

    void paintEvent(QPaintEvent *);

private:
    QPixmap *pixTemp, *pixLine, *pixCircle;

    int mode = 0;
    bool isDrawLine, isShowEdgeValue;

    QPoint beginPos, endPos;
    Circle beginCircle;

    Graph graph;

    bool vis[100];

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // DRAWWIDGET_H
