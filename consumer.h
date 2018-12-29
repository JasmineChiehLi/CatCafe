#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Cat;
//pre-declaration

class Consumer
        :public QObject
{
    Q_OBJECT
public:
    Consumer();
    bool getHaveCafe();
    void setCat(Cat* cat);

    void* consume();

signals:
    void wantCat();

private:
    bool haveCafe;
    Cat* cat;
};

#endif // CONSUMER_H
