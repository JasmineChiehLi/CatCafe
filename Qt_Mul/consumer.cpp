#include "consumer.h"

Consumer::Consumer()
{

}

Consumer::~Consumer() {

}

Consumer::Consumer(Store* s) {
    store = s;
    text = new QGraphicsTextItem();

    text->setX(100);
    text->setY(100);
    //setPlainText("Consumer");
}

void* Consumer::consume() {
    for(int i = 0; i < 20; i++) {
        pthread_mutex_lock(&store->busy);

        while(i >= store->getLength()) {
            pthread_cond_wait(&store->cond, &store->busy);
        }
        N = store->getNum(i);
        //text->setPlainText(QString(N));
        qDebug()<<"Consumer"<<N;

        pthread_cond_signal(&store->cond);
        pthread_mutex_unlock(&store->busy);
        sleep(1);
    }
    pthread_exit(nullptr);
}

int Consumer::getN() {
    return N;
}
