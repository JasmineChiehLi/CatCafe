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
    void setConsumer(Consumer* consumer);

    void* play();

signals:
    void goToWork();
    void goHome();

private:
    bool isFree;
    Consumer* consumer;

};

#endif // CAT_H
