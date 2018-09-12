#include "sortwidget.h"

sortWidget::sortWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1440, 840);
    setAutoFillBackground(true);
    setPalette(QPalette(backgroundColor));

    arr = new Array;

    pixTemp1 = new QPixmap(size());
    pixTemp1->fill(QColor(0, 0, 0, 0));
    pixTemp2 = new QPixmap(size());
    pixTemp2->fill(QColor(0, 0, 0, 0));
    pix = new QPixmap(size());
    pix->fill(QColor(0, 0, 0, 0));

    list = new QListWidget(this);
    list->setGeometry(950, 560, 500, 400);
    list->setFocusPolicy(Qt::NoFocus);
    list->hide();

    isRun = 0;
    isShowBoard = 1;
    speed = 50;
    left = defaultLeft;
    buttom = defaultButtom;
}

sortWidget::~sortWidget()
{
    delete arr;
}

void sortWidget::clear()
{
    left = defaultLeft;
    buttom = defaultButtom;

    arr->clear();

    pix->fill(QColor(0, 0, 0, 0));

    update();
}

void sortWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.drawPixmap(QPoint(0, 0), *pixTemp1);
    painter.drawPixmap(QPoint(0, 0), *pixTemp2);
}

void sortWidget::drawRectText(QRect pos, QString str, QPainter *painter)
{
    pos.setY(pos.y() + 5);
    painter->setFont(getFont());
    painter->setPen(QPen(Qt::black));
    painter->drawText(pos, Qt::AlignCenter, str);
}

void sortWidget::drawRect(int id, QColor color, int isTemp)
{
    QPainter *painter = new QPainter(this);

    if (isTemp == 1) painter->begin(pixTemp1);
    else if (isTemp == 2) painter->begin(pixTemp2);
    else painter->begin(pix);

    painter->setPen(QPen(color));
    painter->setBrush(QBrush(color));
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect x = arr->rect(id).rect();
//    qDebug() << arr->rect(id).left();
    painter->drawRect(x);

    drawRectText(QRect(x.bottomLeft(), QSize(defaultUnitWidth, defaultUnitHeight)), QString::number(arr->val(id)), painter);
    // drawText(x.pos(), QString::number(x.id()), *painter);

    painter->end();
    update();
}

void sortWidget::swapRect(int a, int b)
{
    if (a == b) return;
    int x1 = arr->rect(a).left(), x2 = arr->rect(b).left();
    if (x1 > x2){
        std::swap(x1, x2);
        std::swap(a, b);
    }
//    drawRect(a, backgroundColor);
//    drawRect(b, backgroundColor);
    repaint(a, b);

    int len = x2 - x1;

//    for (int i = x1, j = x2; i <= x2, j >= x1; i++, j--){
//    speed = 50;
    for (int i = 0; i <= 60; i++){
        sleep(speed / 5);
        arr->rect(a).moveTo(x1 + len * i / 60);
        arr->rect(b).moveTo(x2 - len * i / 60);
//        qDebug() << arr->rect(a).left() << arr->rect(b).left();
        pixTemp1->fill(QColor(0, 0, 0, 0));
        pixTemp2->fill(QColor(0, 0, 0, 0));
        update();
        drawRect(a, QColor(154, 255, 154), 1);
        drawRect(b, QColor(154, 255, 154), 2);
    }

    pixTemp1->fill(QColor(0, 0, 0, 0));
    pixTemp2->fill(QColor(0, 0, 0, 0));

    repaint();

    arr->swap(a, b);
}

void sortWidget::repaint(int a, int b)
{
    pix->fill(QColor(0, 0, 0, 0));
    for (int i = 0; i < arr->size(); i++){
        if (i == a || i == b) continue;
        drawRect(i, arr->rect(i).color());
    }
    update();
}

void sortWidget::withdraw()
{
    if (arr->size() == 0) return;
    arr->del();
    left -= defaultUnitWidth + 10;
    repaint();
}

void sortWidget::loadArray(int id)
{
    clear();
    std::string str = basePath + "Array\\" + std::to_string(id) + ".txt";
    freopen(str.c_str(), "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0, x; i < n; i++){
        scanf("%d", &x);
        arr->insert(QPoint(left, buttom), x);
        left += defaultUnitWidth + 10;
    }
    fclose(stdin);

    repaint();
}

void sortWidget::addRect(int x)
{
    int id = arr->insert(QPoint(left, buttom), x);
    if (id == -1) return;
    left += defaultUnitWidth + 10;
    drawRect(id, arr->rect(id).color());
//    repaint();
}

bool sortWidget::setShowBoard()
{
    isShowBoard ^= 1;
//    if (isShowBoard) list->show();
//    else list->hide();
    if (!isShowBoard) list->hide();
    else if (isRun) list->show();
    return true;
}
