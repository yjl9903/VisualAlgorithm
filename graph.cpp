#include "graph.h"
#include "drawwidget.h"


void drawWidget::algorithm(QString str, int begID)
{
    isRun = 1;
    repaint();
    if (begID >= graph.size()) return;
    memset(vis, 0, sizeof vis);
    if (str == "dfs") dfs(begID);
    if (str == "bfs") bfs(begID);
    isRun = 0;
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

        drawLineAnimation(u, i, QColor(154, 255, 154));
        Circle v = graph.circle(i);
        drawCircle(v, QColor(154, 255, 154));
        drawCircle(tot, tot.color());

        sleep(500);

        cleanTemp();

        if (!vis[i]){
            dfs(i);
        }
        else {
            drawLine(u, i, Qt::gray, defaultLineSize + 1);
            drawCircle(v, v.color());
        }

        drawCircle(tot, QColor(154, 255, 154));

        sleep(100);
    }

    sleep(500);
    drawCircle(tot, tot.color());
    sleep(500);
}

void drawWidget::bfs(int beg)
{

}
