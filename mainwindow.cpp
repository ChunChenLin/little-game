#include "mainwindow.h"
#include "gameover.h"
#include "home.h"
#include <ctime>
#include <QPainter>
#include <QPixmap>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    score = 0;
    win_width = 380;
    win_height = 450;
    this->setFixedSize(win_width,win_height);	//視窗大小
    this->setWindowIcon(QIcon(":/Image/bird1.png"));
    this->setWindowTitle("Qt FlappyBird");
    char * m1 = "musicFile/bird.wav";
    char * m2 = "musicFile/chic.wav";
    bgm = new easyMusic(m1, 80, 0);
    fgm = new easyMusic(m2, 80, 0);
    go = new easyMusic("musicFile/gameover.wav", 80, 0);
    st = new easyMusic("musicFile/start.wav", 80, 1);

    //創建首頁
    Home = new home(this);
    Home->move(0,0);

    //創建水管
    for(int i=0;i<pipeCount;i++)
        pipe[i]=new OBSTACLE(this);

    //創建鳥
    birds=new ROLE(this);

    GameOver = new gameover(this);

    GameOver->move(400,0);

    //創建地板
    ground[0] = new Floor(this);
    ground[1] = new Floor(this);
    ground[0]->move(0,390);
    ground[1]->move(380,390);
    ground[0]->hide();
    ground[1]->hide();

    //遊戲初始模式
    gameRedy();
    //birdTimer=new QTimer(this);
    connect(birdTimer,SIGNAL(timeout()),this,SLOT(birdAction()));

    //遊戲開始
    //gameStart();

}
void MainWindow::paintEvent(QPaintEvent *)		//繪圖事件, 用来產生背景
{
    // 可以在這裡新增背景圖片
    QPainter painter(this);
    QPixmap bgImg;

    bgImg.load(":/Image/bg.png");
    painter.drawPixmap(0,0,win_width,win_height,bgImg);
    QFont font = painter.font() ;
    font.setPointSize(40);
    painter.setFont(font);
    int num_d = (int)score;
    sprintf(num, "%d", num_d);
    painter.drawText(0,0,100,75,Qt::AlignLeft,num);

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 在這裡設定按下滑鼠要觸發的功能
    if(event->button()==Qt::LeftButton) {
        birdup();
        fgm -> play();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 在這裡設定按下鍵盤要觸發的功能
    if(event->key()==Qt::Key_Space) {
        gameLose();
        gameRedy();
        gameStart();
    }
    else if(event->key()==Qt::Key_Return) {
        gameStart();
    } else if(event->key()==Qt::Key_A) {
        if(pipeTValue>2&&groundTValue>2) {
            pipeTValue--;
            groundTValue--;
            pipeTimer->start(pipeTValue);
            groundTimer->start(groundTValue);
        }
    } else if(event->key()==Qt::Key_S) {
            pipeTValue++;
            groundTValue++;
            pipeTimer->start(pipeTValue);
            groundTimer->start(groundTValue);
    } else if(event->key()==Qt::Key_R) {
            pipeTValue = 8;
            groundTValue = 8;
            pipeTimer->start(pipeTValue);
            groundTimer->start(groundTValue);
    }
}
void MainWindow::createPipe()		//初始化水管，依序排在視窗外
{

    int startx=win_width+10;		//第一个水管的位置
    pipeXgap=200;		//水管水平間距
    int pipR;			//水管垂直位置隨機數
    qsrand(time(NULL));		//qrand是qt的隨機函數 用法和c的rand一樣

    for(int i=0;i<pipeCount;i++)
    {
        pipR=qrand()%200;

        pipe[i]->move(startx+i*pipeXgap,-200+pipR);
        lastPipe=i;		//很重要 記錄最後一個水管號碼 為後面的循環水管建立基礎
    }

    pipeTimer =new QTimer(this);	//pipeTimer 處理兩個動作
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(pipeAction()));
    connect(pipeTimer,SIGNAL(timeout()),this,SLOT(collisDete()));
    pipeTValue=8;

}
void MainWindow::createBird(){
    if(gamemod==redy) {
        birds->move(0,80);
    } else {
        birds->move(60,250);
    }
    birdTimer=new QTimer(this);
    //鳥的上下速度
    this->birdV_array[0]=-2;
    this->birdV_array[1]=-3;
    this->birdV_array[2]=-2;
    this->birdV_array[3]=-1;
    this->birdV_array[4]=0;
    this->birdV_array[5]=0;
    this->birdV_array[6]=0;
    this->birdV_array[7]=0;
    this->birdV_array[8]=1;
    this->birdV_array[9]=1;
    this->birdV_array[10]=2;
    this->birdV_array[11]=2;
    this->birdV_array[12]=2;
    this->birdV_array[13]=3;
    this->birdV_array[14]=3;

    this->index_birdV=0;

    birdV=0;

    timedata=8;
}
void MainWindow::birdup(){
    index_birdV=0.0;
    birdV=birdV_array[int(index_birdV)];
}
void MainWindow::birdAction()
{
    if(gamemod==redy) {
        birds->move(birds->pos().x()+1,birds->pos().y());
        if(birds->pos().x()>380) {
            birds->move(0,birds->pos().y());
        }
        return;
    }
    //鳥的運動
    // 每次觸發這個function都會更改鳥的位置，x軸不變, y軸加上 birdV成為新的位置
    // XX->pos().x() and XX->pos().y() 是QWidget物件的函式，可以用來取得xy座標位置
    birds->move(birds->pos().x(),birds->pos().y()+birdV);


    if(index_birdV<14.0)
        index_birdV+=0.2;
    else
        index_birdV=14.0;

    birdV=birdV_array[int(index_birdV)];

    // 這邊做一個地板碰撞偵測
    if(birds->pos().y()+birds->height()>=win_height+10-30)
    {
        birds->move(birds->pos().x(),win_height-birds->height()+10); // XX->height可用來取得物件高度
        birdTimer->stop();
        gameLose();
    }
}
void MainWindow::pipeAction()
{
    //水管動畫，水管離開地圖後，重新回到右側接替lastPipe位置
    int pipR; // 一個隨機變數，讓每次水管的位置都不太一樣
    // 每次觸發這個函式，水管都會向左移動，如果最左邊的水管離開地圖範圍則移動到最右邊
    for(int i=0;i<pipeCount;i++)
    {
        pipe[i]->move(pipe[i]->pos().x()-1,pipe[i]->pos().y());
        if(pipe[i]->pos().x()<-100)
        {
            pipR=qrand()%200;
            pipe[i]->move(pipe[lastPipe]->pos().x()+pipeXgap,-200+pipR);
            lastPipe=i;
        }
    }
}
void MainWindow::createGround()
{
    groundTimer =new QTimer(this);
    connect(groundTimer,SIGNAL(timeout()),this,SLOT(groundAction()));
    groundTValue=8;
}

