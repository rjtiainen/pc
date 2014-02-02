#ifndef RPNPARSER_H
#define RPNPARSER_H

#include "QList"
#include "parser.h"

class RPNParser : public Parser
{
public:
    RPNParser(CalcStack* _cstack);
    bool parse(const QString& in);

    typedef bool (*checkFunction)(RPNParser*, QString& s);
private:
    // List of functions to be called for every new input.
    // Must return true if the function was able to correctly handle the input,
    // false otherwise.
    static checkFunction f[];

    // Functions for the list
    static bool clr(RPNParser* p, QString& s);
    static bool add(RPNParser* p, QString& s);
    static bool sub(RPNParser* p, QString& s);
    static bool hex(RPNParser* p, QString& s);
    static bool real(RPNParser* p, QString& s);
    static bool integer(RPNParser* p, QString& s);
    static bool empty(RPNParser* p, QString& s);
};

#endif // RPNPARSER_H
