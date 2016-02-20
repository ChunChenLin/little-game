#include "home.h"
#include <QPixmap>
#include <QPainter>

home::home(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(380,450);
}

home::~home() {}

void home::paintEvent(QPaintEvent *)
{
    QPixmap homeImg;
    QPainter painter(this);
    homeImg.load(":/Image/home.png");
    painter.drawPixmap(0,0,380,450,homeImg);
}

