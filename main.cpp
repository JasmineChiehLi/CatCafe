#include "widget.h"
#include <QApplication>
#include "root.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI* gui = new GUI();
    Root* root = new Root(gui);

    pthread_t tidGenCon;
    pthread_attr_t attrGenCon;

    pthread_attr_init(&attrGenCon);
    pthread_create(&tidGenCon, &attrGenCon, root->consumerGenThread, root);

    return a.exec();
}
