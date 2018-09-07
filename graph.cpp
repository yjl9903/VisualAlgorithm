#include "graph.h"
#include "drawwidget.h"

void drawWidget::setSpeed(int v)
{
//    qDebug() << v;
    speed = (100 - v) * 10;
}

QListWidgetItem* setItem(QString str)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(str);
    item->setFont(getFont());
    item->setFlags(Qt::ItemIsEnabled);
    return item;
}

void drawWidget::setListWidget(QString str, int beg = 0)
{
    list->clear();
    list->show();
    if (str == "dfs"){
        item[0] = setItem("function dfs(u):");
        item[1] = setItem("    for each neighbour v of u:");
        item[2] = setItem("        if v has not been visted:");
        item[3] = setItem("            dfs(v)");
        for (int i = 0; i < 4; i++)
            list->addItem(item[i]);
    }
    if (str == "bfs"){
        item[0] = setItem("queue q = {" + QString::number(beg) + "}");
        item[1] = setItem("function bfs():");
        item[2] = setItem("    while q.empty() == false:");
        item[3] = setItem("        u = q.front(), q.pop()");
        item[4] = setItem("        for each nerighbour v of u:");
        item[5] = setItem("            if v has not been visted:");
        item[6] = setItem("                q.push(v)");
        for (int i = 0; i < 7; i++)
            list->addItem(item[i]);
    }
}

void drawWidget::algorithm(QString str, int begID)
{
    isRun = 1;
    repaint();
    setListWidget(str, begID);
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

//    sleep(300);
    item[0]->setTextColor(Qt::red);
    item[3]->setTextColor(Qt::black);
    drawCircle(tot, QColor(154, 255, 154));
    sleep(speed);


    for (int i = 0; i < graph.size(); i++){
        if (i == u || !graph.edge(u, i)) continue;

        item[0]->setTextColor(Qt::black);
        item[1]->setTextColor(Qt::red);

        drawLineAnimation(u, i, QColor(154, 255, 154));
        Circle v = graph.circle(i);
        drawCircle(v, QColor(154, 255, 154));
        drawCircle(tot, tot.color());

        sleep(speed);

        item[1]->setTextColor(Qt::black);
        item[2]->setTextColor(Qt::red);

        cleanTemp();

        if (!vis[i]){
            sleep(speed);
            item[2]->setTextColor(Qt::black);
            item[3]->setTextColor(Qt::red);
            sleep(speed);
            dfs(i);
        }
        else {
            sleep(speed);
            drawLine(u, i, Qt::gray, defaultLineSize + 1);
            drawCircle(v, v.color());
        }

        drawCircle(tot, QColor(154, 255, 154));
        item[1]->setTextColor(Qt::black);

        sleep(speed / 5);
    }

    sleep(speed);
    drawCircle(tot, tot.color());
    sleep(speed);
}

void drawWidget::bfs(int beg)
{
//    drawCircle(graph.circle(beg), QColor(154, 255, 154));
    std::queue<int> q; q.push(beg); vis[beg] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        Circle tot = graph.circle(u);
        drawCircle(tot, QColor(154, 255, 154));
        sleep(speed);

        for (int i = 0; i < graph.size(); i++){
            if (i == u || !graph.edge(u, i)) continue;

            drawLineAnimation(u, i, QColor(154, 255, 154));
            Circle v = graph.circle(i);
            drawCircle(v, QColor(154, 255, 154));
            drawCircle(tot, tot.color());
            sleep(speed);

            cleanTemp();

            if (!vis[i]){
                sleep(speed);
                q.push(i);
            }
            else {
                sleep(speed);
                drawLine(u, i, Qt::gray, defaultLineSize + 1);

            }

            drawCircle(v, v.color());
            drawCircle(tot, QColor(154, 255, 154));

            sleep(speed / 5);
        }

        sleep(speed);
        drawCircle(tot, tot.color());
        sleep(speed);
    }
}
