#include "canvas.h"

void ColorList::init()
{
    if (!v.empty()) return;
//        qDebug() << "haha";

    std::string path = basePath + "color.txt";
    freopen(path.c_str(), "r", stdin);
    int r, g, b;
    while (~scanf("%d%d%d", &r, &g, &b)){
//            qDebug("%d %d %d", r, g, b);
        v.append(QColor(r, g, b));
    }
    fclose(stdin);
}

QColor ColorList::operator[](int i)
{
    if (i >= v.length()) return QColor(0, 0, 0);
    return v[i];
}

QColor ColorList::randomColor()
{
    int r = rand() % v.size();
    return v[r];
}


double Circle::distance(QPoint x)
{
    double d1 = 1.0 * x.x() - 1.0 * _pos.x();
    double d2 = 1.0 * x.y() - 1.0 * _pos.y();
    return sqrt(d1 * d1 + d2 * d2);
}



bool Container::isInCircle(QPoint x, int range)
{
    for (auto& t : _circle){
//            qDebug("Check: %lf %d %d", t.distance(x), t.size(), range);
        if (t.distance(x) <= t.size() + range)
            return true;
    }
    return false;
}

int Container::getCircleIndex(QPoint x)
{
    for (auto& t : _circle){
        if (t.distance(x) <= t.size())
            return t.id();
    }
    return -1;
}

int Container::insertCircle(QPoint pos, int size)
{
    if (isInCircle(pos, size))
        return -1;
    Circle t(pos, size, _circle.size());
    t.setColor(mld.randomColor());
    _circle.append(t);
    return _circle.size() - 1;
}

QPair<int,int> Container::insertLine(QPoint begin, QPoint end)
{
    int x = getCircleIndex(begin), y = getCircleIndex(end);
    if (x == -1 || y == -1 || x == y)
        return QPair<int,int>(-1, -1);
    Line t(_circle[x].pos(), _circle[y].pos(), _line.size());
    t.setColor(Qt::black);
    _line.append(t);
    return QPair<int,int>(x,y);
}
