#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums = {
                {Qt::Key_0, ui->bt0},
                {Qt::Key_1, ui->bt1},
                {Qt::Key_2, ui->bt2},
                {Qt::Key_3, ui->bt3},
                {Qt::Key_4, ui->bt4},
                {Qt::Key_5, ui->bt5},
                {Qt::Key_6, ui->bt6},
                {Qt::Key_7, ui->bt7},
                {Qt::Key_8, ui->bt8},
                {Qt::Key_9, ui->bt9},
              };

    btnShuang = {
                 {Qt::Key_Plus, ui->btjia},
                 {Qt::Key_Minus, ui->btjian},
                 {Qt::Key_Asterisk, ui->btcheng},
                 {Qt::Key_Slash, ui->btchu},
                };

    foreach(auto btn, btnNums)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    foreach(auto btn, btnShuang)
        connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));

    connect(ui->btbaifen, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btx2, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btgen, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->bt1x, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btjiajian, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));

    connect(ui->btshanchu, SIGNAL(clicked()), this, SLOT(btnBtshanchuClicked()));
    connect(ui->btC, SIGNAL(clicked()), this, SLOT(btnBtCClicked()));
    connect(ui->btdengyu, SIGNAL(clicked()), this, SLOT(btnBtdengyuClicked()));
    connect(ui->btCE, SIGNAL(clicked()), this, SLOT(btnBtCEClicked()));
    connect(ui->btdian, SIGNAL(clicked()), this, SLOT(btnBtdianClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton*>(sender())->text();

    if (operand != "")
    {
        operands.push_back(operand);
        operand = "";
        opcodes.push_back(opcode);
    }
    else if (opcodes.size() == 0 && operands.size() != 0)
         opcodes.push_back(opcode);
    else if (opcodes.size() == 1)
    {
        opcodes.pop_front();
        opcodes.push_back(opcode);
    }

    QString result = calculation();

    ui->kuang->setText(result);
}


QString MainWindow::calculation()
{
    double result = 0;
    if(operands.size() == 2 && opcodes.size() > 0)
    {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+")
            result = operand1 + operand2;
        else if(op == "-")
            result = operand1 - operand2;
        else if(op == "×")
            result = operand1 * operand2;
        else if(op == "/")
            result = operand1 / operand2;

        operands.push_back(QString::number(result));
    }
    return QString::number(result);
}


void MainWindow::btnBtdengyuClicked()
{
    if(operands.size() == 1 && opcodes.size() > 0)
        operands.push_back(operand);

    if(operands.size() == 2 && opcodes.size() > 0)
    {
        QString result = calculation();
        ui->kuang->setText(result);
        operand = "";
    }
}


void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if (digit == "0" && operand == "0")
        digit = "";

    if (operand == "0" && digit != "0")
        operand.clear();

    operand += digit;
    ui->kuang->setText(operand);
}


void MainWindow::btnBtdianClicked()
{
    if(!operand.contains(".") && operand != "")
        operand += qobject_cast<QPushButton*>(sender())->text();

    ui->kuang->setText(operand);
}


void MainWindow::btnBtshanchuClicked()
{
    operand = operand.left(operand.length() - 1);
    ui->kuang->setText(operand);
}


void MainWindow::btnBtCClicked()
{
    operands.clear();
    operand.clear();
    opcode.clear();
    opcodes.clear();
    ui->kuang->setText(operand);
}


void MainWindow::btnBtCEClicked()
{
    operand.clear();
    ui->kuang->setText(operand);
}


void MainWindow::btnUnaryOperatorClicked()
{
    double result = 0;
    int y = 0;
    if (operand != "")
    {
        result = operand.toDouble();
        operand = "";
        y = -1;
    }
    else if (operands.size() > 0)
    {
        result = operands.front().toDouble();
        operands.pop_front();
        y = 1;
    }

    QString op = qobject_cast<QPushButton*>(sender())->text();

    if(op == "%")
        result /= 100.0;
    else if(op == "1/x")
        result = 1 / result;
    else if(op == "x^2")
        result *= result;
    else if(op == "√")
        result = sqrt(result);
    else if(op == "±")
        result *= -1;

    if (y == -1)
        operand = QString::number(result);
    else if (y == 1)
        operands.push_back(QString::number(result));

    ui->kuang->setText(QString::number(result));
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach (auto btnKey, btnNums.keys())
        if(event->key() == btnKey)
            btnNums[btnKey]->animateClick();

    foreach (auto btnKey, btnShuang.keys())
        if(event->key() == btnKey)
            btnShuang[btnKey]->animateClick();

    if(event->key() == Qt::Key_Percent)
        ui->btbaifen->animateClick();
    if(event->key() == Qt::Key_Equal)
        ui->btdengyu->animateClick();
    if(event->key() == Qt::Key_Period)
        ui->btdian->animateClick();
    if(event->key() == Qt::Key_Backspace)
        ui->btshanchu->animateClick();
}
