#include "drawwidget.h"
#include <string>

drawWidget::drawWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1440, 840);
    setAutoFillBackground(true);
    setPalette(QPalette(backgroundColor));

    list = new QListWidget(this);
    list->setGeometry(950, 560, 500, 400);
    list->setFocusPolicy(Qt::NoFocus);
    list->hide();

    pixTemp = new QPixmap(size());
    pixTemp->fill(QColor(0, 0, 0, 0));
    pixLine = new QPixmap(size());
    pixLine->fill(QColor(0, 0, 0, 0));
    pixCircle = new QPixmap(size());
    pixCircle->fill(QColor(0, 0, 0, 0));

    mode = 0;
    isShowEdgeValue = 0;
    isRun = 0;
    isShowBoard = 1;
}

drawWidget::~drawWidget()
{
    delete pixTemp;
    delete pixLine;
    delete pixCircle;
}

void drawWidget::clear()
{
    graph.clear();
    ope.clear();
//    QPixmap *p = new QPixmap(size());
//    p->fill(QColor(0, 0, 0, 0));
    pixCircle->fill(QColor(0, 0, 0, 0));
    pixLine->fill(QColor(0, 0, 0, 0));
    update();
}

void drawWidget::cleanTemp()
{
    pixTemp->fill(QColor(0, 0, 0, 0));
    update();
}

void drawWidget::repaint()
{
//    qDebug() << graph.size() << graph.sizeLine();
    pixTemp->fill(QColor(0, 0, 0, 0));
    pixCircle->fill(QColor(0, 0, 0, 0));
    pixLine->fill(QColor(0, 0, 0, 0));
    update();
    for (int i = 0; i < graph.size(); i++){
        Circle t = graph.circle(i);
        drawCircle(t, t.color());
    }

    for (int i = 0; i < graph.sizeLine(); i++){
        Line t = graph.line(i);
        drawLine(i, t.begin(), t.end(), t.color());
    }
}

void drawWidget::loadGraph(int id)
{
    if (isRun) return;
    clear();
    std::string str = "E:\\Graph\\" + std::to_string(id) + ".txt";
    freopen(str.c_str(), "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0, x, y; i < n; i++){
        scanf("%d%d", &x, &y);
        graph.insert(QPoint(x, y));
    }
    for (int i = 0, x, y; i < m; i++){
        scanf("%d%d", &x, &y);
        graph.link(graph.circle(x).pos(), graph.circle(y).pos());
    }
    fclose(stdin);
    ope.append(2);
    repaint();
}

bool drawWidget::setShowEdgeValue()
{
    if (isRun) return false;
    isShowEdgeValue ^= 1;
    repaint();
    return true;
}

bool drawWidget::setShowBoard()
{
    isShowBoard ^= 1;
//    if (isShowBoard) list->show();
//    else list->hide();
    if (!isShowBoard) list->hide();
    return true;
}

bool drawWidget::setMode(int x)
{
    if (isRun) return false;
    mode = x;
    return true;
//    if (mode == 2){
//        drawLineAnimation(graph.line(0), QColor(255, 185, 15));

//        QEventLoop loop;
//        QTimer::singleShot(200, &loop, SLOT(quit()));
//        loop.exec();

//        Line x = graph.line(0);
//        drawLine(0, x.begin(), x.end(), x.color());
//    }
}

void drawWidget::paintEvent(QPaintEvent *e){
//    qDebug() << "paint";
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pixLine);
    painter.drawPixmap(QPoint(0, 0), *pixTemp);
    painter.drawPixmap(QPoint(0, 0), *pixCircle);
}

void drawWidget::mousePressEvent(QMouseEvent *e)
{
    beginPos = e->pos();
    if (mode == 1){
        isDrawLine = 0;
        int id = graph.getCircleIndex(beginPos);
        if (id == -1) return;
        beginPos = graph.circle(id).pos();

        beginCircle = graph.circle(id);
        drawCircle(beginCircle, QColor(255, 99, 71));

        isDrawLine = 1;
    }
}

void drawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mode == 1 && isDrawLine){
        drawLine(-1, beginPos, e->pos(), QColor(255, 99, 71));
    }
}

void drawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    endPos = e->pos();
    if (mode == 0){
        if (e->pos().x() + defaultSize >= this->width()) return;
        if (e->pos().x() - defaultSize <= 0) return;
        if (e->pos().y() + defaultSize >= this->height()) return;
        if (e->pos().y() - defaultSize <= 0) return;

        int id = graph.insert(e->pos());
        if (id == -1)
            return;
        Circle x = graph.circle(id);
        ope.append(0);
        drawCircle(x, x.color());
    }
    if (mode == 1){
        if (isDrawLine){
            drawCircle(beginCircle, beginCircle.color());
        }
        int id = graph.link(beginPos, endPos);
        if (id == -1){
            pixTemp->fill(QColor(0, 0, 0, 0));
            update();
            return;
        }
        Line x = graph.line(id);
        ope.append(1);
        drawLine(id, x.begin(), x.end());
    }
}

void drawWidget::withdraw()
{
//    qDebug() << ope.size();
    if (ope.size() == 0) return;
    if (ope.back() == 2) {
        clear();
        return;
    }
    graph.del(ope.back());
    ope.pop_back();
//    qDebug() << ope.size();
    repaint();
}
