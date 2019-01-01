#ifndef CONSUMER_H
#define CONSUMER_H

#include <pthread.h>
#include <QGraphicsTextItem>
#include <unistd.h>
#include "store.h"

class Consumer
        :public QObject
{
    //Q_OBJECT
private:
    Store* store;
    int N;

public:
    QGraphicsTextItem* text;

    Consumer();
    ~Consumer();
    Consumer(Store* s);
    void* consume();
    int getN();
};

#endif // CONSUMER_H
