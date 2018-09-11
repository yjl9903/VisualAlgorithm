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

void drawWidget::setListWidget(QString str, QString queue = "")
{
    list->clear();
    if(isShowBoard) list->show();
    if (str == "dfs"){
        list->setGeometry(950, 560, 500, 400);
        item[0] = setItem("function dfs(u):");
        item[1] = setItem("    for each neighbour v of u:");
        item[2] = setItem("        if v has not been visted:");
        item[3] = setItem("            dfs(v)");
        for (int i = 0; i < 4; i++)
            list->addItem(item[i]);
    }
    else if (str == "bfs"){
        list->setGeometry(850, 560, 600, 400);
        item[0] = setItem("queue q = { " + queue + " }");
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
    if (begID < 0 || begID > graph.size()) return;
    isRun = 1;
    repaint();
//    setListWidget(str, begID);
    if (begID >= graph.size()) {
        isRun = 0; list->hide();
        return;
    }
    memset(vis, 0, sizeof vis);
    if (str == "dfs") setListWidget(str), dfs(begID);
    if (str == "bfs") setListWidget(str, QString::number(begID)), bfs(begID);
    isRun = 0;
    list->hide();
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
            item[2]->setTextColor(Qt::black);
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

QString getQueue(QVector<int> v)
{
    QString s = "";
    if (v.empty()) return s;
    int last = v.back(); v.pop_back();
    for (auto &x : v){
        s += QString::number(x) + ", ";
    }
    s += QString::number(last);
    return s;
}

void drawWidget::bfs(int beg)
{
//    drawCircle(graph.circle(beg), QColor(154, 255, 154));
    std::queue<int> q; q.push(beg); vis[beg] = 1;
    QVector<int> vec; vec.append(beg);

    item[1]->setTextColor(Qt::red);
    sleep(speed);
    item[1]->setTextColor(Qt::black);

    while (!q.empty()){
        item[2]->setTextColor(Qt::red);
        sleep(speed);

        int u = q.front(); q.pop(); vec.pop_front();
        setListWidget("bfs", getQueue(vec));
        Circle tot = graph.circle(u);

        item[2]->setTextColor(Qt::black);
        item[3]->setTextColor(Qt::red);
        drawCircle(tot, QColor(154, 255, 154));
        sleep(speed);

        for (int i = 0; i < graph.size(); i++){
            if (i == u || !graph.edge(u, i)) continue;

            item[3]->setTextColor(Qt::black);
            item[4]->setTextColor(Qt::red);

            drawLineAnimation(u, i, QColor(154, 255, 154));
            Circle v = graph.circle(i);
            drawCircle(v, QColor(154, 255, 154));
            drawCircle(tot, tot.color());
            sleep(speed);

            cleanTemp();

            item[4]->setTextColor(Qt::black);
            item[5]->setTextColor(Qt::red);
            sleep(speed);

            if (!vis[i]){
                vec.append(i);
                setListWidget("bfs", getQueue(vec));
                item[5]->setTextColor(Qt::black);
                item[6]->setTextColor(Qt::red);
                sleep(speed);

                vis[i] = 1;
                q.push(i);
            }
            else {
                item[5]->setTextColor(Qt::black);
                sleep(speed);
                drawLine(u, i, Qt::gray, defaultLineSize + 1);
            }

            drawCircle(v, v.color());
            drawCircle(tot, QColor(154, 255, 154));
            item[6]->setTextColor(Qt::black);
            sleep(speed / 3);
        }

        sleep(speed);
        item[3]->setTextColor(Qt::black);
        drawCircle(tot, tot.color());
        sleep(speed);
    }
}
