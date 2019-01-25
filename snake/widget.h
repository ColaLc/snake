#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QTime>
#include <gameover.h>
#include <QPushButton>
#include <QList>
#include "astar_formal.h"


extern int score;
extern bool isAi;
extern int speed;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void moveSnakeHead();
    void creatFood();
    void addSnake();
    bool checkEatFood();  //
    void snakeEnd();
    void stopGame();
    void initialization();  //初始化参数
    bool canFindTail();
    bool canFindFood();

    //寻路
    void setBarrier();
    void cycleRun();//  循环跑圈

protected:
    void paintEvent(QPaintEvent *p);
    void timerEvent(QTimerEvent *t);
    void keyPressEvent(QKeyEvent *k);

signals:
    void signal_window(QString);

private slots:
    void on_pushButton_clicked();
    void slot_quit();

private:
    Ui::Widget *ui;

    QPushButton *btn;

    int id;  //定时器
    int m_snakeX,m_snakeY;
    int m_level;
    int m_snakeWidth,m_snakeHeight; //蛇大小

    char m_direction;

    QPoint m_snakeHead;
    QPoint m_food;

    QList<QPoint> m_pathFindFood;
    QList<QPoint> m_pathTail;
    QList<QPoint>snake;

    bool isFindWay=true;
    bool isFindTail=true;
    bool status=true;


};

#endif // WIDGET_H
