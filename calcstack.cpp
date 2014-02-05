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

#include "calcstack.h"

CalcStack::CalcStack() {
    stack.clear();
}

void CalcStack::clear(void) {
    stack.clear();
}

bool CalcStack::pushItem(CalcStackItem* item) {
    unsigned sizeBefore = stack.size();

    stack.push_front(item);

    return ((stack.size()-sizeBefore) == 1);
}

CalcStackItem* CalcStack::popItem(void) {
    CalcStackItem* item = (CalcStackItem*)0;

    if (!stack.empty()) {
        item = stack.at(0);
        stack.pop_front();
    }

    return item;
}

CalcStackItem* CalcStack::top(void) {
    CalcStackItem* item = (CalcStackItem*)0;

    if(!stack.empty()) {
        item = stack.at(0);
    }

    return item;
}

bool CalcStack::exportToStringList(QListWidget* w) {
    bool status=false;
    QList<CalcStackItem*>::iterator it;

    w->clear();

    if(!stack.empty()) {
        it=stack.begin();

        while(it != stack.end()) {
            w->addItem((*it)->getString());
            it++;
        }
        status=true;
    }

    return status;
}
