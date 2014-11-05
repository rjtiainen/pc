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

#ifndef VERSION_H
#define VERSION_H

#include <QString>

typedef struct {
    unsigned major;
    unsigned minor;
    unsigned internal;
} ProgramVersion;

const ProgramVersion programVersion = {0, 6, 5};

QString VERSIONGetVersion(void) {
    return QString::number(programVersion.major)+"."+QString::number(programVersion.minor)+"."+QString::number(programVersion.internal);
}

#endif // VERSION_H
