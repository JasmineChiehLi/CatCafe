#ifndef CAT_H
#define CAT_H

#include <QObject>
#include <sys/types.h>
#include <sys/wait.h>

class Consumer;

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
    //gui-concerned signals
    void work(Cat* cat);
    void home(Cat* cat);

private:
    bool isFree;
    Consumer* consumer;
    pthread_t tid;
};

#endif // CAT_H
