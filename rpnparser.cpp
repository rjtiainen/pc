#include "rpnparser.h"
#include <QDebug>

// Check function table for the parser.
// 1. Check for known functions and operators
// 2. Check for hexadecimal and binary prefixes
// 3. Check for decimal point
// 4. Check for valid integer
RPNParser::checkFunction RPNParser::f[] = {
    clr,
    add,
    sub,
    hex,
    real,
    integer,
    empty,
    (checkFunction)0    // terminator, do not remove
};

RPNParser::RPNParser(CalcStack* _cstack)
{
    cstack = _cstack;
}

bool RPNParser::parse(const QString &in) {
    bool status = false;
    QString s = in;
    checkFunction* fp = &f[0];
    s.replace(" ","");  // Get rid of whitespace

    // Here be parsing algorithm
    // RPN is the easy one and even that is a bit of a bitch
    while(*fp != (checkFunction)0) {
        if((*fp)(this,s)) {
            status=true;
            break;
        }
        fp++;
    }

    return status;
}

bool RPNParser::clr(RPNParser *p, QString &s) {
    bool status = false;

    if(s == "c") {
        p->cstack->clear();
        status=true;
    }

    return status;
}

// Int + Int = Int, Int + Float = Float, Float + Float = Float
bool RPNParser::add(RPNParser* p, QString& s) {
    bool status = false;
    CalcStackItem *a,*b,*c;

    if(s == "+") {
        // Do the math if there is enough stuff in the stack
        if(p->cstack->items() >= 2) {
            a = p->cstack->popItem();
            b = p->cstack->popItem();
            if(a->isInteger() && b->isInteger()) {
                qlonglong i = a->getString().toLongLong(&status,a->getBase());
                if(status) {
                    i += b->getString().toLongLong(&status,b->getBase());
                }
                if(status) {
                    // Which of the differing bases to choose? Pick the topmost one.
                    c = new CalcStackItemInt(i, a->getBase());
                    p->cstack->pushItem(c);
                }
            }
        }
        // a and b are gone, free the memory
        delete a;
        delete b;
    }

    return status;
}

// Int + Int = Int, Int + Float = Float, Float + Float = Float
// Works the wrong way around, fix it.
bool RPNParser::sub(RPNParser* p, QString& s) {
    bool status = false;
    CalcStackItem *a,*b,*c;

    if(s == "-") {
        // Do the math if there is enough stuff in the stack
        if(p->cstack->items() >= 2) {
            a = p->cstack->popItem();
            b = p->cstack->popItem();
            if(a->isInteger() && b->isInteger()) {
                qlonglong i = b->getString().toLongLong(&status,b->getBase());
                if(status) {
                    i -= a->getString().toLongLong(&status,a->getBase());
                }
                if(status) {
                    // Which of the differing bases to choose? Pick the topmost one.
                    c = new CalcStackItemInt(i, a->getBase());
                    p->cstack->pushItem(c);
                }
            }
        }
        // a and b are gone, free the memory
        delete a;
        delete b;
    }

    return status;
}

bool RPNParser::hex(RPNParser *p, QString &s) {
    return false;
}

bool RPNParser::real(RPNParser *p, QString &s) {
    bool status=false;

    // If there is exactly 1 decimal point in the number,
    // it may be a float.
    if(s.count('.') == 1) {
        qreal f = s.toDouble(&status);
        if(status) {
            CalcStackItem* newItem = new CalcStackItemFloat(f);
            p->cstack->pushItem(newItem);
        }
    }
    return status;
}

bool RPNParser::integer(RPNParser* p, QString& s) {
    bool status = false;
    qlonglong i = s.toLongLong(&status, 10);

    //qDebug() << status;    // TEST

    if(status) {
        CalcStackItem* newItem = new CalcStackItemInt(i);
        p->cstack->pushItem(newItem);
        status = true;
    }

    return status;
}

bool RPNParser::empty(RPNParser *p, QString &s) {
    bool status=false;

    // Duplicate the topmost item in the stack
    if(s=="") {
        // Once again, I don't know how to do this properly in C++.
        // Will have to switch-case all derived CalcStackItem classes in
        // practice.
        if(p->cstack->top()->isFloat()) {
            // CalcStackItemFloat* i = new CalcStackItemFloat((const CalcStackItemFloat&)*p->cstack->top());
        }
        else {
            CalcStackItemInt* i = new CalcStackItemInt((const CalcStackItemInt&)*p->cstack->top());
            p->cstack->pushItem(i);
        }

        status=true;
    }

    return status;
}
