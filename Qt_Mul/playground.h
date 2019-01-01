#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <pthread.h>

#include "producer.h"
#include "consumer.h"

class Playground
        :public QGraphicsView
{
    Q_OBJECT
private:
    Store* store;
    Producer* producer;
    Consumer* consumer;
    QGraphicsScene* scene;
public:
    QGraphicsTextItem* conText;

    Playground();
    ~Playground();
    void play();
    static void *produce(void* param);
    static void *consume(void* param);

public slots:
    void storeNew();
};

#endif // PLAYGROUND_H
