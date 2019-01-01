#ifndef ROOT_H
#define ROOT_H

#include <QObject>
#include <QQueue>

#include "consumer.h"
#include "cat.h"

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include <time.h>
#include <stdlib.h>

#define MAX_CON_NUM 128
#define MAX_CAT_NUM 6

#define MIN_CON_GAP 2
#define CON_VAR 2

class GUI;
class Employee;

class Root
        :public QObject
{
       Q_OBJECT
public:
    Root();
    Root(GUI* gui, Employee* employee);
    ~Root();
    void* genConsumer();
    //randomly generate consumers - thread function
    static void* consumerThread(void* param);
    static void* catThread(void* param);
    static void* consumerGenThread(void* param);
    static void* monitor(void* param);

    void catConsumer(Consumer* consumer);
    //distribute cat - operation function
    void* consumerEmp();
    //keep record of whether the employee is available
    //and whether there are waiting consumers

    void* run();

signals:
    void newConsumer();
    void catSemChange();
    //use see_getvalue() to update ui
    void removeConsumer(Consumer* consumer);

public slots:
    void consumed(Consumer* consumer);
    void catFree(Cat* cat);
    void cated(Consumer* consumer);
    void queueCon(Consumer* consumer);


private:
    GUI* gui;
    Employee* employee;
    Consumer* consumer[MAX_CON_NUM];
    Cat* cat[MAX_CAT_NUM];

    sem_t cat_sem;

    pthread_t conTid[MAX_CON_NUM];
    pthread_attr_t conAttr[MAX_CON_NUM];

    pthread_t catTid[MAX_CAT_NUM];
    pthread_attr_t catAttr[MAX_CAT_NUM];

    QQueue<Cat*> *freeCat;
    QQueue<Consumer*> *wConsumer;
    //consumer in queue

};

#endif // ROOT_H
