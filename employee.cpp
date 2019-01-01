#include "employee.h"

Employee::Employee() {
    consumer = nullptr;
    sem_init(&empSem, 1, 1);
    //binary semaphore, mutex resouce
}

void Employee::setConsumer(Consumer* consumer){
    this->consumer=consumer;
}

void Employee::genServeTime() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

int Employee::getServeTime(){
    return serveTime;
}

void Employee::setTid(pthread_t tid){
    this->tid=tid;
}

pthread_t Employee::getTid(){
    return tid;
}

void* Employee::serve(){
    int i=0;
    genServeTime();
    qDebug()<<"employee begins to work";
    while(true){
        while(consumer == nullptr) {
            wait(nullptr);
        }
        sem_wait(&empSem);
        i++;
        qDebug()<<"consumer "<<i<<" coming";
        emit hello();

        serveTime = rand() % SERVE_VAR + SERVE_GAP;
        sleep(static_cast<unsigned int>(serveTime));
        consumer->setHaveCafe(true);

        qDebug()<<"work finished";
        emit enjoy();
        consumer = nullptr;
        sem_post(&empSem);
    }
}

void* Employee::run(void* param){
    return static_cast<Employee*>(param)->serve();
}
