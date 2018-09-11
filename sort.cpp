#include "sortwidget.h"

void sortWidget::setSpeed(int x)
{
    speed = (100 - x);
}

void sortWidget::setListWidget(QString str)
{
    list->clear();
    if(isShowBoard) list->show();
    if (str == "bubble"){
        list->setGeometry(950, 560, 500, 400);
        item[0] = setItem("function bubbleSort(A, n):");
        item[1] = setItem("    for i = 1...n - 1:");
        item[2] = setItem("        for j = 1...n - i - 1");
        item[3] = setItem("            if A[j] > A[j + 1]:");
        item[4] = setItem("                swap(A[j], A[j + 1])");
        for (int i = 0; i < 5; i++)
            list->addItem(item[i]);
    }
    else if (str == "quick"){
        list->setGeometry(950, 560, 500, 400);
        item[0] = setItem("function quickSort(A, n, l, r):");
        item[1] = setItem("    for i = 1...n - 1:");
        item[2] = setItem("        for j = 1...n - i - 1");
        item[3] = setItem("            if A[j] > A[j + 1]:");
        item[4] = setItem("                swap(A[j], A[j + 1])");
        for (int i = 0; i < 5; i++)
            list->addItem(item[i]);
    }
}

void sortWidget::algorithm(QString str)
{
    isRun = 1;
    setListWidget(str);

    if (str == "bubble") bubbleSort();
    else if (str == "quick") quickSort(1, arr->size());

    isRun = 0;
    list->hide();
}

void sortWidget::bubbleSort()
{
    item[0]->setTextColor(Qt::red);
    sleep(speed * 20);
    item[0]->setTextColor(Qt::black);

    for (int i = 0; i < arr->size(); i++){

        item[1]->setTextColor(Qt::red);
        sleep(speed * 20);
        item[1]->setTextColor(Qt::black);
        sleep(speed * 10);

        for (int j = 0; j < arr->size() - i - 1; j++){

            sleep(speed * 5);
            item[2]->setTextColor(Qt::red);

            pixTemp1->fill(QColor(0, 0, 0, 0));
            pixTemp2->fill(QColor(0, 0, 0, 0));
            update();

            sleep(speed * 10);
            item[2]->setTextColor(Qt::black);
            item[3]->setTextColor(Qt::red);
            drawRect(j, QColor(255, 185, 15), 1);
            drawRect(j + 1, QColor(255, 185, 15), 2);
            sleep(speed * 10);

            item[3]->setTextColor(Qt::black);

            if (arr->val(j) > arr->val(j + 1)){
                item[4]->setTextColor(Qt::red);
                swapRect(j, j + 1);
                item[4]->setTextColor(Qt::black);
            }
            else sleep(speed * 5);

            sleep(speed * 5);
        }
    }

    pixTemp1->fill(QColor(0, 0, 0, 0));
    pixTemp2->fill(QColor(0, 0, 0, 0));
    update();
}

void sortWidget::quickSort(int l, int r)
{

}
