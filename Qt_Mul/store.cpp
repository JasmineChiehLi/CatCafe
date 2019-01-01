#include "store.h"

Store::Store()
{
    length = 0;
    text = new QGraphicsTextItem();

    pthread_mutex_init(&busy, nullptr);
    cond = PTHREAD_COND_INITIALIZER;

    text->setX(300);
    text->setY(100);
    text->setPlainText("Store");
}

Store::~Store() {

}

void Store::setNum(int pos, int n) {

    if(pos <= length+1 && length < SIZE-1) {
        if(pos > length) {
            length = pos+1;
            //text->setPlainText("good");
            qDebug()<<"store" <<n;
        }
       num[pos] = n;
       emit storeUpdate();
       return;
    }
    else {
        qDebug()<<"Overflow";
    }
}

int Store::getNum(int pos) {
    if(pos>=length) {
        return -1;
    }
    return num[pos];
}

int Store::getLength() {
    return length;
}
