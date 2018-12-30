#ifndef GUI_H
#define GUI_H

#include <QGraphicsView>
#include <QDebug>

class Cat;
class Consumer;

class GUI
        :public QGraphicsView
{
    Q_OBJECT
public:
    GUI();

public slots:
    void updateCatSem();
public slots:
    void updateCat(Cat* cat);
public slots:
    void removeConsumer(Consumer* consumer);
};

#endif // GUI_H
