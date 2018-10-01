#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QPushButton>


namespace Ui {
class Calculator;
}

struct GlobalCoors{
        int X;
        int Y;
};

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();
    GlobalCoors Axis;


private:
    Ui::Calculator *ui;

    bool IsMouseDown = false;
    QPoint LastMousePosition;
    QPoint MousePos;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent * event);


private slots:
    void on_QuitButton_clicked();
    //void buttonClicked();
    void buttonClicked(QString value);
    void digitClicked(int);
    void operatorClicked(QString);
    void UpdatingDisplay(QString equation, QString current, QString result);


};

#endif // CALCULATOR_H
