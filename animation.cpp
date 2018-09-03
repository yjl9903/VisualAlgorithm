#include "drawwidget.h"

QFont getFont()
{
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(defaultFontSize);
    return font;
}

void drawWidget::drawText(QPoint pos, QString str, QPainter& painter)
{
    painter.setFont(getFont());
    painter.setPen(QPen(Qt::black));
    if (str.size() == 1){
        pos.setX(pos.x() - 8);
        pos.setY(pos.y() + 8);
    }
    else {
        pos.setX(pos.x() - 16);
        pos.setY(pos.y() + 8);
    }
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

void drawWidget::drawCircle(Circle x, QColor color, int size)
{
    QPainter *painter = new QPainter(this);
    painter->begin(pixCircle);
    painter->setPen(QPen(color));
    painter->setBrush(QBrush(color));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(x.pos(), size, size);

    drawText(x.pos(), QString::number(x.id()), *painter);

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

void drawWidget::drawLine(int id, QPoint beg, QPoint end, QColor color, int width)
{
    QPainter *painter = new QPainter(this);
    pixTemp->fill(QColor(0, 0, 0, 0));
    if (id == -1){
        painter->begin(pixTemp);
    }
    else{
        painter->begin(pixLine);
    }
    painter->setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawLine(beg, end);

    if (id == -1){
        drawArrowLine(beg, end, *painter);
    }
    else{
        QPoint v = end - beg;
        double x = v.x(), y = v.y();
        double t = sqrt(x * x + y * y);
        int i = graph.getCircleIndex(end);
        double k = (t - graph.circle(i).size()) / t;
        QPoint tag = beg + v * k;

        drawArrowLine(beg, tag, *painter);

        drawLineText(beg, end, QString::number(graph.val(id)), *painter);
    }

    painter->end();
    update();
}
