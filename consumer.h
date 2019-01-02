#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QDebug>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <QGraphicsPixmapItem>

#include "cat.h"

#define CAT_GAP 10
#define CAT_VAR 5


//pre-declaration

class Consumer
        :public QObject
{
    Q_OBJECT
public:
    Consumer();
    bool getHaveCafe();
    void setHaveCafe(bool nowHaveCafe);
    Cat* getCat();
    void setCat(Cat* cat);
    void setTid(pthread_t tid);
    void setBeingServed(bool nowServed);
    void setIsRegistered(bool registered);
    bool getIsRegistered();
    pthread_t getTid();
    QGraphicsPixmapItem* getImage();

    void* consume();

signals:
    void wantCat(Consumer* consumer);
    void bye(Consumer* consumer);
    //delete

    void queueUp(Consumer* consumer);

    //gui-concerned signals
    void waitCat(Consumer* consumer);
    void cating(Consumer* consumer, Cat* cat);

private:
    bool haveCafe;
    bool beingServed;
    bool isRegistered;
    int catTime;
    Cat* cat;
    pthread_t tid;
    QGraphicsPixmapItem* image;
};

#endif // CONSUMER_H
