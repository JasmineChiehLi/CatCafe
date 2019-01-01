#ifndef STORE_H
#define STORE_H

#define SIZE 128

#include <pthread.h>
#include <QGraphicsTextItem>
#include <QDebug>

class Store
        :public QObject
{
    Q_OBJECT
private:
    int num[SIZE];
    int length;

signals:
    void storeUpdate();

public:
    QGraphicsTextItem* text;
    pthread_mutex_t busy;
    pthread_cond_t cond;

    Store();
    ~Store();
    void setNum(int pos, int N);
    int getNum(int pos);
    int getLength();
};

#endif // STORE_H
