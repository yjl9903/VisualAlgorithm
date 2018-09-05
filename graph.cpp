#include "graph.h"
#include "drawwidget.h"


void drawWidget::algorithm(QString str, int begID)
{
    if (begID >= graph.size()) return;
    memset(vis, 0, sizeof vis);
    if (str == "dfs") dfs(begID);
}

void drawWidget::dfs(int u)
{
    Circle tot = graph.circle(u);
    vis[u] = 1;

    sleep(100);
    drawCircle(tot, QColor(154, 255, 154));
    sleep(500);

    for (int i = 0; i < graph.size(); i++){
        if (i == u || !graph.edge(u, i)) continue;

        drawLineAnimation(graph.line(graph.edgeID(u, i)), QColor(154, 255, 154));
        Circle v = graph.circle(i);
        drawCircle(v, QColor(154, 255, 154));
        drawCircle(tot, tot.color());

        sleep(500);

        pixTemp->fill(QColor(0, 0, 0, 0));
        update();

        if (!vis[i]){
            dfs(i);
        }
        else {
            drawCircle(v, v.color());
        }

        drawCircle(tot, QColor(154, 255, 154));

        sleep(100);
    }

    sleep(500);
    drawCircle(tot, tot.color());
    sleep(500);
}
