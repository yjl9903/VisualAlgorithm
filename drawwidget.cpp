#include "drawwidget.h"

drawWidget::drawWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1000, 800);
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());
    pix->fill(backgroundColor);
    mode = 0;
}

drawWidget::~drawWidget()
{
    delete pix;

}

void drawWidget::clear()
{
    QPixmap *p = new QPixmap(size());
    p->fill(backgroundColor);
    pix = p;
    update();
}

void drawWidget::setMode(int x)
{
    mode = x;
}

void drawWidget::drawCircle(QPoint x, QColor color, int size)
{
    QPainter *painter = new QPainter(this);
    painter->begin(pix);
//    painter->setPen(QPen(Qt::blue));
    painter->setPen(QPen(color));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(x, size, size);
    painter->end();
    update();
}

void drawWidget::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
}

void drawWidget::mousePressEvent(QMouseEvent *e)
{
    beginPos = e->pos();
}

void drawWidget::mouseMoveEvent(QMouseEvent *e)
{

}

void drawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    endPos = e->pos();
    if (mode == 0){
        int id = container.insertCircle(e->pos());
//        qDebug("%d", id);
        if (id == -1)
            return;
        drawCircle(e->pos(), container.circle(id).color());
    }
    if (mode == 1){

    }
}
