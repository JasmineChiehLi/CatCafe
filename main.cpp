#include <QApplication>
#include "root.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI* gui = new GUI();
//    Employee* employee = new Employee();
//    Root* root = new Root(gui, employee);


//    pthread_t tidGenCon, tidEmp, tidMon;
//    pthread_attr_t attrGenCon, attrEmp, attrMon;

//    pthread_attr_init(&attrEmp);
//    pthread_create(&tidEmp, &attrEmp, employee->run, employee);

//    pthread_attr_init(&attrGenCon);
//    pthread_create(&tidGenCon, &attrGenCon, root->consumerGenThread, root);

//    pthread_attr_init(&attrMon);
//    pthread_create(&tidMon, &attrMon, root->monitor, root);
    gui->show();

    return a.exec();
}
