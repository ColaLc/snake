#include "view.h"
#include "ui_view.h"
#include "qdebug.h"


bool isAi=false;  //全局变量
int speed=600;

view::view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::view)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
               QBrush(QPixmap(":/image/view.jpg").scaled(// 缩放背景图.
                   this->size(),
                   Qt::IgnoreAspectRatio,
                   Qt::SmoothTransformation)));             // 使用平滑的缩放方式
       this->setPalette(palette);                           // 给widget加上背景图

}

view::~view()
{
    delete ui;
}



void view::on_startBtn_clicked()
{
    wid=new Widget;
    wid->show();
    this->hide();
    connect(wid,&Widget::signal_window,this,&view::slot_reShow);
}

void view::on_exitBtn_clicked()
{
    //this->close();
    QApplication *app;
    app->exit(0);
}

void view::slot_reShow(QString score)
{
    this->show();
    ui->labelScore->setText(score);
}



void view::on_pushButton_clicked()
{
    speed=ui->lineEdit->text().toInt();
    isAi=true;
    wid=new Widget;
    wid->show();
    this->hide();
    connect(wid,&Widget::signal_window,this,&view::slot_reShow);    
}
