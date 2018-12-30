#include "gui.h"
#include "cat.h"
#include "consumer.h"

GUI::GUI()
{

}

void GUI::updateCatSem() {

}

void GUI::updateCat(Cat* cat) {
    qDebug() << "GUI: cat " << cat->getTid() << " is free? " << cat->getIsFree() <<endl;
}

void GUI::removeConsumer(Consumer* consumer) {
    qDebug() << "GUI: consumer " << consumer->getTid() << " just left" <<endl;
}


