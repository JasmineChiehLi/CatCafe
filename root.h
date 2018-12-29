#ifndef ROOT_H
#define ROOT_H

#include <QObject>
#include "consumer.h"
#include "cat.h"
#include "gui.h"

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include <time.h>
#include <stdlib.h>

#define MAX_CON_NUM 128
#define MAX_CAT_NUM 6

#define MIN_CON_GAP 7
#define CON_VAR 6


class Root
        :public QObject
{
       Q_OBJECT
public:
    Root();
    Root(GUI* gui);
    ~Root();
    void* genConsumer();
    //randomly generate consumers - thread function

    static void* consumerThread(void* param);
    static void* catThread(void* param);
    static void* consumerGenThread(void* param);

    void catConsumer(Consumer* consumer);
    //distribute cat - operation function

    void* run();

signals:
    void newConsumer();
    void catSemChange();
    //use see_getvalue() to update ui

public slots:
    void consumed(Consumer* consumer);
    void catFree();


private:
    GUI* gui;
    Consumer* consumer[MAX_CON_NUM];
    Cat* cat[MAX_CAT_NUM];

    sem_t* cat_sem;

    pthread_t conTid[MAX_CON_NUM];
    pthread_attr_t conAttr[MAX_CON_NUM];

    pthread_t catTid[MAX_CAT_NUM];
    pthread_attr_t catAttr[MAX_CAT_NUM];

};

#endif // ROOT_H
