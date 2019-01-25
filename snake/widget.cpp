#include "widget.h"
#include "ui_widget.h"
#include "qdebug.h"
#include "mymapp.h"
#include <QRectF>

int score=0;            //全局变量
extern int myMap[35][30];

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("IceCola");
    initialization();
    ui->lineEdit->setText("0");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime())); //随机数
    creatFood();
    m_snakeHead=QPoint(150,150);
    snake.push_back(QPoint(150,165));
    canFindFood();
    canFindTail();
//    snake.push_back(QPoint(150,180));

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initialization()
{
    id=startTimer(speed); //1s
    m_snakeX=150;
    m_snakeY=150;
    m_snakeWidth=15;
    m_snakeHeight=15;
    m_direction='w';
}

void Widget::moveSnakeHead()
{
    if(isAi==false)
    {
    if(m_direction=='w') m_snakeY=m_snakeY-15;
    else
        if(m_direction=='s') m_snakeY=m_snakeY+15;
    else
            if(m_direction=='a') m_snakeX=m_snakeX-15;
    else
                if(m_direction=='d') m_snakeX=m_snakeX+15;


    m_snakeHead=QPoint(m_snakeX,m_snakeY);

    }

/**************自动寻路*************/
    if(isAi)
    {
        if(canFindFood()==true)  //能找到食物
        {
                QPoint lastPos=m_snakeHead;
                m_snakeHead=m_pathFindFood.first();
                if(canFindTail()==false) //吃到食物后不能找到尾巴
                {
                    m_snakeHead=lastPos;
                    canFindTail();
                    m_snakeHead=m_pathTail.first();  //寻找蛇头
                }
        }
        else   //无法找到食物
        {
            if(canFindTail()==true)
            m_snakeHead=m_pathTail.first();
        }
    }

}
void Widget::paintEvent(QPaintEvent *p)
{

     QPainter painter(this);
     QPen pen;
     pen.setWidth(10);
     painter.drawPixmap(0,0,535,460,QPixmap(":/image/ui.PNG"));  //35  30


     //绘制食物
     painter.drawPixmap(m_food.x(),m_food.y(),m_snakeWidth,
     m_snakeHeight,QPixmap(":/image/food.PNG"));

     //绘制蛇身
      for(int i=0;i<snake.size()-1;i++)
      {
         if(i%3==0)
         {
             pen.setColor(Qt::white);
             painter.setPen(pen);
             painter.drawLine(snake[i].x()+7,snake[i].y()+7,snake[i+1].x()+7,snake[i+1].y()+7);
         }
         else
          {
             pen.setColor(Qt::gray);
             painter.setPen(pen);
             painter.drawLine(snake[i].x()+7,snake[i].y()+7,snake[i+1].x()+7,snake[i+1].y()+7);

          }
      }

     //绘制蛇头
       painter.drawPixmap(m_snakeHead.x(),m_snakeHead.y(),m_snakeWidth,
       m_snakeHeight,QPixmap(":/image/headW.png"));

}
void Widget::timerEvent(QTimerEvent *t)
{
    if(status==true)

    if(t->timerId()==id)  //时间确定难度
    {
        checkEatFood();
        snake.push_front(m_snakeHead);
        //if(checkEatFood()==false)
        {
            snake.removeLast();
        }
        moveSnakeHead();  //蛇头方向
        snakeEnd();
        update();

    }
}
void Widget::keyPressEvent(QKeyEvent *k)//键盘按键读取
{
    switch (k->key())
    {
    case Qt::Key_W : m_direction='w'; break;
    case Qt::Key_S : m_direction='s'; break;
    case Qt::Key_A : m_direction='a'; break;
    case Qt::Key_D : m_direction='d'; break;
    }
}

void Widget::setBarrier()  //设置障碍物
{
    int x;
    int y;
    for(int i=0;i<35;i++)
    for(int j=0;j<30;j++)
    {
        myMap[i][j]=0;

    }
    //添加障碍物蛇坐标
    for(int i=0;i<snake.size()-1;i++) //障碍物
    {
                    x=snake[i].x()/15;
                    y=snake[i].y()/15;
                    myMap[x][y]=1;
    }
}

