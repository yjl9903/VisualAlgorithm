#ifndef GRAPH_H
#define GRAPH_H

#include "canvas.h"
#include <cstring>

class Graph : public Container
{
private:
    int n, m;
    int G[100][100];
    int Gid[100][100];
    QVector<int> _val;

public:
    Graph()
    {
        mld.init();
        _circle.clear();
        _line.clear();
        n = m = 0;
        memset(G, 0, sizeof G);
        memset(Gid, -1, sizeof Gid);
    }
    int val(int i){return _val[i];}
    int size(){return n;}
    int sizeLine(){return m;}
    int edge(int x, int y){return G[x][y];}
    int edgeID(int x, int y){return Gid[x][y];}
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
        Gid[id.first][id.second] = m;
        return m++;
    }

//    void algorithm(QString, int);
};

#endif // GRAPH_H
