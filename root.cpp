#include "root.h"

//Third-party view


//wether bought coffee
//wether available cat
//generate cat
//generate consumer

Root::Root()
{
    for(int i = 0; i < MAX_CAT_NUM; i++) {
        cat[i] = new Cat();

        QObject::connect(cat[i], SIGNAL(goToWork()), gui, SLOT(updateCat(cat[i])));

        pthread_attr_init(&catAttr[i]);
        pthread_create(&catTid[i], &catAttr[i], catThread, static_cast<void*>(cat[i]));
    }

    sem_init(cat_sem, 0, MAX_CAT_NUM);
}

Root::Root(GUI* gui) {
    this->gui = gui;
}

Root::~Root() {

}

void* Root::genConsumer() {
    //randomly generate new consumer

    for(int i = 0; i < MAX_CON_NUM; i++) {
        consumer[i] = new Consumer();
        QObject::connect(consumer[i], SIGNAL(wantCat()), this, SLOT(consumed(consumer[i])));

        pthread_attr_init(&conAttr[i]);
        pthread_create(&conTid[i], &conAttr[i], consumerThread, static_cast<void*>(consumer[i]));

        emit newConsumer();

        //Sleep
        srand(static_cast<unsigned>(time(nullptr)));
        unsigned int gap = rand() % CON_VAR + MIN_CON_GAP;
        sleep(gap);
    }
    return nullptr;
}

void Root::consumed(Consumer* consumer) {
    if(consumer->getHaveCafe()) {
        catConsumer(consumer);
    }
}

void Root::catConsumer(Consumer* consumer) {
    //distribute cat
    sem_wait(cat_sem);
    emit catSemChange();

    for(int i = 0; i < MAX_CAT_NUM; i++) {
        if(cat[i]->getIsFree()) {
            cat[i]->setIsFree(false);
            cat[i]->setConsumer(consumer);
            consumer->setCat(cat[i]);
        }
    }

}

void* Root::consumerThread(void* param) {
    return static_cast<Consumer*>(param)->consume();
}

void* Root::consumerGenThread(void *param) {
    return static_cast<Root*>(param)->genConsumer();
}

void* Root::catThread(void* param) {
    return static_cast<Cat*>(param)->play();
}

void Root::catFree() {
    sem_post(cat_sem);
    emit catSemChange();
}
