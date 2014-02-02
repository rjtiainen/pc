/* Programmer's Calculator
 *
 * (C) 2013 Risto Tiainen
 *
 * Licensed under the GNU General Public License V3
 *
 */
#include "programmerscalculator.h"
#include "ui_programmerscalculator.h"

#include <QDebug>

ProgrammersCalculator::ProgrammersCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgrammersCalculator)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Programmer\'s Calculator"));

    calcStack = new CalcStack();
    parser = new RPNParser(calcStack);

    connect(ui->inputEdit, SIGNAL(returnPressed()), this, SLOT(newInput()));

    ui->radixListWidget->addItem("Programmer's Calculator");
    ui->radixListWidget->addItem("");
    ui->radixListWidget->addItem("(C) 2013-2014 Risto Tiainen");
    ui->radixListWidget->addItem("Free software under the terms of GNU GPL V3");
    ui->inputEdit->setFocus();
}

ProgrammersCalculator::~ProgrammersCalculator()
{
    delete ui;
}

void ProgrammersCalculator::newInput(void) {
    bool status=parser->parse(ui->inputEdit->text());

    if(status) {
        ui->statusBar->clearMessage();
        updateDisplay();
        ui->inputEdit->clear();
    }
    else {
        ui->statusBar->showMessage("Parse error.");
    }
}

void ProgrammersCalculator::updateDisplay(void) {
    bool status;

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
            data.f = i->getString().toDouble();
            //ui->radixListWidget->addItem(QString::number(data.f,'g'));
            //ui->radixListWidget->addItem(QString::number(data.u, 10));  // Show the memory contents
            // Binary missing
        }
        else if(i->isUnsigned()) {
            data.u = i->getString().toULongLong(&status, i->getBase());
        }
        else {
            data.i = i->getString().toLongLong(&status, i->getBase());
            //ui->radixListWidget->addItem(QString("%1").arg(data.u, 8, 16, QChar('0')).toUpper());
            //ui->radixListWidget->addItem(QString::number(data.u,2));
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
        ui->radixListWidget->addItem(QString::number(data.f,'g'));

    }

}
