#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>

class Floor : public QWidget
{
    Q_OBJECT
public:
    explicit Floor(QWidget *parent = 0);
    ~Floor();
protected:
    void paintEvent(QPaintEvent *);
private:
    int win_width;
    int win_height;
};

#endif // FLOOR_H
