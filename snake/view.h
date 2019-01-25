#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class view;
}

class view : public QWidget
{
    Q_OBJECT

public:
    explicit view(QWidget *parent = 0);
    ~view();
    Widget *wid;


private slots:
    void on_startBtn_clicked();

    void on_exitBtn_clicked();
    void slot_reShow(QString);

    void on_pushButton_clicked();

private:
    Ui::view *ui;
};

#endif // VIEW_H
