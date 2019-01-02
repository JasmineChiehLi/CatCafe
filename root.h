#ifndef ROOT_H
#define ROOT_H

#include <QObject>
#include <QQueue>

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include <time.h>
#include <stdlib.h>

#include "gui.h"
#include "employee.h"

#define MAX_CON_NUM 128
#define MAX_CAT_NUM 6

#define MIN_CON_GAP 3
#define CON_VAR 2

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
  //  static void* monitor(void* param);

    void catConsumer(Consumer* consumer);
    //distribute cat - operation function
   // void* consumerEmp();
    //keep record of whether the employee is available
    //and whether there are waiting consumers

    void* run();

    sem_t sem_q;

signals:
    void catSemChange();
    //use see_getvalue() to update ui
    void removeConsumer(Consumer* consumer);
    void queueUp(Consumer* consumer);

    //gui-concerned signals
    void enQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer);
    void deQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer);

public slots:
    void consumed(Consumer* consumer);
    void catFree(Cat* cat);
    void cated(Consumer* consumer);
    void queueCon(Consumer* consumer);
    void consumerEmp();

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
