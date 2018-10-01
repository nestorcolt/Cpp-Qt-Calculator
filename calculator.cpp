#include "calculator.h"
#include "ui_calculator.h"
#include <QtWidgets>
#include <QtGui>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <iostream>
#include <QString>

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::Calculator)
{

    ui->setupUi(this);
    setObjectName("Colt Calculator Borderless");


    // Getting all buttons && connecting them to the slot mapping
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    qDebug() << buttons.size();

    for (const auto *button: buttons)
    {
        qDebug() << " - " << button->objectName();
        ///Connect
        //connect(but, SIGNAL(clicked()), this, SLOT(buttonClicked())); /// Old Signal style but usefull
        // new lambda expression
        QString digit = button->text();
        connect(button, &QPushButton::clicked,
                [this, digit]()
                {
                    buttonClicked(digit);
                }
        );
    }
}


Calculator::~Calculator()
{
    delete ui;
}


void Calculator::resizeEvent(QResizeEvent  *event)
{
    QPixmap pixmap(this->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(pixmap.rect(), 18, 18);
    this->setMask(pixmap.mask());
    painter.end();
    event->accept();
}

void Calculator::mousePressEvent(QMouseEvent *event)
{
    if (!this->underMouse()){return;}
    if (event->button() == Qt::LeftButton)
    {
        IsMouseDown = true;
        LastMousePosition = event->pos();
        Axis.X = event->x();
        Axis.Y = event->y();
        //qDebug() << "MousePressInside";
        event->accept();
    }
}

void Calculator::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton) {
        IsMouseDown = false;
    }

}

void Calculator::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->underMouse()){return;}
    if (IsMouseDown)
    {
        MousePos = event->globalPos();
        move(event->globalX() - Axis.X,event->globalY() - Axis.Y);
        event->accept();
    }
}

void Calculator::on_QuitButton_clicked()
{
    qDebug() << "Closing Calculator";
    close();

}

void Calculator::UpdatingDisplay(QString oper, int equation)
{
    QString Operation(QString::number(equation));
    QString text("<font size=2>%1</font><br><font size=1>%2</font>");

    int resultMath = DoMath(oper, equation);
    ui->Display->setText(text.arg(Operation, QString::number(resultMath)));
}


void Calculator::buttonClicked(QString value)
{
    //qDebug() << "Emited value: " << value;
    bool isNumber = false;
    // can be int, float or double or word like "top"
    qreal number = value.toInt(&isNumber);

    if (isNumber) {
      //qDebug() << number;
        QString DText = ui->Display->text();
        if (DText == "0.0"){DText = "";}
        ui->Display->setText(DText + value);
        Current = ui->Display->text().toInt();

    }
    else {
      qDebug() << value;
      UpdatingDisplay(value, Current);
    }
}

void Calculator::digitClicked(int value){
    //qDebug() << "Click Emit";
    //qDebug() << value;
    ui->Display->setText(QString::number((value)));
}

void Calculator::operatorClicked(QString value){
    //qDebug() << "Click Emit";
    //qDebug() << value;
    ui->Display->setText(QString(value));
}

int Calculator::DoMath(QString oper, int oper_1){

    int math;
    int firstArg = oper_1;
    int secondArg = Current;

    if (QString::compare(oper, "+", Qt::CaseInsensitive) == 0){
        math = firstArg + secondArg;
        return math;
    }
    else if (QString::compare(oper, "-", Qt::CaseInsensitive)== 0){
        math = firstArg - secondArg;
        return math;
    }
    else if (QString::compare(oper, "X", Qt::CaseInsensitive)== 0){
        math = firstArg * secondArg;
        return math;
    }
    else if (QString::compare(oper, "/", Qt::CaseInsensitive)== 0){
        math = firstArg / secondArg;
        return math;
    }
    else if (QString::compare(oper, "+/-", Qt::CaseInsensitive)== 0){
        math = firstArg * -1;
        return math;
    }
    else if (QString::compare(oper, "=", Qt::CaseInsensitive)== 0){
        math = firstArg;
        return math;
    }
    else{
        math = firstArg;
        return math;
    }

}