void Widget::creatFood() //生成随机实物
{
    bool reCreat=true;
    while(reCreat==true)
    {
        reCreat=false;
        int randX=qrand()%35;
        int randY=qrand()%30;
        m_food=QPoint(randX*m_snakeWidth,randY*m_snakeHeight);
        QList<QPoint>::iterator i;
        for(i=snake.begin();i!=snake.end();i++)
        {
            if(randX==(*i).x()/15  &&  randY==(*i).y()/15)  //重叠
            {
                reCreat=true;  //
                break;
            }
        }
    }

}
bool Widget::checkEatFood()  //吃到食物
{
    int snX,snY;
    int foodX,foodY;
    snX=m_snakeHead.x();
    snY=m_snakeHead.y();
    foodX=m_food.x();
    foodY=m_food.y();
    if(snX==foodX && snY==foodY)
    {
        creatFood();
        snake.push_back(QPoint(500,500));
        score=score+100;
        ui->lineEdit->setText(QString::number(score));
        return true;
    }
    else
        return false;
}
void Widget::addSnake()     //增加长度
{
    snake.push_back(QPoint(500,500));  //待定
}
void Widget::snakeEnd()     //结束
{
    for(int i=0;i<snake.size()-1;i++)
    {
       if((m_snakeHead.x()==snake[i].x())
           &&(m_snakeHead.y()==snake[i].y()))
       {
           stopGame();
       }
    }

    if(m_snakeHead.x()<0 || m_snakeHead.x()>510 ||
       m_snakeHead.y()<0 || m_snakeHead.y()>444)
    {
        stopGame();
    }

}

void Widget::stopGame()        //结束处理
{
    status=false;
    GameOver *game=new GameOver(this);
    game->setGeometry(100,100,275,190);
    game->show();
    btn=new QPushButton(this);
    btn->setText("QUIT");
    btn->setGeometry(150,250,50,30);
    btn->show();
    connect(btn,&QPushButton::released,this,&Widget::slot_quit);
    //关闭自动寻路
    isAi=false;

}
void Widget::slot_quit()
{
    this->close();
    emit    signal_window(ui->lineEdit->text());
    score=0;
}



void Widget::on_pushButton_clicked()
{
    if(status==true)
    {
        status=false;
        ui->pushButton->setText("开始");
    }

    else
        {
            status=true;
            ui->pushButton->setText("暂停");
            //检测难度
            if(ui->comboBox->currentText()=="简单") m_level=1;
            else if(ui->comboBox->currentText()=="困难") m_level=2;
            else if(ui->comboBox->currentText()=="极限") m_level=3;

            switch (m_level) {
            case 1:
                id=startTimer(600);
                break;
            case 2:
                id=startTimer(400);
                break;
            case 3:
                id=startTimer(200);
                break;
            default:
                break;
            }

    }
}

bool Widget::canFindFood()
{
    setBarrier();
    //myMap[snake.last().x()/15][snake.last().y()/15]=1;
    int endX=m_food.x()/15;
    int endY=m_food.y()/15;
    int begX=m_snakeHead.x()/15;
    int begY=m_snakeHead.y()/15;

    Astar findFood;
    findFood.setBeginPos(begX,begY);
    findFood.setEndPos(endX,endY);
    QPoint pos;
    m_pathFindFood.clear();
    while(1)
    {
        findFood.creatNextPos();
        findFood.selectMin();

        if(findFood.currPos->pos.x==findFood.endPos.x  &&  findFood.currPos->pos.y==findFood.endPos.y)      //找到终点
        {
             //找到目标
            while(findFood.currPos->pParent)
            {
               pos.setX(findFood.currPos->pos.x*15);
               pos.setY(findFood.currPos->pos.y*15);
               m_pathFindFood.push_front(pos);
               findFood.currPos=findFood.currPos->pParent;
            }

            return true;
        }
        if (findFood.openList.size() == 0 )  //无法找到
        {
            return false;
        }

    }
}


bool Widget::canFindTail()
{
    setBarrier();

    int endX=snake.last().x()/15;
    int endY=snake.last().y()/15;
    int begX=m_snakeHead.x()/15;
    int begY=m_snakeHead.y()/15;

    Astar findTail;
    findTail.setBeginPos(begX,begY);
    findTail.setEndPos(endX,endY);
    QPoint pos;
    m_pathTail.clear();
    while(1)
    {
        findTail.creatNextPos();
        findTail.selectMin();
        if(findTail.currPos->pos.x==findTail.endPos.x  &&  findTail.currPos->pos.y==findTail.endPos.y)      //找到终点
        {
            while(findTail.currPos->pParent)
            {
               pos.setX(findTail.currPos->pos.x*15);
               pos.setY(findTail.currPos->pos.y*15);
               m_pathTail.push_front(pos);
               findTail.currPos=findTail.currPos->pParent;
            }
            return true;
        }
        if (findTail.openList.size() == 0 )  //无法找到
        {
                return false;
        }

    }
}
