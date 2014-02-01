#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "calcstack.h"

class Parser {
public:
    // Parser owns the calc stack and is responsible for pushing and popping
    // stuff into it. Main program handles displaying the stack.
//    Parser(CalcStack* _cstack) {
//        cstack = _cstack;
//    }
    virtual bool parse(const QString& in) = 0;
protected:
    CalcStack* cstack;
};

#endif // PARSER_H
