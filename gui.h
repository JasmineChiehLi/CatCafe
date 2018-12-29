#ifndef GUI_H
#define GUI_H

#include <QGraphicsView>

class Cat;

class GUI
        :public QGraphicsView
{
    Q_OBJECT
public:
    GUI();

public slots:
    void updateCatSem();
    void updateCat(Cat* cat);
};

#endif // GUI_H
