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

    connect(ui->EqualButton, SIGNAL(clicked()), this, SLOT(on_EqualButton_clicked));

    // Getting all buttons && connecting them to the slot mapping
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    //qDebug() << buttons.size();
    connect(ui->MemClearButton, SIGNAL(clicked()), this, SLOT(on_ClearButton_clicked())); /// Old Signal style but usefull    
    connect(ui->ChangeSignButton, SIGNAL(clicked()), this, SLOT(on_ChangeSignButton_clicked));
    connect(ui->DelButton, SIGNAL(clicked()), this, SLOT(on_DelButton_clicked));

    for (const auto *button: buttons)
    {
        if (button->objectName() == "EqualButton" || button->objectName() == "MemStoreButton"
                || button->objectName() == "MemClearButton" || button->objectName() == "DelButton"){
            continue;
        }

        //qDebug() << " - " << button->objectName();
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
    close();
}


void Calculator::buttonClicked(QString value)
{
    //qDebug() << "Emited value: " << value;
    bool isNumber = false;
    // can be int, float or double or word like "top"
    qreal number = value.toInt(&isNumber);
    QString DText = ui->Display->text();
    QString DTextCopy = DText;

    if (isNumber) {

        if (DText == "0" || switchAfterOperatorPress == true)
            {
            DText = "";
            }

        else if (LastResult.size() > 0){
            StoredResult = LastResult;
            LastResult = "";
            DText = "";
        }

        if (switchAfterOperatorPress == false && DTextCopy != "0"){
            ui->Display->setText(DTextCopy + QString::number(int(number)));
            CurrentOperation = ui->Display->text();
        }
        else{
            ui->Display->setText(DText + QString::number(int(number)));
            CurrentOperation = ui->Display->text();
        }

        ///
        switchAfterOperatorPress = false;

    }
    else {

        qDebug() << ui->Display->text();
        LastOperation = CurrentOperation;

        if (StoredResult.size() > 0){
          LastOperation = StoredResult;
        }

      CurrentOperator = value;
      switchAfterOperatorPress = true;
    }
}


void Calculator::on_EqualButton_clicked()
{
    if (LastOperation.length() > 0 && CurrentOperation.length() > 0){
        LastResult = DoMath();
        ui->Display->setText(LastResult);
        StoredResult = LastResult;
    }
}


void Calculator::on_ClearButton_clicked()
{
    LastOperation = "";
    StoredResult = "";
    LastResult = "";
    CurrentOperation = "";
    LastOperator = "";
    LastOperation = "";
    ui->Display->setText("0");
    switchAfterOperatorPress = false;
}

QString Calculator::DoMath(){
    if (CurrentOperator == "+"){
        return QString::number(LastOperation.toInt() + CurrentOperation.toInt());
    }
    else if (CurrentOperator == "-"){
        return QString::number(LastOperation.toInt() - CurrentOperation.toInt());
    }
    else if (CurrentOperator == "X"){
        return QString::number(LastOperation.toInt() * CurrentOperation.toInt());
    }
    else if (CurrentOperator == "/"){
        return QString::number(LastOperation.toInt() / CurrentOperation.toInt());
    }
    else{
        return "No Math operator";
    }
}


void Calculator::on_ChangeSignButton_clicked()
{
    QString MinusOneString = QString::number(ui->Display->text().toInt() * -1);
    ui->Display->setText(MinusOneString);
    StoredResult = MinusOneString;
}

void Calculator::on_DelButton_clicked()
{
    QString text = ui->Display->text();
    if (text == "0"){return;}

    //
    if (text.length() <= 1){
       ui->Display->setText("0");
       return;
    }

    text.resize(text.length() - 1);
    ui->Display->setText(text);
}
