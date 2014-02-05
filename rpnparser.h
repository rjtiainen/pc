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
    bool parse(const QString& in);

    typedef bool (*checkFunction)(RPNParser*, QString& s);
private:
    // List of functions to be called for every new input.
    // Must return true if the function was able to correctly handle the input,
    // false otherwise.
    static checkFunction f[];

    // Functions for the list
    static bool clr(RPNParser* p, QString& s);
    static bool swap(RPNParser* p, QString& s);
    static bool inv(RPNParser* p, QString& s);
    static bool conv(RPNParser* p, QString& s);
    static bool asmd(RPNParser* p, QString& s);
    static bool hex(RPNParser* p, QString& s);
    static bool bin(RPNParser *p, QString &s);
    static bool real(RPNParser* p, QString& s);
    static bool integer(RPNParser* p, QString& s);
    static bool empty(RPNParser* p, QString& s);
};

#endif // RPNPARSER_H
