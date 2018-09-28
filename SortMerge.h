#ifndef SORTMERGE_H
#define SORTMERGE_H

#include <QObject>

class SortMerge : public QObject {
    Q_OBJECT
public:
    SortMerge();
    ~SortMerge();

    QList<int> items;
    QList<int> left;
    QList<int> right;


    SortMerge *lSortLeft;
    SortMerge *lSortRight;
    QThread   *lThreadLeft;
    QThread   *lThreadRight;
    unsigned short mMaxThread;


//    static void sort(QList<int> &aItem);
    static void merge(QList<int> &items, QList<int> &left, QList<int> &right);

    int b1;

public slots:
    void sort();
    void bbbb1();






signals:
    void finished();


};

#endif // SORTMERGE_H
