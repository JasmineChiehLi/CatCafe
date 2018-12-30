#ifndef CAT_H
#define CAT_H

#include <QObject>
#include "consumer.h"

class Cat
        :public QObject
{
    Q_OBJECT
public:
    Cat();
    bool getIsFree();
    void setIsFree(bool isFreeNow);
    void setTid(pthread_t tid);
    pthread_t getTid();
    void setConsumer(Consumer* consumer);

    void* Mew();

signals:
    void goToWork(Cat* cat);
    void goHome(Cat* cat);

private:
    bool isFree;
    Consumer* consumer;
    pthread_t tid;
};

#endif // CAT_H
