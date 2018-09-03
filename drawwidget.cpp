#include "drawwidget.h"

QFont getFont()
{
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(defaultFontSize);
    return font;
}

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

void drawWidget::drawText(QPoint pos, QString str, QPainter& painter)
{
    painter.setFont(getFont());
    painter.setPen(QPen(Qt::black));
    pos.setX(pos.x() - 8);
    pos.setY(pos.y() + 8);
    painter.drawText(pos, str);
}

void drawWidget::drawLineText(QPoint beg, QPoint end, QString str, QPainter& painter)
{
    painter.setFont(getFont());
    painter.setPen(QPen(Qt::black));
    QPoint pos, half = (beg + end) / 2;

    if (beg.x() <= end.x()){
        pos.setY(half.y() - 15);
        if (beg.y() <= end.y()){
            qDebug() << 1;
            pos.setX(half.x() + 3);
        }
        else {
            qDebug() << 2;
            pos.setX(half.x() - 15);
        }
    }
    else {
        pos.setY(half.y() + 20);
        if (beg.y() <= end.y()){
            qDebug() << 3;
            pos.setX(half.x() + 15);
        }
        else {
            qDebug() << 4;
            pos.setX(half.x() - 30);
        }
    }

    painter.drawText(pos, str);
}

void drawWidget::drawCircle(QPoint x, int id, QColor color, int size)
{
    QPainter *painter = new QPainter(this);
    painter->begin(pixCircle);
    painter->setPen(QPen(color));
    painter->setBrush(QBrush(color));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(x, size, size);

    drawText(x, QString::number(id), *painter);

    painter->end();
    update();
}

void drawWidget::drawArrowLine(QPoint begin, QPoint end, QPainter& painter, QColor color, double size)
{
    double par = size;
    double slopy = atan2((end.y() - begin.y()), (end.x() - begin.x()));
    double cosy = cos(slopy);
    double siny = sin(slopy);

    QPoint point1 = QPoint(end.x() + int(-par*cosy - (par / 2.0*siny)), end.y() + int(-par*siny + (par / 2.0*cosy)));
    QPoint point2 = QPoint(end.x() + int(-par*cosy + (par / 2.0*siny)), end.y() - int(par / 2.0*cosy + par*siny));
    QPoint points[3] = { end, point1, point2 };

    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen drawTrianglePen;
    drawTrianglePen.setColor(color);
    drawTrianglePen.setWidth(3);
    painter.setPen(drawTrianglePen);
    painter.setBrush(QBrush(color));

    painter.drawPolygon(points, 3);
}

void drawWidget::drawLine(int k, QPoint beg, QPoint end, QColor color, int width)
{
    QPainter *painter = new QPainter(this);
    pixTemp->fill(QColor(0, 0, 0, 0));
    if (k == 0){
        painter->begin(pixTemp);
    }
    else{
        painter->begin(pixLine);
    }
    painter->setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawLine(beg, end);

    if (k == 0){
        drawArrowLine(beg, end, *painter);
    }
    else{
        QPoint v = end - beg;
        double x = v.x(), y = v.y();
        double t = sqrt(x * x + y * y);
        int id = container.getCircleIndex(end);
        double kk = (t - container.circle(id).size()) / t;
        QPoint tag = beg + v * kk;
        drawArrowLine(beg, tag, *painter);

        drawLineText(beg, end, QString::number(k), *painter);
    }

    painter->end();
    update();
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
        int id = container.getCircleIndex(beginPos);
        if (id == -1) return;
        beginPos = container.circle(id).pos();
        isDrawLine = 1;
    }
}

void drawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mode == 1 && isDrawLine){
        drawLine(0, beginPos, e->pos());
    }
}

void drawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    endPos = e->pos();
    if (mode == 0){
        int id = container.insertCircle(e->pos());
        if (id == -1)
            return;
        drawCircle(e->pos(), id, container.circle(id).color());
    }
    if (mode == 1){
        int id = container.insertLine(beginPos, endPos);
        if (id == -1){
            pixTemp->fill(QColor(0, 0, 0, 0));
            update();
            return;
        }
        drawLine(rand() % 9 + 1, container.line(id).begin(), container.line(id).end());
    }
}
