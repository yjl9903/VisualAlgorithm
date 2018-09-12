#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QVector>
#include <QPair>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <QDebug>

const int defaultSize = 35;
const int defaultUnitHeight = 50;
const int defaultUnitWidth = 80;

const std::string basePath = "\\";

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

class Rect : public Canvas
{
private:
    QRect _rect;

public:
    Rect(){ _rect = QRect(0, 0, 0, 0); }
    Rect(int x, int y, int w, int h){ _rect = QRect(x, y, w, h); }
    int setID(int i){ _id = i; }
    QSize size(){return _rect.size();}
    QRect rect(){return _rect;}
    int left(){return _rect.left();}
    int right(){return _rect.right();}
    void setLeft(int i){ _rect.setLeft(i); }
    void setRight(int i){ _rect.setRight(i); }
    void moveTo(int x){ _rect.setLeft(x); _rect.setRight(x + defaultUnitWidth); }
};

class Array
{
private:
    QVector<Rect> v;
    QVector<int> _val;
    ColorList mld;

public:
    Array()
    {
        v.clear();
        mld.init();
    }
    int size(){return v.size();}
    Rect &rect(int i){ return v[i]; }
    int val(int i){ return _val[i]; }
    int insert(QPoint pos, int x)
    {
        if (v.size() == 14) return -1;

        int h = x * defaultUnitHeight;
        Rect t(pos.x(), pos.y() - h, defaultUnitWidth, h);
        t.setColor(mld.randomColor());

        v.append(t);
        _val.append(x);
//        qDebug() << (int)v.size() - 1;
        return (int)v.size() - 1;
    }

    void swap(int a, int b)
    {
        Rect t = v[a];
        v[a] = v[b];
        v[b] = t;
        int t2 = v[a].id();
        v[a].setID(v[b].id());
        v[b].setID(t2);
        t2 = _val[a];
        _val[a] = _val[b];
        _val[b] = t2;
    }

    void del()
    {
        v.pop_back();
        _val.pop_back();
    }

    void clear()
    {
        v.clear();
        _val.clear();
    }
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


