#include "floor.h"

#include <QPixmap>
#include <QPainter>

Floor::Floor(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(380,60);
}

Floor::~Floor()
{

}

void Floor::paintEvent(QPaintEvent *)
{
    QPixmap floorImg;
    QPainter painter(this);
    floorImg.load(":/Image/floor.jpg");
    painter.drawPixmap(0,0,380,60,floorImg);
}

