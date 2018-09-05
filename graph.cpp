#include "graph.h"
#include "drawwidget.h"

QListWidgetItem* setItem(QString str)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(str);
    item->setFont(getFont());
    item->setFlags(Qt::ItemIsEnabled);
    return item;
}

void drawWidget::setListWidget(QString str)
{
    list->clear();
    list->show();
    item[0] = setItem("function dfs(u):");
    item[1] = setItem("    for each neighbour v of u:");
    item[2] = setItem("        if v has not been visted:");
    item[3] = setItem("            dfs(v)");
    for (int i = 0; i < 4; i++)
        list->addItem(item[i]);

}

void drawWidget::algorithm(QString str, int begID)
{
    isRun = 1;
    repaint();
    setListWidget("");
    if (begID >= graph.size()) {
        isRun = 0; list->hide();
        return;
    }
    memset(vis, 0, sizeof vis);
    if (str == "dfs") dfs(begID);
    if (str == "bfs") bfs(begID);
    isRun = 0; list->hide();
}

void drawWidget::dfs(int u)
{
    Circle tot = graph.circle(u);
    vis[u] = 1;

    sleep(300);
    item[0]->setTextColor(Qt::red);
    item[3]->setTextColor(Qt::black);
    drawCircle(tot, QColor(154, 255, 154));
    sleep(500);


    for (int i = 0; i < graph.size(); i++){
        if (i == u || !graph.edge(u, i)) continue;

        item[0]->setTextColor(Qt::black);
        item[1]->setTextColor(Qt::red);

        drawLineAnimation(u, i, QColor(154, 255, 154));
        Circle v = graph.circle(i);
        drawCircle(v, QColor(154, 255, 154));
        drawCircle(tot, tot.color());

        sleep(500);

        item[1]->setTextColor(Qt::black);
        item[2]->setTextColor(Qt::red);

        cleanTemp();

        if (!vis[i]){
            sleep(500);
            item[2]->setTextColor(Qt::black);
            item[3]->setTextColor(Qt::red);
            sleep(500);
            dfs(i);
        }
        else {
            sleep(500);
            drawLine(u, i, Qt::gray, defaultLineSize + 1);
            drawCircle(v, v.color());
        }

        drawCircle(tot, QColor(154, 255, 154));
        item[1]->setTextColor(Qt::black);

        sleep(100);
    }

    sleep(500);
    drawCircle(tot, tot.color());
    sleep(500);
}

void drawWidget::bfs(int beg)
{

}
