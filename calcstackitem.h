#ifndef CALCSTACKITEM_H
#define CALCSTACKITEM_H

class CalcStackItem
{
public:
    virtual QString getString(void) = 0;
    virtual bool isInteger(void) { return false; }  // Is SIGNED integer?
    virtual bool isUnsigned(void) { return false; }
    virtual bool isFloat(void) { return false; }
    virtual unsigned getBase(void) { return 10; }
};

class CalcStackItemInt : public CalcStackItem
{
public:
    typedef qlonglong sInt;     // Type for signed ints...
    typedef qulonglong uInt;    // and unsigned
    CalcStackItemInt(uInt _val=0, unsigned _base=10) : CalcStackItem() {
        uval = _val;
        base = _base;
        isSigned = false;
    }
    CalcStackItemInt(sInt _val=0, unsigned _base=10) : CalcStackItem() {
        sval = _val;
        base = _base;
        isSigned = true;
    }
    bool isInteger(void) { return isSigned; }
    bool isUnsigned(void) { return !isSigned; }
    unsigned getBase(void) { return base; }
    QString getString(void) {
        if(isSigned) {
            return QString::number(sval);    // \todo Base
        }
        else {
            return QString::number(uval);
        }
    }

protected:
    sInt sval;
    uInt uval;
    unsigned base;
    bool isSigned;
};

class CalcStackItemFloat : public CalcStackItem
{
public:
    typedef qreal real;
    CalcStackItemFloat(qreal _val=0.0) : CalcStackItem() {
        val = _val;
    }
    bool isFloat(void) { return true; }
    // We could play around with precision/format, won't do that
    // for now (probably not needed anyway)
    QString getString(void) {
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

protected:
    real val;
};

#endif // CALCSTATEITEM_H
