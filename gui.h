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

class GUI
        :public QGraphicsView
{
    Q_OBJECT
public:
    GUI();

public slots:
    void removeConsumer(Consumer* consumer);

    void enQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer);
    void deQueue(Consumer* consumer, QQueue<Consumer*> *wConsumer);
    void waitCat(Consumer* consumer);
    void cating(Consumer* consumer, Cat* cat);

    void work(Cat* cat);
    void home(Cat* cat);
private:
    QGraphicsScene* scene;
    QPixmap* pic[3];
};

#endif // GUI_H
