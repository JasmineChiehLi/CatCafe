#include "playground.h"

Playground::Playground()
{
    store = new Store();
    producer  = new Producer(store);
    consumer = new Consumer(store);
    scene = new QGraphicsScene();
    conText = new QGraphicsTextItem();
    conText->setX(300);
    conText->setY(300);

    QObject::connect(store, SIGNAL(storeUpdate()), this, SLOT(storeNew()));

    //scene->addItem(consumer->text);
    scene->addItem(store->text);
    scene->addItem(conText);
    scene->setSceneRect(0, 0, 800, 600);

    this->setScene(scene);
}

Playground::~Playground() {

}

void Playground::play() {
    pthread_t tidP, tidC;
    pthread_attr_t attrP, attrC;

    pthread_attr_init(&attrP);
    pthread_attr_init(&attrC);

    pthread_create(&tidP, &attrP, produce, static_cast<void*>(producer));
    pthread_create(&tidC, &attrC, consume, static_cast<void*>(consumer));
}

void* Playground::produce(void* param) {
    return static_cast<Producer*>(param)->produce();
}

void* Playground::consume(void* param) {
    return static_cast<Consumer*>(param)->consume();
}

void Playground::storeNew() {
    conText->setPlainText(QString::number(consumer->getN()));
}
