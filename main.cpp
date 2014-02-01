#include <QtGui/QApplication>
#include "programmerscalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgrammersCalculator w;
    w.show();
    
    return a.exec();
}
