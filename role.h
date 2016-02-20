#ifndef ROLE_H
#define ROLE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class ROLE : public QWidget
{
    Q_OBJECT
public:
    explicit ROLE(QWidget *parent = 0);
    ~ROLE();
public:
    void paintEvent(QPaintEvent *);

private:
    QString src;
    QString ROLEImg[3];
    int i;
    QTimer *ROLETimer;
    char num[50];
    int score;
};

#endif // ROLE_H