void MainWindow::groundAction()
{
    for(int i=0;i<2;i++) {
        ground[i]->move(ground[i]->pos().x()-1,ground[i]->pos().y());
        if(ground[i]->pos().x()<=-380) {
            ground[i]->move(380,ground[i]->pos().y());
        }
    }
}

void MainWindow::aniAction()
{
    int step_length = 500;
    int i=0;

    if(i<=step_length) {
        ani->move(i,100);
        i+=10;
    }
}

void MainWindow::collisDete()
{
    //水管碰撞偵測
    int birdRx=birds->pos().x()+30;
    int birdDy=birds->pos().y()+30;
    for(int i=0;i<pipeCount;i++)
    {
        if(birdRx>=pipe[i]->pos().x()&&birds->pos().x()<=pipe[i]->pos().x()+pipe[i]->width()-10) // XX->width可用來取得物件寬度
        {
            if(birds->pos().y() <= (pipe[i]->pos().y()+pipe[i]->getH1()) || birdDy >= (pipe[i]->pos().y()+pipe[i]->getH1()+pipe[i]->getGap()))
            {  //碰到水管遊戲結束
                //GameOver = new gameover(this);
                //GameOver->move(0,0);
                //restart = 1;
                gameLose();
            }
        }
    }
    //update();
    score = (score+0.1);
    update();
}
void MainWindow::gameRedy()
{
    gamemod=redy;
    st -> play();
    GameOver->move(500,0);
    /*Home = new home(this);
    Home->move(0,0);*/

    ani = new animation(this);
    ani->move(0,100);
    aniTimer = new QTimer(this);
    connect(aniTimer,SIGNAL(timeout()),this,SLOT(aniAction()));
    aniTimer->start(100);

    createBird();
    birdTimer->start(timedata);
    createPipe();

}
void MainWindow::gameLose()
{
    gamemod=lose;
    ground[0]->hide();
    ground[1]->hide();
    groundTimer->stop();
    pipeTimer->stop();
    GameOver -> score = score;
    GameOver->move(0,0);
    bgm -> stop();
    go -> play();
}
void MainWindow::gameStart()
{
    score =0 ;
    createGround();
    Home->hide();
    ani->hide();
    st -> stop();
    go -> stop();
    ground[0]->show();
    ground[1]->show();
    bgm -> play();
    gamemod=start;
    createBird();
    birdTimer->start(timedata);
    pipeTimer->start(pipeTValue);
    groundTimer->start(groundTValue);
}
