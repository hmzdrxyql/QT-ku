#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStack>
#include <QKeyEvent>
#include <QPushButton>
#include <QMap>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;

    QStack<QString> operands;
    QStack<QString> opcodes;

    QString calculation();

    QMap<int, QPushButton*> btnNums;
    QMap<int, QPushButton*> btnShuang;


private slots:

    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void btnBtdianClicked();
    void btnBtshanchuClicked();
    void btnBtCClicked();
    void btnBtdengyuClicked();
    void btnBtCEClicked();

    virtual void keyPressEvent(QKeyEvent *event);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
