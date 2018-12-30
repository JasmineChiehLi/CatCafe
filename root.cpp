#include "root.h"

//Third-party view


//wether bought coffee
//wether available cat
//generate cat
//generate consumer

Root::Root()
{

}

Root::Root(GUI* gui) {
    freeCat = new QQueue<Cat*>();

    for(int i = 0; i < MAX_CAT_NUM; i++) {
        cat[i] = new Cat();

        pthread_attr_init(&catAttr[i]);

        QObject::connect(cat[i], SIGNAL(goToWork(Cat*)), gui, SLOT(updateCat(Cat*)));
        QObject::connect(cat[i], SIGNAL(goHome(Cat*)), gui, SLOT(updateCat(Cat*)));

        freeCat->enqueue(cat[i]);
    }

    for(int i = 0; i < MAX_CAT_NUM; i++) {
        pthread_create(&catTid[i], &catAttr[i], catThread, static_cast<void*>(cat[i]));
        cat[i]->setTid(static_cast<pthread_t>(i));
    }

    sem_init(&cat_sem, 0, MAX_CAT_NUM);
    this->gui = gui;
    QObject::connect(this, SIGNAL(removeConsumer(Consumer*)), gui, SLOT(removeConsumer(Consumer*)));
}

Root::~Root() {

}

void* Root::genConsumer() {
    //randomly generate new consumer

    for(int i = 0; i < MAX_CON_NUM; i++) {
        consumer[i] = new Consumer();
        QObject::connect(consumer[i], SIGNAL(wantCat(Consumer*)), this, SLOT(consumed(Consumer*)));
        QObject::connect(consumer[i], SIGNAL(finish(Consumer*)), this, SLOT(cated(Consumer*)));

        pthread_attr_init(&conAttr[i]);
        pthread_create(&conTid[i], &conAttr[i], consumerThread, static_cast<void*>(consumer[i]));

        consumer[i]->setTid(static_cast<pthread_t>(i));
        emit newConsumer();

        //Sleep
        srand(static_cast<unsigned>(time(nullptr)));
        unsigned int gap = rand() % CON_VAR + MIN_CON_GAP;
        sleep(gap);
    }

    pthread_exit(nullptr);
}

void Root::consumed(Consumer* consumer) {
    if(consumer->getHaveCafe()) {
        catConsumer(consumer);
    }
}

void Root::cated(Consumer* consumer) {
    emit removeConsumer(consumer);
    catFree(consumer->getCat());

    delete consumer;
    consumer = nullptr;

}

void Root::catConsumer(Consumer* consumer) {
    //distribute cat
    sem_wait(&cat_sem);
    emit catSemChange();

    Cat* cat = freeCat->dequeue();
    cat->setIsFree(false);
    cat->setConsumer(consumer);
    cat->setIsFree(false);
    consumer->setCat(cat);

}

void* Root::consumerThread(void* param) {
    return static_cast<Consumer*>(param)->consume();
}

void* Root::consumerGenThread(void *param) {
    return static_cast<Root*>(param)->genConsumer();
}

void* Root::catThread(void* param) {
    return static_cast<Cat*>(param)->Mew();
}

void Root::catFree(Cat* cat) {
    cat->setConsumer(nullptr);
    freeCat->enqueue(cat);
    sem_post(&cat_sem);
    emit catSemChange();
}
