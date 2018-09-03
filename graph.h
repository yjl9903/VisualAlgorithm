#ifndef GRAPH_H
#define GRAPH_H

#include "canvas.h"
#include <cstring>

class Graph : public Container
{
private:
    int n, m;
    int G[100][100];
    QVector<int> _val;

public:
    Graph()
    {
        mld.init();
        _circle.clear();
        _line.clear();
        n = m = 0;
        memset(G, 0, sizeof G);
    }
    int val(int i){return _val[i];}
    int insert(QPoint pos)
    {
        if (n == 100) return -1;
        int id = insertCircle(pos);
        if (id == -1) return -1;
        return n++;
    }
    int link(QPoint beg, QPoint end)
    {
        QPair<int,int> id = insertLine(beg, end);
        if (id.first == -1 && id.second == -1) return -1;
        if (G[id.first][id.second]) {
            _line.pop_back();
            return -1;
        }
        int v = rand() % 9 + 1;
        _val.append(v);
        G[id.first][id.second] = v;
        return m++;
    }
};

#endif // GRAPH_H
