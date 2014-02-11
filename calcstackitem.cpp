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

#include <QString>
#include "calcstackitem.h"

QString CalcStackItemInt::getString(void) const {
    QString str="";

    if(base == 16) {
        str="0x"+QString::number(val, 16);
    }
    else if(base == 2) {
        str="0b"+QString::number(val, 2);
    }
    else {
        str=QString::number(val);
    }

    return str;
}

QString CalcStackItemFloat::getString(void) const {
    QString s = QString::number(val);
    if(!s.contains('.')) {
        if(!s.contains('e')) {
            s.append(".0");
        }
        else {
            s = s.section('e',0,0)+".0e"+s.section('e',1,1);
        }
    }
    return s;
}

CalcStackItem* CalcStackItem::add(const CalcStackItem* a, const CalcStackItem* b, bool* status) {
    CalcStackItem* res=0;

    if(a->isInteger() && b->isInteger()) {
        res = new CalcStackItemInt(a->getInteger()+b->getInteger(), b->getBase());
    }
    else {
        res = new CalcStackItemFloat(a->getFloat()+b->getFloat());
    }

    // Addition always succeeds
    if(status != 0) {
        *status = true;
    }

    return res;
}

CalcStackItem* CalcStackItem::sub(const CalcStackItem* a, const CalcStackItem* b, bool* status) {
    CalcStackItem* res=0;

    if(a->isInteger() && b->isInteger()) {
        res = new CalcStackItemInt(a->getInteger()-b->getInteger(), b->getBase());
    }
    else {
        res = new CalcStackItemFloat(a->getFloat()-b->getFloat());
    }

    // Subtraction always succeeds
    if(status != 0) {
        *status = true;
    }

    return res;
}

CalcStackItem* CalcStackItem::mul(const CalcStackItem* a, const CalcStackItem* b, bool* status) {
    CalcStackItem* res=0;

    if(a->isInteger() && b->isInteger()) {
        res = new CalcStackItemInt(a->getInteger()*b->getInteger(), b->getBase());
    }
    else {
        res = new CalcStackItemFloat(a->getFloat()*b->getFloat());
    }

    // Multiplication always succeeds
    if(status != 0) {
        *status = true;
    }

    return res;
}

CalcStackItem* CalcStackItem::div(const CalcStackItem* a, const CalcStackItem* b, bool* status) {
    CalcStackItem* res=0;

    if(a->isInteger() && b->isInteger()) {
        if(b->getInteger()!=0) {
            res = new CalcStackItemInt(a->getInteger()/b->getInteger(), b->getBase());
        }
    }
    else {
        // Even if b is actually integer, we may use getFloat as it does a cast
        // Also, if for the purposes of comparison, b is not 0.0, then it shouldn't
        // be for the purposes of division, either.
        if(b->getFloat() != 0.0) {
            res = new CalcStackItemFloat(a->getFloat()/b->getFloat());
        }
    }

    if(status != 0) {
        *status = (res!=0);
    }

    return res;
}
