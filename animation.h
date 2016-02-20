#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class animation : public QWidget
{
    Q_OBJECT
public:
    explicit animation(QWidget *parent = 0);
    ~animation();
protected:
    void paintEvent(QPaintEvent *);
private:
    int i;
    int j;
    QString animationImg[3];
};

#endif // ANIMATION_H
