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

#include "programmerscalculator.h"
#include "ui_programmerscalculator.h"
#include "version.h"
#include <QTextEdit>
#include <QFontMetricsF>
#include <QFile>
#include <QClipboard>

#include <QDebug>


ProgrammersCalculator::ProgrammersCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammersCalculator)
{
    ui->setupUi(this);
    this->setWindowTitle("Programmer\'s Calculator "+VERSIONGetVersion());

    calcStack = new CalcStack();
    parser = new RPNParser(calcStack);

    connect(ui->inputEdit, SIGNAL(returnPressed()), this, SLOT(newInput()));

    ui->radixListWidget->addItem("Programmer's Calculator");
    ui->radixListWidget->addItem("");
    ui->radixListWidget->addItem("Copyright 2014-2015, Risto Tiainen");
    ui->radixListWidget->addItem("Free software under the terms of GNU GPL V3");
    ui->radixListWidget->addItem(":help<enter> gives the command list");
    ui->radixListWidget->addItem(":lic<enter> gives the license");
    ui->inputEdit->setFocus();
}

ProgrammersCalculator::~ProgrammersCalculator()
{
    delete ui;
}

void ProgrammersCalculator::newInput(void) {
    QString retMsg = "";
    bool status=parser->parse(ui->inputEdit->text(), retMsg);

    ui->statusBar->clearMessage();

    if(status) {
        updateDisplay();
        ui->inputEdit->clear();
    }
    else if(ui->inputEdit->text()==":q") {
        qApp->exit(0);
    }
    else if(ui->inputEdit->text()==":lic") {
        showText("COPYING");
        ui->inputEdit->clear();
    }
    else if(ui->inputEdit->text()==":help") {
        showText("README");
        ui->inputEdit->clear();
    }
    else if(ui->inputEdit->text()==":c") {
        if(ui->stackListWidget->itemAt(0,0) != 0) {
            QApplication::clipboard()->setText(ui->stackListWidget->itemAt(0,0)->text());
        }
        ui->inputEdit->clear();
    }
    else if(retMsg=="") {
        ui->statusBar->showMessage("Parse error.");
    }
    else {
        ui->statusBar->showMessage(retMsg);
    }
}

void ProgrammersCalculator::updateDisplay(void) {
    union {
        qulonglong u;
        qlonglong i;
        qreal f;
        quint8 c[sizeof(qulonglong)];
    } data;

    calcStack->exportToStringList(ui->stackListWidget);
    ui->radixListWidget->clear();

    if(calcStack->items() > 0) {
        CalcStackItem* i = calcStack->top();
        if(i->isFloat()) {
            data.f = i->getFloat();
        }
        else {
            data.i = i->getInteger();
        }
        ui->radixListWidget->addItem(QString::number(data.i,10));
        ui->radixListWidget->addItem(QString::number(data.u,10));
        ui->radixListWidget->addItem(QString::number(data.u,16).toUpper());
        QString str = "";
        for(int j=(sizeof(data)-1);j>-1;j--) {
            str.append(QString("%1").arg(data.c[j], 8, 2, QChar('0')));
            str.append(" ");
            if(j==4) {
                str.append("\n");
            }
        }
        ui->radixListWidget->addItem(str);

        // Double precision can accurately represent at least 15 digits, but not many more,
        // Show the number here justified to more or less the same length as the binary string
        // above it, which is 4*8 digits + 3 spaces = 35 characters long. Find the accuracy at
        // which the length of the resulting string is 35 chars or less.
        unsigned prec=35;
        while(QString::number(data.f,'g',prec).length() > 34) {
            --prec;
        }
        ui->radixListWidget->addItem(QString::number(data.f,'g',prec));
    }
}

// Show GPL text from the file COPYING. Installer copies
// COPYING to the same directory as the executable.
// todo: Write help file and use this routine to show it as well
void ProgrammersCalculator::showText(const QString fileName) {
    QMainWindow* window = new QMainWindow(this);
    QTextEdit* textEdit = new QTextEdit(window);
    QFile* file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);

    window->setCentralWidget(textEdit);
    window->setWindowTitle("Programmer's Calculator -- " + fileName);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    textEdit->setFont(font);

    if(file->isOpen()) {
        QTextStream* stream = new QTextStream(file);
        QString license = stream->readAll();
        file->close();
        textEdit->setText(license);
    }
    else {
        textEdit->setText("File "+fileName+" not found. Check your installation.");
    }

    window->show();
    // Set the window width to 80 characters + a few pixel margin
    window->setMinimumWidth(textEdit->fontMetrics().width(QString("").leftJustified(80,'x')) + 40);
    window->setMinimumHeight(400);
}
