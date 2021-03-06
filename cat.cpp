#include "cat.h"
#include "consumer.h"

Cat::Cat()
{
    isFree = true;
    consumer = nullptr;
}

bool Cat::getIsFree() {
    return isFree;
}

void Cat::setIsFree(bool isFreeNow) {
    this->isFree = isFreeNow;
}

void Cat::setTid(pthread_t tid) {
    this->tid = tid;
}

void Cat::setConsumer(Consumer* consumer) {
    this->consumer = consumer;
}

void* Cat::Mew() {
    while(true) {
        qDebug() <<"Cat "<< this->tid << ": I'm waiting for a consumer" << endl;
        //sleep(1);
        while (consumer == nullptr) {
            wait(nullptr);
        }
        emit work(this);
        qDebug() <<"Cat "<< this->tid << " I'm going to work" <<endl;

        while (consumer != nullptr) {
            wait(nullptr);
        }
        setIsFree(true);
        qDebug() <<"Cat "<< this->tid << " I'm free" <<endl;

        emit home(this);
        qDebug() <<"Cat "<< this->tid << " I'm home" <<endl;
    }
}

pthread_t Cat::getTid() {
    return this->tid;
}
