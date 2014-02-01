#ifndef CALCSTACKITEM_H
#define CALCSTACKITEM_H

class CalcStackItem
{
public:
    virtual QString getString(void) = 0;
    virtual bool isInteger(void) { return false; }
    virtual bool isFloat(void) { return false; }
    virtual unsigned getBase(void) { return 10; }
};

class CalcStackItemInt : public CalcStackItem
{
public:
    CalcStackItemInt(unsigned long _val=0, unsigned _base=10) : CalcStackItem() {
        val = _val;
        base = _base;
    }
    bool isInteger(void) { return true; }
    unsigned getBase(void) { return base; }
    QString getString(void) {
        return QString::number(val);    // \todo Base etc.
    }

protected:
    unsigned long val;
    unsigned base;
};

#endif // CALCSTATEITEM_H
