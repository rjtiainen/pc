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

#endif // CALCSTATEITEM_H
