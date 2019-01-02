#include "gui.h"
#include "root.h"

GUI::GUI()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage("/home/li/CatCafe/img/Background.png")));

    //    pic = {QPixmap("/home/li/CatCafe/img/Consumer.png"), "/home/li/CatCafe/img/Employee.png", "/home/li/CatCafe/img/Cat.png"};
    pic[0] = new QPixmap("/home/li/CatCafe/img/Consumer.png");
    pic[1] = new QPixmap("/home/li/CatCafe/img/Cat.png");
    pic[2] = new QPixmap("/home/li/CatCafe/img/Employee.png");

    setScene(scene);
}

void GUI::setRoot(Root* root) {
    this->root = root;
}

void GUI::removeConsumer(Consumer* consumer) {
    qDebug() << "GUI: consumer " << consumer->getTid() << " just left" <<endl;
}

void GUI::work(Cat* cat) {

}

void GUI::home(Cat* cat) {

}

void GUI::enQueue(Consumer* consumer, QQueue<Consumer*>* wConsumer) {
    sem_wait(&(root->sem_q));
    int d=wConsumer->size();
    qDebug() << "enqueue:" << d;
    sem_post(&(root->sem_q));

    QGraphicsPixmapItem *image;
    image = consumer->getImage();
    image->setPixmap(*pic[rand() % 3]);
    image->setPos(180, 85*d);
    //这里要处理一下，如果超过了人数。也就是纵坐标的极限值
    qDebug()<<consumer->getTid();
    scene->addItem(image);
    consumer->setIsRegistered(true);
}

void GUI::waitCat(Consumer* consumer) {

}

void GUI::cating(Consumer* consumer, Cat* cat) {

}

void GUI::deQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer) {
    QGraphicsPixmapItem *image;
    image = consumer->getImage();
    while(!consumer->getIsRegistered()) {
        wait(nullptr);
    }

    scene->removeItem(image);
    image->setPos(500, 500);
    scene->addItem(image);

    sem_wait(&(root->sem_q));
    for(int j = 0; j < 2; j++) {
        for (int i = 0, n = wConsumer->size();i < n;i++) {//从队列的第二个开始
            image = wConsumer->at(i)->getImage();
            scene->removeItem(image);
            image->setPos(180, (i+1) * 85);
            scene->addItem(image);
            qDebug() << "dequeue: " << image->pos().y();
        }
    }
    sem_post(&(root->sem_q));
}
