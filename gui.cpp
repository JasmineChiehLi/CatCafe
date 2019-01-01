#include "gui.h"


GUI::GUI()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage("/home/li/CatCafe/img/Background.png")));

    qDebug() << "why?";
    setScene(scene);
}

void GUI::removeConsumer(Consumer* consumer) {
    qDebug() << "GUI: consumer " << consumer->getTid() << " just left" <<endl;
}

void GUI::work(Cat* cat) {

}

void GUI::home(Cat* cat) {

}

void GUI::enQueue(Consumer* consumer) {

}

void GUI::waitCat(Consumer* consumer) {

}

void GUI::cating(Consumer* consumer, Cat* cat) {

}
