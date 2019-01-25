#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
extern int score;

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = 0);
    ~GameOver();

private slots:



private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
