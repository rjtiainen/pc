/* Programmer's Calculator
 *
 * (C) 2013 Risto Tiainen
 *
 * Licensed under the GNU General Public License V3
 *
 */
#include "programmerscalculator.h"
#include "ui_programmerscalculator.h"

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
        //ui->stackListWidget->addItem(calcStack->top()->getString());    // Replace this with get from stack
        updateDisplay();
        ui->inputEdit->clear();
    }
}

void ProgrammersCalculator::updateDisplay(void) {
    calcStack->exportToStringList(ui->stackListWidget);
}
