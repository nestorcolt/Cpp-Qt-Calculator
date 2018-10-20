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
#include <QString>

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

    bool switchAfterOperatorPress = false;
    bool IsMouseDown = false;
    bool ZeroFirst = false;

    QPoint LastMousePosition;
    QPoint MousePos;

    QString LastOperator;
    QString LastOperation;
    QString CurrentOperation;
    QString LastResult;
    QString StoredResult;
    QString CurrentOperator;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent * event);



private slots:
    void on_QuitButton_clicked();
    void on_ClearButton_clicked();
    void buttonClicked(QString value);
    void on_EqualButton_clicked();
    QString DoMath();
    void on_ChangeSignButton_clicked();
    void on_DelButton_clicked();
};

#endif // CALCULATOR_H
