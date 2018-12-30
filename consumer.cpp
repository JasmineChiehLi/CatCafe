#include "consumer.h"

Consumer::Consumer()
{
    cat = nullptr;
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

Cat* Consumer::getCat() {
    return cat;
}

void* Consumer::consume() {
    sleep(2);
    qDebug() << "Consumer "<< this->tid <<": I want a cat!" << endl;

    setHaveCafe(true);
    emit wantCat(this);

    while(cat == nullptr) {
        wait();
    }
    qDebug() <<"Consumer "<< this->tid <<": I got a cat!" << endl;
    sleep(3);

    emit finish(this);
    qDebug() <<"Consumer "<< this->tid <<": Bye!" << endl;
    return nullptr;
}

void Consumer::setTid(pthread_t tid) {
    this->tid = tid;
}

pthread_t Consumer::getTid() {
    return tid;
}
