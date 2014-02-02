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
