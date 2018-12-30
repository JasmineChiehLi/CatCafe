#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <unistd.h>

#include <QDebug>

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
    pthread_t getTid();

    void* consume();

signals:
    void wantCat(Consumer* consumer);
    void finish(Consumer* consumer);

private:
    bool haveCafe;
    Cat* cat;
    pthread_t tid;
};

#endif // CONSUMER_H
