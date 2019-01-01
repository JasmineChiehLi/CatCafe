#ifndef PRODUCER_H
#define PRODUCER_H

#include <unistd.h>
#include <pthread.h>

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsRectItem>

#include "store.h"
class Producer
{
private:
    Store* store;
public:
    Producer();
    Producer(Store* s);
    void* produce();
};

#endif // PRODUCER_H
