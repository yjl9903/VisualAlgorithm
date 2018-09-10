#ifndef GRAPH_H
#define GRAPH_H

#include "canvas.h"
#include <cstring>
#include <queue>

class Graph : public Container
{
private:
    int n, m;
    int G[100][100];
    int Gid[100][100];
    QVector<int> _val;
    QVector<QPair<int,int>> _link;

public:
    Graph()
    {
        mld.init();
        _circle.clear();
        _line.clear();
        _link.clear();
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
        _link.append(id);
        G[id.first][id.second] = v;
        Gid[id.first][id.second] = m;
        return m++;
    }

    void del(int type)
    {
        if (type == 0){
            if (n == 0) return;
            _circle.pop_back();
            n--;
        }
        else if (type == 1){
            if (m == 0) return;
            QPair<int,int> x = _link.back();
            G[x.first][x.second] = 0;
            Gid[x.first][x.second] = -1;
            _link.pop_back();
            _line.pop_back();
            _val.pop_back();
            m--;
        }
    }

    void clear()
    {
        _circle.clear();
        _line.clear();
        _val.clear();
        _link.clear();
        n = m = 0;
        memset(G, 0, sizeof G);
        memset(Gid, -1, sizeof Gid);
    }
};

#endif // GRAPH_H
