#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QPoint>
#include <QVector>
#include <QPair>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <QDebug>

const int defaultSize = 35;

class ColorList{
private:
    QVector<QColor> v;

public:
    ColorList(){ v.clear(); }
    void init();
    QColor operator[](int i);
    QColor randomColor();
};

class Canvas
{
protected:
    int _id;
    QColor _color;

public:
    virtual int id(){ return _id; }
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
        _id = i;
    }

    QPoint pos(){ return _pos; }
    int size(){ return _size; }
    double distance(QPoint x);
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
        _id = i;
    }

    QPoint begin(){return _begin;}
    QPoint end(){return _end;}
    QPoint v(){return _end - _begin;}
};

class Container
{
protected:
    QVector<Circle> _circle;
    QVector<Line> _line;
    ColorList mld;

    int insertCircle(QPoint pos, int size = defaultSize);
    QPair<int,int> insertLine(QPoint begin, QPoint end);

public:
    Circle circle(int i){return _circle[i];}
    Line line(int i){return _line[i];}
    bool isInCircle(QPoint x, int range = 0);
    int getCircleIndex(QPoint x);

    virtual void clear() = 0;
    virtual int insert(QPoint) = 0;
    virtual int link(QPoint, QPoint) = 0;
};

//struct Operator
//{
//private:
//    Circle x;
//    Line y;
//    int _type;
//public:
//    Operator(Circle a)
//    {
//        _type = 0;
//        x = a;
//    }
//    Operator(Line a)
//    {
//        _type = 1;
//        y = a;
//    }
//    Operator()
//    {
//        _type = -1;
//    }
//    int type(){return _type;}
//    Circle data(){return x;}
//    Line data(int){return y;}
//};

#endif // CANVAS_H


