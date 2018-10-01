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

void Calculator::UpdatingDisplay(QString equation, QString current, QString result)
{
    QString Operation("Operation");
    QString Result("Result");
    QString text("<font size=2>%1</font><br><font size=1>%2</font>");
    ui->Display->setText(text.arg(Operation, Result));
}


//void Calculator::buttonClicked()
//{
//    QPushButton* button = qobject_cast<QPushButton*>(sender());
//    emit digitClicked(button->text()[0].digitValue());
//}

void Calculator::buttonClicked(QString value)
{
    //qDebug() << "Emited value: " << value;
    bool isNumber = false;
    // can be int, float or double or word like "top"
    qreal number = value.toInt(&isNumber);

    if (isNumber) {
      qDebug() << number;

    } else {
      qDebug() << value;

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
