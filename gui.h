#ifndef GUI_H
#define GUI_H

#include <QGraphicsView>
#include <QGraphicsScene>
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

    void enQueue(Consumer* consumer);
    void waitCat(Consumer* consumer);
    void cating(Consumer* consumer, Cat* cat);

    void work(Cat* cat);
    void home(Cat* cat);

private:
    QGraphicsScene* scene;
};

#endif // GUI_H
