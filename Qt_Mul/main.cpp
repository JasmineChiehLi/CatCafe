#include "widget.h"
#include <QApplication>
#include "playground.h"

int main(int argc, char* argv[])
{
   QApplication a(argc, argv);

   Playground* pg = new Playground();

   pg->show();
   pg->play();

   return a.exec();
}
