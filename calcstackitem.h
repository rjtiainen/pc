#ifndef CALCSTACKITEM_H
#define CALCSTACKITEM_H

#include <memory>

class CalcStackItem
{
public:
    virtual QString getString(void) const = 0;
    virtual bool isInteger(void) const { return false; }
    virtual bool isFloat(void) const { return false; }
    virtual unsigned getBase(void) const { return 10; }
    virtual qlonglong getInteger(void) const = 0;
    virtual qreal getFloat(void) const = 0;
    virtual void setInteger(qlonglong val) = 0;
    virtual void setFloat(qreal val) = 0;

    // Basic arithmetic operators (+, -, *, /)
    // These return a new object such that integer-integer operations
    // produce integers, and anything involving a float produces a float.
    static CalcStackItem* add(const CalcStackItem* a, const CalcStackItem* b, bool* status = 0);
    static CalcStackItem* sub(const CalcStackItem* a, const CalcStackItem* b, bool* status = 0);
    static CalcStackItem* mul(const CalcStackItem* a, const CalcStackItem* b, bool* status = 0);
    static CalcStackItem* div(const CalcStackItem* a, const CalcStackItem* b, bool* status = 0);
};

class CalcStackItemInt : public CalcStackItem
{
friend class CalcStackItemFloat;
public:
    CalcStackItemInt(qlonglong _val=0, unsigned _base=10) : CalcStackItem() {
        sval = _val;
        base = _base;
    }
    bool isInteger(void) const { return true; }
    unsigned getBase(void) const { return base; }
    qlonglong getInteger(void) const { return sval; }
    qreal getFloat(void) const { return qreal(sval); }
    void setInteger(qlonglong val) { this->sval = val; }
    void setFloat(qreal val) { this->sval = qlonglong(val); }
    QString getString(void) const;
protected:
    qlonglong sval;
    unsigned base;
};

class CalcStackItemFloat : public CalcStackItem
{
friend class CalcStackItemInt;
public:
    typedef qreal real;
    CalcStackItemFloat(qreal _val=0.0) : CalcStackItem() {
        val = _val;
    }
    bool isFloat(void) const { return true; }
    qlonglong getInteger(void) const { return qlonglong(val); }
    qreal getFloat(void) const { return val; }
    void setInteger(qlonglong val) { this->val = qreal(val); }
    void setFloat(qreal val) { this->val = val; }
    // We could play around with precision/format, won't do that
    // for now (probably not needed anyway)
    QString getString(void) const;
protected:
    real val;
};


#endif // CALCSTATEITEM_H
