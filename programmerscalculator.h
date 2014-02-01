#ifndef PROGRAMMERSCALCULATOR_H
#define PROGRAMMERSCALCULATOR_H

#include <QMainWindow>
#include "calcstack.h"
#include "rpnparser.h"

namespace Ui {
class ProgrammersCalculator;
}

class ProgrammersCalculator : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ProgrammersCalculator(QWidget *parent = 0);
    ~ProgrammersCalculator();
    
private:
    void updateDisplay(void);
    Ui::ProgrammersCalculator *ui;
    Parser* parser;
    CalcStack* calcStack;

private slots:
    void newInput(void);
};

#endif // PROGRAMMERSCALCULATOR_H
