#include "sortwidget.h"

void sortWidget::setSpeed(int x)
{
    speed = (100 - x);
}

void sortWidget::setListWidget(QString str, int t1 = 0, int t2 = 0)
{
    QString str1 = QString::number(t1), str2 = QString::number(t2);
    list->clear();
    if(isShowBoard) list->show();
    if (str == "bubble"){
        list->setGeometry(950, 560, 500, 400);
        item[0] = setItem("function bubbleSort(A, n):");
        item[1] = setItem("    for i = 1...n - 1:");
        item[2] = setItem("        for j = 1...n - i - 1:");
        item[3] = setItem("            if A[j] > A[j + 1]:");
        item[4] = setItem("                swap(A[j], A[j + 1])");
        item[5] = setItem("Compare " + str1 + " times");
        item[6] = setItem("Swap " + str2 + " times");
        list->addItem(item[5]);
        list->addItem(item[6]);
        for (int i = 0; i < 5; i++)
            list->addItem(item[i]);
    }
    else if (str == "select"){
        list->setGeometry(950, 460, 500, 500);
        item[0] = setItem("function selectSort(A, n):");
        item[1] = setItem("    for i = 1...n:");
        item[2] = setItem("        min = a[i], pos = i");
        item[3] = setItem("        for j = i + 1...n - 1:");
        item[4] = setItem("            if A[j] > min:");
        item[5] = setItem("                min = a[j], pos = j");
        item[6] = setItem("        swap(a[i], a[pos])");
        item[7] = setItem("Compare " + str1 + " times");
        item[8] = setItem("Swap " + str2 + " times");
        list->addItem(item[7]);
        list->addItem(item[8]);
        for (int i = 0; i < 7; i++)
            list->addItem(item[i]);
    }
    else if (str == "quick"){
        list->setGeometry(950, 370, 500, 590);
        item[0] = setItem("function quickSort(A, l, r):");
        item[1] = setItem("    if l >= r: return");
        item[2] = setItem("    x = A[r], i = l - 1");
        item[3] = setItem("    for j = l...r - 1:");
        item[4] = setItem("        if A[j] <= x:");
        item[5] = setItem("            i = i + 1");
        item[6] = setItem("            swap(A[i], A[j])");
        item[7] = setItem("    swap(A[i + 1], A[r])");
        item[8] = setItem("    quickSort(A, l, i)");
        item[9] = setItem("    quickSort(A, i + 2, r)");
        item[10] = setItem("Compare " + str1 + " times");
        item[11] = setItem("Swap " + str2 + " times");
        list->addItem(item[10]);
        list->addItem(item[11]);
        for (int i = 0; i < 10; i++)
            list->addItem(item[i]);
    }
}

