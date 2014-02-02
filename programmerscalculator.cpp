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

    ui->inputEdit->setFocus();
}

ProgrammersCalculator::~ProgrammersCalculator()
{
    delete ui;
}

void ProgrammersCalculator::newInput(void) {
    bool status=parser->parse(ui->inputEdit->text());

    if(status) {
        qDebug() << status;
        updateDisplay();
        ui->inputEdit->clear();
    }
}

void ProgrammersCalculator::updateDisplay(void) {
    calcStack->exportToStringList(ui->stackListWidget);
}
