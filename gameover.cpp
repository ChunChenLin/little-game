#include "gameover.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QPainter>

gameover::gameover(QWidget *parent) : QWidget(parent)
{
    //win_width = 380;
    //win_height = 450;
    this->setFixedSize(380,450);
}
gameover::~gameover() {}

void gameover::paintEvent(QPaintEvent *)
{
    QPixmap gameoverImg;
    QPainter painter(this);
    gameoverImg.load(":/Image/gameover.png");
    painter.drawPixmap(0,0,380,450,gameoverImg);

    QFont font = painter.font() ;
    font.setPointSize(40);
    painter.setFont(font);
    //int num_d = (int)score;
    sprintf(num, "%d", score);
    painter.drawText(150,200,100,75,Qt::AlignLeft,num);
}



