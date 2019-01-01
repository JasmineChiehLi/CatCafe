#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QDebug>

#include <unistd.h>
#include <stdlib.h>

#define CAT_GAP 7
#define CAT_VAR 5

class Cat;
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
    pthread_t getTid();

    void* consume();

signals:
    void queueUp(Consumer* consumer);
    //加入排队买咖啡
    void wantCat(Consumer* consumer);
    void bye(Consumer* consumer);
    //delete

private:
    bool haveCafe;
    bool beingServed;
    int catTime;
    Cat* cat;
    pthread_t tid;
};

#endif // CONSUMER_H
