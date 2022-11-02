#include "chooseplayerscene.h"
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>

ChoosePlayerScene::ChoosePlayerScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);
    this->setWindowIcon(QPixmap(":/Images/windowIcon.jpg"));
    this->setWindowTitle("选择玩家人数");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("菜单");

    QAction * returnAction = startMenu->addAction("返回");
    QAction * exitAction = startMenu->addAction("退出");

    connect(returnAction, &QAction::triggered, [=] () {
        emit this->chooseBack();
    });
    connect(exitAction, &QAction::triggered, [=] () {
        this->close();
    });

    MyPushButton * backBtn = new MyPushButton(":/Images/back.jpg");
    backBtn->resize(backBtn->width() * 4, backBtn->height() * 3);
    backBtn->setIconSize(QSize(backBtn->width(), backBtn->height()));
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height() - 10);
    connect(backBtn, &MyPushButton::clicked, [=] () {
        backBtn->zoom1();
        backBtn->zoom2();
        emit this->chooseBack();
    });

    MyPushButton * btn_2 = new MyPushButton(":/Images/button2.jpg");
    MyPushButton * btn_3 = new MyPushButton(":/Images/button3.jpg");
    MyPushButton * btn_4 = new MyPushButton(":/Images/4.jpg");
    MyPushButton * btn_5 = new MyPushButton(":/Images/5.jpg");
    MyPushButton * btn_6 = new MyPushButton(":/Images/6.jpg");
    btn_2->resize(btn_2->width() * 2, btn_2->height() * 2);
    btn_2->setIconSize(QSize(btn_2->width(), btn_2->height()));
    btn_2->setParent(this);
    btn_2->move(this->width() / 2 - 225 - btn_2->width() / 2, this->height() / 2 - btn_2->height() / 2 - 100);

    btn_3->resize(btn_3->width() * 2, btn_3->height() * 2);
    btn_3->setIconSize(QSize(btn_3->width(), btn_3->height()));
    btn_3->setParent(this);
    btn_3->move(this->width() / 2 - 125 + btn_3->width() / 2, this->height() / 2 - btn_2->height() / 2 - 100);

    btn_4->resize(btn_4->width() * 2, btn_4->height() * 2);
    btn_4->setIconSize(QSize(btn_4->width(), btn_4->height()));
    btn_4->setParent(this);
    btn_4->move(this->width() / 2 + 225 - btn_4->width() / 2, this->height() / 2 - btn_4->height() / 2 - 100);

    btn_5->resize(btn_5->width() * 2, btn_5->height() * 2);
    btn_5->setIconSize(QSize(btn_5->width(), btn_5->height()));
    btn_5->setParent(this);
    btn_5->move(this->width() / 2 - 125 - btn_5->width() / 2, this->height() / 2 - btn_5->height() / 2 + 100);

    btn_6->resize(btn_6->width() * 2, btn_6->height() * 2);
    btn_6->setIconSize(QSize(btn_6->width(), btn_6->height()));
    btn_6->setParent(this);
    btn_6->move(this->width() / 2 + 125 - btn_6->width() / 2, this->height() / 2 - btn_6->height() / 2 + 100);


    connect(btn_2, &MyPushButton::clicked, [=] () {
        play = new PlayScene(2);
        this->hide();
        play->show();
        connect(play, &PlayScene::back, [=] () {
            QTimer::singleShot(200, this, [=](){
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });

    });

    connect(btn_3, &MyPushButton::clicked, [=] () {
        play = new PlayScene(3);
        this->hide();
        play->show();
        connect(play, &PlayScene::back, [=] () {
            QTimer::singleShot(200, this, [=](){
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });
    });

    connect(btn_4, &MyPushButton::clicked, [=] () {
        play = new PlayScene(4);
        this->hide();
        play->show();
        connect(play, &PlayScene::back, [=] () {
            QTimer::singleShot(200, this, [=](){
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });
    });

    connect(btn_5, &MyPushButton::clicked, [=] () {
        play = new PlayScene(5);
        this->hide();
        play->show();
        connect(play, &PlayScene::back, [=] () {
            QTimer::singleShot(200, this, [=](){
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });
    });

    connect(btn_6, &MyPushButton::clicked, [=] () {
        play = new PlayScene(6);
        this->hide();
        play->show();
        connect(play, &PlayScene::back, [=] () {
            QTimer::singleShot(200, this, [=](){
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });
    });


}

void ChoosePlayerScene::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Images/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
