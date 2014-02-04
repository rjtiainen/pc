#include <QString>
#include "calcstackitem.h"

QString CalcStackItemInt::getString(void) const {
    QString str="";

    if(base == 16) {
        str="0x"+QString::number(sval, 16);
    }
    else {
        str=QString::number(sval);
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

bool CalcStackItem::add(CalcStackItem** res, const CalcStackItem* a, const CalcStackItem *b) {
    if(a->isInteger() && b->isInteger()) {
        *res = new CalcStackItemInt(a->getInteger()+b->getInteger());
    }
    else {
        *res = new CalcStackItemFloat(a->getFloat()+b->getFloat());
    }

    // Addition always succeeds
    return true;
}

bool CalcStackItem::sub(CalcStackItem** res, const CalcStackItem* a, const CalcStackItem *b) {
    if(a->isInteger() && b->isInteger()) {
        *res = new CalcStackItemInt(a->getInteger()-b->getInteger());
    }
    else {
        *res = new CalcStackItemFloat(a->getFloat()-b->getFloat());
    }

    // Subtraction always succeeds
    return true;
}

bool CalcStackItem::mul(CalcStackItem** res, const CalcStackItem* a, const CalcStackItem *b) {
    if(a->isInteger() && b->isInteger()) {
        *res = new CalcStackItemInt(a->getInteger()*b->getInteger());
    }
    else {
        *res = new CalcStackItemFloat(a->getFloat()*b->getFloat());
    }

    // Multiplication always succeeds
    return true;
}

bool CalcStackItem::div(CalcStackItem** res, const CalcStackItem* a, const CalcStackItem *b) {
    bool status=false;

    if(a->isInteger() && b->isInteger()) {
        if(b->getInteger()!=0) {
            *res = new CalcStackItemInt(a->getInteger()/b->getInteger());
            status=true;
        }
    }
    else {
        // Even if b is actually integer, we may use getFloat as it does a cast
        // Also, if for the purposes of comparison, b is not 0.0, then it shouldn't
        // be for the purposes of division, either.
        if(b->getFloat() != 0.0) {
            *res = new CalcStackItemFloat(a->getFloat()/b->getFloat());
            status = true;
        }
    }

    return status;
}
