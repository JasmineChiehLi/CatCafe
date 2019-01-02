#include "root.h"

//Third-party view


//wether bought coffee
//wether available cat
//generate cat
//generate consumer

Root::Root()
{
    gui = nullptr;
    employee = nullptr;
}

Root::Root(GUI* gui, Employee* employee) {
    freeCat = new QQueue<Cat*>();
    wConsumer = new QQueue<Consumer*>();

    this->gui = gui;
    this->employee = employee;
    QObject::connect(this, SIGNAL(removeConsumer(Consumer*)), gui, SLOT(removeConsumer(Consumer*)));
    QObject::connect(this, SIGNAL(enQueue(Consumer*, QQueue<Consumer*>*)), gui, SLOT(enQueue(Consumer*, QQueue<Consumer*>*)));
    QObject::connect(this, SIGNAL(deQueue(Consumer*, QQueue<Consumer*>*)), gui, SLOT(deQueue(Consumer*, QQueue<Consumer*>*)));

    for(int i = 0; i < MAX_CAT_NUM; i++) {
        cat[i] = new Cat();

        pthread_attr_init(&catAttr[i]);

        QObject::connect(cat[i], SIGNAL(work(Cat*)), gui, SLOT(work(Cat*)));
        QObject::connect(cat[i], SIGNAL(home(Cat*)), gui, SLOT(home(Cat*)));

        freeCat->enqueue(cat[i]);
    }

    for(int i = 0; i < MAX_CAT_NUM; i++) {
        pthread_create(&catTid[i], &catAttr[i], catThread, static_cast<void*>(cat[i]));
        cat[i]->setTid(static_cast<pthread_t>(i));
    }

    sem_init(&cat_sem, 0, MAX_CAT_NUM);
}

Root::~Root() {

}

void* Root::genConsumer() {
    //randomly generate new consumer
    srand(static_cast<unsigned>(time(nullptr)));

    for(int i = 0; i < MAX_CON_NUM; i++) {
        consumer[i] = new Consumer();
        QObject::connect(consumer[i], SIGNAL(wantCat(Consumer*)), this, SLOT(consumed(Consumer*)));
        QObject::connect(consumer[i], SIGNAL(bye(Consumer*)), this, SLOT(cated(Consumer*)));
        QObject::connect(consumer[i], SIGNAL(queueUp(Consumer*)), this, SLOT(queueCon(Consumer*)));
        QObject::connect(consumer[i], SIGNAL(waitCat(Consumer*)), gui, SLOT(waitCat(Consumer*)));
        QObject::connect(consumer[i], SIGNAL(cating(Consumer*, Cat*)), gui, SLOT(cating(Consumer*, Cat*)));

        pthread_attr_init(&conAttr[i]);
        pthread_create(&conTid[i], &conAttr[i], consumerThread, static_cast<void*>(consumer[i]));

        consumer[i]->setTid(static_cast<pthread_t>(i));
        emit newConsumer();

        //Sleep
        unsigned int gap = rand() % CON_VAR + MIN_CON_GAP;
        sleep(gap);
    }

    pthread_exit(nullptr);
}

void Root::consumed(Consumer* consumer) {
    emit deQueue(consumer, wConsumer);
    if(consumer->getHaveCafe()) {
        catConsumer(consumer);
    }
}

void Root::cated(Consumer* consumer) {
    emit removeConsumer(consumer);
    catFree(consumer->getCat());

    delete consumer;
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

void* Root::consumerEmp() {
    while(true) {
        sem_wait(&(employee->empSem));
        //when emplyee is available

        while(wConsumer->empty()) {
            wait(nullptr);
        }

        Consumer* consumer = wConsumer->dequeue();
        employee->setConsumer(consumer);
        consumer -> setBeingServed(true);

        sem_post(&(employee->empSem));
    }
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

void* Root::monitor(void* param) {
    return static_cast<Root*>(param)->consumerEmp();
}

void Root::catFree(Cat* cat) {
    cat->setConsumer(nullptr);
    freeCat->enqueue(cat);
    sem_post(&cat_sem);
    emit catSemChange();
}

void Root::queueCon(Consumer* consumer) {
    wConsumer->enqueue(consumer);
    sleep(1);
    qDebug() << "queueCon: " << wConsumer->size();
    emit enQueue(consumer, wConsumer);
    qDebug() << "consumer " << consumer->getTid() <<"in queue"<<endl;
}
