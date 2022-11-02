#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include "chooseplayerscene.h"
#include <QTimer>
#include <QDebug>
#include "qizi.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);




    QPushButton * qizi = new QPushButton;

    qizi->move(this->width(), this->height());
    qizi->setParent(this);

    this->setFixedSize(800, 600);
    this->setWindowIcon(QIcon(":/Images/windowIcon.jpg"));
    this->setWindowTitle("跳棋");

    connect(ui->actionexit, &QAction::triggered, [=] () {
        this->close();
    });

    MyPushButton * startBtn = new MyPushButton(":/Images/realfinalstart.png");
    startBtn->setParent(this);
    startBtn->move(this->width() / 2 - startBtn->width() / 2, 0.3 * this->height());

    MyPushButton * exitBtn = new MyPushButton(":/Images/exit.png");
    exitBtn->resize(217, 89);
    exitBtn->setIconSize(QSize(217, 89));
    exitBtn->setParent(this);
    exitBtn->move(this->width() / 2 - startBtn->width() / 2, 0.6 * this->height());

    connect(exitBtn, &QPushButton::clicked, [=] () {
        this->close();
    });


    chooseScene = new ChoosePlayerScene;
    connect(startBtn, &QPushButton::clicked, [=] () {
        startBtn->zoom1();
        startBtn->zoom2();
        qDebug() << startBtn->width();
        qDebug() << startBtn->height();
        QTimer::singleShot(200, this, [=](){
            this->hide();
            chooseScene->show();
        });
    });
    connect(chooseScene, &ChoosePlayerScene::chooseBack, [=] () {

        QTimer::singleShot(200, this, [=](){
            chooseScene->hide();
            this->show();
        });
    });

}

MainScene::~MainScene()
{
    delete ui;
}


void MainScene::paintEvent(QPaintEvent * ev)
{
//    QPainter painter(this);
//    QPixmap pix;
//    pix.load(":/Images/background.png");
//    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
