#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>

class gameover : public QWidget
{
    Q_OBJECT
public:
    explicit gameover(QWidget *parent = 0);
    ~gameover();
    int score;
protected:
    void paintEvent(QPaintEvent *);
private:
    int win_width;
    int win_height;
    char num[50];
};

#endif // GAMEOVER_H
