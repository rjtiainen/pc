// Programmer's Calculator
//
// Copyright 2014, Risto Tiainen
//
// Programmer's Calculator is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// Programmer's Calculator is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Programmer's Calculator.
// If not, see <http://www.gnu.org/licenses/>.

#ifndef RPNPARSER_H
#define RPNPARSER_H

#include <QList>
#include "parser.h"

class RPNParser : public Parser
{
public:
    RPNParser(CalcStack* _cstack);
    bool parse(const QString& in, QString& out);

    // S is the string to be parsed, err will be set if check recognized the
    // function but was not able to perform the task (insufficient data etc.)
    typedef bool (*checkFunction)(RPNParser* p, QString& s, QString& err);
private:
    // List of functions to be called for every new input.
    // Must return true if the function was able to correctly handle the input,
    // false otherwise.
    static checkFunction f[];

    // Functions for the list
    static bool clr(RPNParser* p, QString& s, QString& err);
    static bool pop(RPNParser* p, QString& s, QString& err);
    static bool swap(RPNParser* p, QString& s, QString& err);
    static bool inv(RPNParser* p, QString& s, QString& err);
    static bool conv(RPNParser* p, QString& s, QString& err);
    static bool asmd(RPNParser* p, QString& s, QString& err);
    static bool logopbin(RPNParser* p, QString& s, QString& err);
    static bool logopun(RPNParser* p, QString& s, QString& err);
    static bool power(RPNParser* p, QString& s, QString& err);
    static bool trig(RPNParser* p, QString& s, QString& err);
    static bool constant(RPNParser* p, QString& s, QString& err);
    static bool hex(RPNParser* p, QString& s, QString& err);
    static bool bin(RPNParser *p, QString &s, QString& err);
    static bool real(RPNParser* p, QString& s, QString& err);
    static bool integer(RPNParser* p, QString& s, QString& err);
    static bool scientific(RPNParser* p, QString& s, QString& err);
    static bool empty(RPNParser* p, QString& s, QString& err);
};

#endif // RPNPARSER_H
