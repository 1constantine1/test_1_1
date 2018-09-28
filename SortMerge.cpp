#include "SortMerge.h"

#include <QThread>
#include <QtConcurrent/QtConcurrentMap>
#include <QDebug>

SortMerge::SortMerge() {
 b1 = 0;

}

SortMerge::~SortMerge() {

}

void SortMerge::sort()
{
    b1 = 0;

    qDebug() << items;

    if (items.length() <= 1)
    {
        qDebug() << "finished ";
        emit finished();
        return;
    }

    int leftSize = items.length() / 2;
    int rightSize = items.length() - leftSize;


    for (int i = 0; i < items.length(); i++) {
        if (i < leftSize) {
            left.push_back(items[i]);
        } else {
            right.push_back(items[i]);
        }
    }

    lSortLeft    = new SortMerge();
    lSortRight   = new SortMerge();
    lThreadLeft  = new QThread;
    lThreadRight = new QThread;
    lSortLeft->items  = left;
    lSortRight->items = right;
    lSortLeft->mMaxThread = static_cast<int>(mMaxThread - 2 / 2);
    lSortRight->mMaxThread = static_cast<int>(mMaxThread - 2 / 2);
    lSortLeft->moveToThread(lThreadLeft);
    lSortRight->moveToThread(lThreadRight);
    connect(lThreadLeft,  SIGNAL(started()), lSortLeft,  SLOT(sort()));
    connect(lThreadRight, SIGNAL(started()), lSortRight, SLOT(sort()));
   connect(lSortLeft, SIGNAL(finished()), lThreadLeft, SLOT(quit()));
   connect(lSortLeft, SIGNAL(finished()), this, SLOT(bbbb1()));
   connect(lSortRight, SIGNAL(finished()), this, SLOT(bbbb1()));
//    connect(lThreadLeft, SIGNAL(finished()), lSortLeft,   SLOT(deleteLater()));
//    connect(lSortLeft, SIGNAL(finished()), lThreadLeft, SLOT(deleteLater()));
    connect(lSortRight, SIGNAL(finished()), lThreadRight, SLOT(quit()));
//    connect(lThreadRight, SIGNAL(finished()), lSortRight,   SLOT(deleteLater()));
//    connect(lSortRight, SIGNAL(finished()), lThreadRight, SLOT(deleteLater()));


    lThreadLeft->start();
    lThreadRight->start();

//    this->sort(left);
//    this->sort(right);
//    merge(items, left, right);
    qDebug() << "Result = " << items;
}

void SortMerge::bbbb1() {
    b1++;
    qDebug() << "b1 = " << b1;
    if (b1 == 2) {
        qDebug() << " 3 ";
        this->merge(items, lSortLeft->items, lSortRight->items);
        qDebug() << " 4 ";
        qDebug() << " 5 ";
        qDebug() << items;
        emit finished();
    }
}

//void SortMerge::sort(QList<int> &aItem)
//{
//    if (aItem.length() <= 1) {
//        return;
//    }

//    int leftSize = aItem.length() / 2;
//    int rightSize = aItem.length() - leftSize;
//    QList<int> left;
//    QList<int> right;

//    for (int i = 0; i < aItem.length(); i++) {
//        if (i < leftSize) {
//            left.push_back(aItem[i]);
//        } else {
//            right.push_back(aItem[i]);
//        }
//    }

//    QList<QList<int>> a1;
//    a1.push_back(left);
//    a1.push_back(right);
//    QFuture<void> future = QtConcurrent::map(a1, sort); // map(a1, std::bind(&SortMerge::sort, this, std::placeholders::_1));
//    future.waitForFinished();

//    merge(aItem, left, right);
//}

void SortMerge::merge(QList<int> &items, QList<int> &left, QList<int> &right)
{
    qDebug() << "1";

    int leftIndex    = 0;
    int rightIndex   = 0;
    int targetIndex  = 0;
    int remaining = left.length() + right.length();
    while(remaining > 0)
    {
        if (leftIndex >= left.length()) {
            items[targetIndex] = right[rightIndex++];
        } else if (rightIndex >= right.length()) {
            items[targetIndex] = left[leftIndex++];
        } else if (left[leftIndex] < right[rightIndex]) {
            items[targetIndex] = left[leftIndex++];
        } else {
            items[targetIndex] = right[rightIndex++];
        }

        targetIndex++;
        remaining--;
    }
}
