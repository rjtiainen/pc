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
