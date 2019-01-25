#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    ui->label_2->setText(QString::number(score));
}

GameOver::~GameOver()
{
    delete ui;
}



