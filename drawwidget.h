#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include "canvas.h"
#include <QWidget>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QMouseEvent>
#include <QPaintEvent>

const QColor backgroundColor = QColor(255, 239, 219);

class drawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit drawWidget(QWidget *parent = nullptr);

    ~drawWidget();

    void clear();
    void setMode(int);

    void drawCircle(QPoint, QColor color = Qt::yellow, int size = defaultSize);
    void drawLine(QPoint);
    void paintEvent(QPaintEvent *);

private:
    QPixmap *pix;

    int mode = 0;

    QPoint beginPos, endPos;

    Container container;


signals:

public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // DRAWWIDGET_H
