#ifndef HOME_H
#define HOME_H

#include <QWidget>

class home : public QWidget
{
    Q_OBJECT
public:
    explicit home(QWidget *parent = 0);
    ~home();
protected:
    void paintEvent(QPaintEvent *);
private:
    int win_width;
    int win_height;
};

#endif // HOME_H