void sortWidget::algorithm(QString str)
{
    isRun = 1; cmpCnt = swapCnt = 0;
    running = str;
    setListWidget(str);

    for (int i = 0; i < arr->size(); i++) saveArr.append(arr->val(i));

    if (str == "bubble") bubbleSort();
    else if (str == "select") selectSort();
    else if (str == "quick") quickSort(0, arr->size() - 1);

    isRun = 0;
//    list->hide();
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

            setListWidget(running, ++cmpCnt, swapCnt);

            if (arr->val(j) > arr->val(j + 1)){
                setListWidget(running, cmpCnt, ++swapCnt);
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

void sortWidget::selectSort()
{
    item[0]->setTextColor(Qt::red);
    sleep(speed * 20);
    item[0]->setTextColor(Qt::black);

    for (int i = 0; i < arr->size() - 1; i++){

        item[1]->setTextColor(Qt::red);
        sleep(speed * 20);
        item[1]->setTextColor(Qt::black);
        drawRect(i, QColor(255, 0, 0), 1);
        sleep(speed * 10);

        int mi = arr->val(i), pos = i;

        for (int j = i + 1; j < arr->size(); j++){

            sleep(speed * 5);
            item[2]->setTextColor(Qt::red);

            pixTemp1->fill(QColor(0, 0, 0, 0));
            pixTemp2->fill(QColor(0, 0, 0, 0));
            update();

            sleep(speed * 10);
            item[2]->setTextColor(Qt::black);
            item[3]->setTextColor(Qt::red);
            drawRect(j, QColor(255, 185, 15), 1);
//            drawRect(j + 1, QColor(255, 185, 15), 2);
            sleep(speed * 10);

            item[3]->setTextColor(Qt::black);
            setListWidget(running, ++cmpCnt, swapCnt);

            if (arr->val(j) < mi){
//                item[4]->setTextColor(Qt::red);
//                swapRect(i, j);
//                item[4]->setTextColor(Qt::black);
                mi = arr->val(j); pos = j;
            }
//            else sleep(speed * 5);

            sleep(speed * 5);
        }

        setListWidget(running, cmpCnt, ++swapCnt);
        item[4]->setTextColor(Qt::red);
        if (i != pos) swapRect(i, pos);
        item[4]->setTextColor(Qt::black);

        sleep(speed * 5);
    }

    pixTemp1->fill(QColor(0, 0, 0, 0));
    pixTemp2->fill(QColor(0, 0, 0, 0));
    update();
}

void sortWidget::quickSort(int l, int r)
{
    if (l >= r) return;

    sleep(speed * 10);
    item[8]->setTextColor(Qt::black);
    item[9]->setTextColor(Qt::black);
    item[0]->setTextColor(Qt::red);
    QColor cr = arr->rect(r).color();
//    arr->rect(l).setColor(QColor(255, 0, 0));
    arr->rect(r).setColor(QColor(255, 0, 0));
    drawRect(l, QColor(255, 0, 0));
    drawRect(r, QColor(255, 0, 0));

    sleep(speed * 20);

    item[0]->setTextColor(Qt::black);
    drawRect(l, QColor(255, 185, 15), 1);

    int x = arr->val(r);
    int i = l - 1;

    QVector<QColor> v;

    for (int j = l; j < r; j++){

        item[3]->setTextColor(Qt::red);
        sleep(speed * 10);
        pixTemp1->fill(QColor(0, 0, 0, 0));
        drawRect(j, QColor(255, 185, 15), 1);
        sleep(speed * 5);

        item[3]->setTextColor(Qt::black);
        setListWidget(running, ++cmpCnt, swapCnt);
        item[4]->setTextColor(Qt::red);

        if (arr->val(j) <= x){

            sleep(speed * 5);
            setListWidget(running, cmpCnt, ++swapCnt);
            item[4]->setTextColor(Qt::black);
            item[6]->setTextColor(Qt::red);
            i++;
            swapRect(i, j);

            drawRect(i, QColor(0, 255, 255));
            v.append(arr->rect(i).color());
            arr->rect(i).setColor(QColor(0, 255, 255));

            item[6]->setTextColor(Qt::black);
        }
//        else drawRect(j, arr->rect(j).color());

        item[4]->setTextColor(Qt::black);
        sleep(speed * 5);
    }

    item[7]->setTextColor(Qt::red);
    swapRect(i + 1, r);

    for (int j = i; j >= l; j--){
        arr->rect(j).setColor(v.back());
        v.pop_back();
    }
//    arr->rect(i + 1).setColor(cl);
    arr->rect(i + 1).setColor(cr);

//    qDebug() << arr->rect(l).color();
//    qDebug() << arr->rect(r).color();

    sleep(speed * 10);

    pixTemp1->fill(QColor(0, 0, 0, 0));
    repaint();

    item[7]->setTextColor(Qt::black);
    item[8]->setTextColor(Qt::red);

    quickSort(l, i);
    item[8]->setTextColor(Qt::black);

    item[9]->setTextColor(Qt::red);
    quickSort(i + 2, r);
    item[9]->setTextColor(Qt::black);
}
