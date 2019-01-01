#include "consumer.h"

Consumer::Consumer()
{
    cat = nullptr;
    beingServed = false;
    haveCafe = false;

    srand(static_cast<unsigned int>(time(nullptr)));
    catTime = rand() % CAT_VAR + CAT_GAP;
}

bool Consumer::getHaveCafe() {
    return haveCafe;
}

void Consumer::setHaveCafe(bool nowHaveCafe) {
    haveCafe = nowHaveCafe;
}

void Consumer::setCat(Cat* cat) {
    this->cat = cat;
}

void Consumer::setBeingServed(bool nowServed) {
    this->beingServed = nowServed;
}

Cat* Consumer::getCat() {
    return cat;
}

void* Consumer::consume() {
        queueUp(this);
        while(beingServed == false) {
            wait();
        }
        qDebug() << "comsumer buying";

        while(haveCafe == false) {
            wait();
        }
        emit wantCat(this);
        qDebug() << "Consumer "<< this->tid <<": I want a cat!" << endl;


        while(cat == nullptr) {
            wait();
        }
        qDebug() <<"Consumer "<< this->tid <<": I got a cat!" << endl;
        sleep(static_cast<unsigned int>(catTime));

        qDebug() <<"Consumer "<< this->tid <<": Bye!" << endl;
        emit bye(this);
        return nullptr;
}

void Consumer::setTid(pthread_t tid) {
    this->tid = tid;
}

pthread_t Consumer::getTid() {
    return tid;
}
