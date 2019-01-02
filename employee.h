#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QDebug>

#include <stdlib.h>

#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "consumer.h"


#define SERVE_GAP 10
#define SERVE_VAR 3

class Employee
        : public QObject
{
    Q_OBJECT
public:
    sem_t empSem;

    Employee();
    void setConsumer(Consumer* consumer);
    int getServeTime();
    void genServeTime();
    void setTid(pthread_t tid);
    pthread_t getTid();

    void *serve();//線程函數
    static void* run(void* param);
signals:
    void hello();
    void enjoy();

private:
    Consumer* consumer;
    int serveTime;

    pthread_t tid;
};

#endif // EMPLOYEE_H
