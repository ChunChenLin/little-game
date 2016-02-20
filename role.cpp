#include "role.h"


ROLE::ROLE(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(70,70);
    //src=":/Image/bird1.png";
    i=0;//初始狀態
    ROLEImg[0] = ":/Image/bird1.png";
    ROLEImg[1] = ":/Image/bird2.png";
    ROLEImg[2] = ":/Image/bird3.png";
    ROLETimer = new QTimer(this);
    connect(ROLETimer,SIGNAL(timeout()),this,SLOT(update()));
    //ROLETimer->start(1000);
}

ROLE::~ROLE()
{

}

void ROLE::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //int state ;
    /*pix.load(src);
    painter.drawPixmap(0,0,35,35,pix);*/

    if(i == 1)
    {
        pix.load(ROLEImg[0]);
        painter.drawPixmap(0,0,35,35,pix);
        i++;
    }
    else if(i == 2)
    {
        pix.load(ROLEImg[1]);
        painter.drawPixmap(0,0,35,35,pix);
        i++;
    }
    else
    {
        pix.load(ROLEImg[2]);
        painter.drawPixmap(0,0,35,35,pix);
        i = 1;
    }
    /*score = (score+1*10)/1000;
    sprintf(num, "%d", score);
    QFont font = painter.font() ;
    font.setPointSize(70);
    painter.setFont(font);
    painter.drawText(10,10,20,20,Qt::AlignLeft, num);*/
}

