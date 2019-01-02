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
    cConsumer = new QQueue<Consumer*>();

    pic[0] = new QPixmap("/home/li/CatCafe/img/Consumer.png");
    pic[1] = new QPixmap("/home/li/CatCafe/img/Cat.png");
    pic[2] = new QPixmap("/home/li/CatCafe/img/Employee.png");

    for(int i = 0; i < 6; i++) {
        cats[i] = new QGraphicsPixmapItem(QPixmap("/home/li/CatCafe/img/Cat.png"));
        cats[i]->setScale(0.8);
        cats[i]->setPos(690, 75*i);
        scene->addItem(cats[i]);
    }

    setScene(scene);
}

void GUI::enCatQueue(Consumer* consumer) {
    cConsumer->enqueue(consumer);
    int d = cConsumer->size();
    QGraphicsPixmapItem *image;
        image = consumer->getImage();
        int y_ = 85;
        image->setPos(y_*(d-1), 510);
}

void GUI::setRoot(Root* root) {
    this->root = root;
}

void GUI::removeConsumer(Consumer* consumer) {
    qDebug() << "GUI: consumer " << consumer->getTid() << " just left" <<endl;
    scene->removeItem(consumer->getImage());
}

void GUI::work(Cat* cat) {

}

void GUI::home(Cat* cat) {
    int i = cat->getTid();
    cats[i]->setPos(690, 75*i);
    int j = cats[i]->pos().y() / 90;
    pos[i] = 0;
}

void GUI::enQueue(Consumer* consumer) {
        wConsumer->enqueue(consumer);
        int d = wConsumer->size();
        //qDebug() << "en:" <<d;
        QGraphicsPixmapItem *image;
        image = consumer->getImage();
        image->setPixmap(*pic[rand() % 3]);
        image->setPos(180,  85 * d);
        scene->addItem(image);
}

void GUI::cating(Consumer* consumer, Cat* cat) {
        QGraphicsPixmapItem *con, *cat_p;
        con = consumer->getImage();
        int i = cat->getTid();
        cat_p = cats[i];
        for (int i = 0;i < 6;i++) {
            if (pos[i] == 1) {
                i++;
                continue;
            }
            else {
                con->setPos(360, 90 * i);
                //qDebug() <<pos;
                cat_p->setPos(450, 90 * i);
                pos[i] = 1;
                break;
            }
        }
}

void GUI::deQueue(Consumer* consumer, QQueue<Consumer*> *nConsumer) {
    QGraphicsPixmapItem *image;
        image=wConsumer->dequeue()->getImage();
        int dy = 85;
        enCatQueue(consumer);
        for (int i = 0, n = wConsumer->size();i < n;i++) {//从队列的第二个开始
            //qDebug() << "n:  " << n << "  i: " << i;
           // qDebug() << "de:" << i;
            image = wConsumer->at(i)->getImage();
            image->setPos(180, dy * (i + 1));
        }
}

void GUI::deCatQueue(Consumer* consumer, Cat* cat) {
    cating(consumer, cat);
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

