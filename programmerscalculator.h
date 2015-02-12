// Programmer's Calculator
//
// Copyright 2014-2015, Risto Tiainen
//
// Programmer's Calculator is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// Programmer's Calculator is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Programmer's Calculator.
// If not, see <http://www.gnu.org/licenses/>.

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
    void showText(const QString fileName = "COPYING");
    Ui::ProgrammersCalculator *ui;
    Parser* parser;
    CalcStack* calcStack;

private slots:
    void newInput(void);
};

#endif // PROGRAMMERSCALCULATOR_H
