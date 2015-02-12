// Programmer's Calculator
//
// Copyright 2014-2015, Risto Tiainen
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

#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "calcstack.h"

class Parser {
public:
    // Parser owns the calc stack and is responsible for pushing and popping
    // stuff into it. Main program handles displaying the stack.
    virtual bool parse(const QString& in, QString& out) = 0;
protected:
    CalcStack* cstack;
};

#endif // PARSER_H
