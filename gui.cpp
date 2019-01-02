#include "gui.h"
#include "root.h"

GUI::GUI()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage("/home/li/CatCafe/img/Background.png")));

    emp = new QGraphicsPixmapItem(QPixmap("/home/li/CatCafe/img/Employee.png"));
    emp->setPos(180,0);
    emp->setScale(0.85);
    scene->addItem(emp);

    enjoy=new QGraphicsPixmapItem();
    enjoy->setPixmap(QPixmap("/home/li/CatCafe/img/Enjoy.png"));
    enjoy->setPos(-10,0);
    enjoy->setScale(1);
    scene->addItem(enjoy);

    wConsumer = new QQueue<Consumer*>();
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

void GUI::enQueue(Consumer* consumer) {
        wConsumer->enqueue(consumer);
        int d = wConsumer->size();
        qDebug() << "en:" <<d;
        QGraphicsPixmapItem *image;
        image = consumer->getImage();
        image->setPixmap(*pic[rand() % 3]);
        int y_ = 85;
        image->setPos(180,  85 * d);
        //这里要处理一下，如果超过了人数。也就是纵坐标的极限值
        scene->addItem(image);
}

void GUI::waitCat(Consumer* consumer) {

}

void GUI::cating(Consumer* consumer, Cat* cat) {

}

void GUI::deQueue(Consumer* consumer, QQueue<Consumer*> *nConsumer) {
    QGraphicsPixmapItem *image;
        image=wConsumer->dequeue()->getImage();
        int dy = 85;
        image->setPos(400, 200);
        for (int i = 0, n = wConsumer->size();i < n;i++) {//从队列的第二个开始
            //qDebug() << "n:  " << n << "  i: " << i;
            qDebug() << "de:" << i;
            image = wConsumer->at(i)->getImage();
            image->setPos(180, dy * (i + 1));
        }
}

void GUI::sayHello() {
    sleep(1);
    scene->removeItem(enjoy);
    hello=new QGraphicsPixmapItem();
    hello->setPixmap(QPixmap("/home/li/CatCafe/img/Hello.png"));
    hello->setPos(-5,0);
    hello->setScale(1);
    scene->addItem(hello);
}

void GUI::sayEnjoy(){
    scene->removeItem(hello);
    enjoy=new QGraphicsPixmapItem();
    enjoy->setPixmap(QPixmap("/home/li/CatCafe/img/Enjoy.png"));
    enjoy->setPos(-10,0);
    enjoy->setScale(1);
    scene->addItem(enjoy);
}

