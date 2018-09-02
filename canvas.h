#ifndef CANVAS_H
#define CANVAS_H

#endif // CANVAS_H

#include <QColor>
#include <QPoint>
#include <QVector>
#include <QPair>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <QDebug>

const int defaultSize = 30;

class ColorList{
private:
    QVector<QColor> v;

public:
    ColorList(){ v.clear(); }
    void init()
    {
        if (!v.empty()) return;
//        qDebug() << "haha";

        freopen("E:\\color.txt", "r", stdin);
        int r, g, b;
        while (~scanf("%d%d%d", &r, &g, &b)){
//            qDebug("%d %d %d", r, g, b);
            v.append(QColor(r, g, b));
        }
        fclose(stdin);
    }
    QColor operator[](int i)
    {
        if (i >= v.length()) return QColor(0, 0, 0);
        return v[i];
    }
    QColor randomColor()
    {
        int r = rand() % v.size();
        return v[r];
    }
};

class Canvas
{
protected:
    int id;
    QColor _color;

public:
    virtual int getID(){ return id; }
    virtual void setColor(QColor x){ _color = x; }
    virtual QColor color(){ return _color; }
};

class Circle : public Canvas
{
private:
    QPoint _pos;
    int _size;

public:
    Circle()
    {
        _pos = QPoint(0, 0);
        _size = 0;
    }
    Circle(QPoint x, int sz, int i)
    {
        _pos = x;
        _size = sz;
        id = i;
    }

    QPoint pos(){ return _pos; }
    int size(){ return _size; }
    double distance(QPoint x)
    {
        double d1 = 1.0 * x.x() - 1.0 * _pos.x();
        double d2 = 1.0 * x.y() - 1.0 * _pos.y();
        return sqrt(d1 * d1 + d2 * d2);
    }
};

class Line : public Canvas
{
private:
    QPoint _begin, _end;

public:
    Line()
    {
        _begin = QPoint(0, 0);
        _end = QPoint(0, 0);
    }
    Line(QPoint bg, QPoint ed, int i)
    {
        _begin = bg;
        _end = ed;
        id = i;
    }

    QPoint begin(){return _begin;}
    QPoint end(){return _end;}
};

class Container
{
private:
    QVector<Circle> _circle;
    QVector<Line> _line;
    ColorList mld;
public:
    Container()
    {
        mld.init();
        _circle.clear();
        _line.clear();
    }
    Circle circle(int i){return _circle[i];}
    Line line(int i){return _line[i];}
    bool isInCircle(QPoint x, int range = 0)
    {
        for (auto& t : _circle){
//            qDebug("Check: %lf %d %d", t.distance(x), t.size(), range);
            if (t.distance(x) <= t.size() + range)
                return true;
        }
        return false;
    }
    int getCircleIndex(QPoint x)
    {
        for (auto& t : _circle){
            if (t.distance(x) <= t.size())
                return t.getID();
        }
        return -1;
    }
    int insertCircle(QPoint pos, int size = defaultSize)
    {
        if (isInCircle(pos, size))
            return -1;
        Circle t(pos, size, _circle.size());
        t.setColor(mld.randomColor());
        _circle.append(t);
        return _circle.size() - 1;
    }
    int insertLine(QPoint begin, QPoint end)
    {
        int x = getCircleIndex(begin), y = getCircleIndex(end);
        if (x == -1 || y == -1)
            return -1;
        Line t(_circle[x].pos(), _circle[y].pos(), _line.size());
        _line.append(t);
        return t.getID();
    }
};


