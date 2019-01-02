#ifndef GUI_H
#define GUI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QQueue>
#include <QBrush>
#include <QImage>
#include <QDebug>

#include "employee.h"

class Root;

class GUI
        :public QGraphicsView
{
    Q_OBJECT
public:
    GUI();
    void setRoot(Root* root);

public slots:
    void removeConsumer(Consumer* consumer);

    void enQueue(Consumer* consumer);
    void deQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer);
    void waitCat(Consumer* consumer);
    void cating(Consumer* consumer, Cat* cat);

    void work(Cat* cat);
    void home(Cat* cat);

    void sayHello();
    void sayEnjoy();
private:
    QQueue<Consumer*> *wConsumer;
    QGraphicsScene* scene;
    QPixmap* pic[3];
    Root* root;

    QGraphicsPixmapItem* emp;
    QGraphicsPixmapItem* hello;
    QGraphicsPixmapItem* enjoy;
};

#endif // GUI_H
