#include "widget.h"
#include <QApplication>
#include "root.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Root* root = new Root();

    pthread_t tidGenCon;
    pthread_attr_t attrGenCon;

    pthread_attr_init(&attrGenCon);
    pthread_create(&tidGenCon, &attrGenCon, root->consumerGenThread, root);

    return a.exec();
}
