// Programmer's Calculator
//
// Copyright 2014, Risto Tiainen
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

#ifndef CALCSTACK_H
#define CALCSTACK_H

#include <QListWidget>
#include <QString>
#include <QList>

#include "calcstackitem.h"

class CalcStack
{

public:
    CalcStack();
    void clear(void);
    bool pushItem(CalcStackItem* item);
    CalcStackItem* popItem(void);               // Get an item and delete it from the stack
    CalcStackItem* top(void);                   // Get a pointer to the topmost item
    unsigned items(void) { return stack.size(); }
    bool exportToStringList(QListWidget* w);    // A bit dirty, do it better later

private:
    QList<CalcStackItem*> stack;
};

#endif // CALCSTACK_H
