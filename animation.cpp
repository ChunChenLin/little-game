#include "animation.h"
#include <QPainter>
#include <QPixmap>

animation::animation(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(70,70);
    i=0;
    j=1;
    animationImg[0] = ":/Image/bird1.png";
    animationImg[1] = ":/Image/bird2.png";
    animationImg[2] = ":/Image/bird3.png";
}

animation::~animation(){}

void animation::paintEvent(QPaintEvent *)
{
    QPixmap pix;
    QPainter painter(this);
    if(i == 1)
    {
        pix.load(animationImg[0]);
        //painter.drawPixmap(0,0,35,35,pix);
        i++;
    }
    else if(i == 2)
    {
        pix.load(animationImg[1]);
       // painter.drawPixmap(0,0,35,35,pix);
        i++;
    }
    else
    {
        pix.load(animationImg[2]);
       // painter.drawPixmap(0,0,35,35,pix);
        i = 1;
    }
}
