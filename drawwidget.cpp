#include "drawwidget.h"

drawWidget::drawWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1440, 840);
    setAutoFillBackground(true);
    setPalette(QPalette(backgroundColor));
    pixTemp = new QPixmap(size());
    pixTemp->fill(QColor(0, 0, 0, 0));
    pixLine = new QPixmap(size());
    pixLine->fill(QColor(0, 0, 0, 0));
    pixCircle = new QPixmap(size());
    pixCircle->fill(QColor(0, 0, 0, 0));
    mode = 0;
}

drawWidget::~drawWidget()
{
    delete pixTemp;
    delete pixLine;
    delete pixCircle;
}

void drawWidget::clear()
{
    QPixmap *p = new QPixmap(size());
    p->fill(QColor(0, 0, 0, 0));
    pixCircle = p;
    pixLine = p;
    update();
}

void drawWidget::setMode(int x)
{
    mode = x;
}

void drawWidget::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pixLine);
    painter.drawPixmap(QPoint(0, 0), *pixTemp);
    painter.drawPixmap(QPoint(0, 0), *pixCircle);
}

void drawWidget::mousePressEvent(QMouseEvent *e)
{
    beginPos = e->pos();
    if (mode == 1){
        isDrawLine = 0;
        int id = graph.getCircleIndex(beginPos);
        if (id == -1) return;
        beginPos = graph.circle(id).pos();

        beginCircle = graph.circle(id);
        drawCircle(beginCircle, QColor(255, 99, 71));

        isDrawLine = 1;
    }
}

void drawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mode == 1 && isDrawLine){
        drawLine(-1, beginPos, e->pos());
    }
}

void drawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    endPos = e->pos();
    if (mode == 0){
        int id = graph.insert(e->pos());
        if (id == -1)
            return;
        Circle x = graph.circle(id);
        drawCircle(x, x.color());
    }
    if (mode == 1){
        if (isDrawLine){
            drawCircle(beginCircle, beginCircle.color());
        }
        int id = graph.link(beginPos, endPos);
        if (id == -1){
            pixTemp->fill(QColor(0, 0, 0, 0));
            update();
            return;
        }
        Line x = graph.line(id);
        drawLine(id, x.begin(), x.end());
    }
}
