#include "playscene.h"
#include <QMenuBar>
#include <QDebug>
#include "mypushbutton.h"
#include <QLabel>
#include "qizi.h"
#include <QBrush>
#include <QLabel>
#include <QDialog>
#include <QMessageBox>


static int num = 0;
static int current = 0;

void PlayScene::Swap(int s, int t)
{
    QString tmp;
    tmp = qizi[s]->colorId;
    qizi[s]->colorId = qizi[t]->colorId;
    qizi[t]->colorId = tmp;
    QPixmap pix;
    pix.load(qizi[s]->colorId);
    qizi[s]->setIcon(pix);
    pix.load(qizi[t]->colorId);
    qizi[t]->setIcon(pix);
    num = 0;

    int tp = qizi[s]->turn;
    qizi[s]->turn = qizi[t]->turn;
    qizi[t]->turn = tp;

}

void PlayScene::timerEvent(QTimerEvent *)
{
    timer.setText(QString::number(60 - num++));
    if (num == 60)
    {
        QMessageBox::information(this, "超时了！", "有请下一位");
        num = 0;
        current = (current + 1) % playerNumber;
    }

}

bool PlayScene::check()
{
    bool mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[10 * 100 + i]->colorId != ":/Images/circlePink.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "粉色胜利！");
        return 1;
    }
    mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[11 * 100 + i]->colorId != ":/Images/circleGreen.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "绿色胜利！");
        return 1;
    }

    mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[12 * 100 + i]->colorId != ":/Images/circlered.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "红色胜利！");
        return 1;
    }

    mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[13 * 100 + i]->colorId != ":/Images/circleYellow.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "黄色胜利！");
        return 1;
    }

    mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[14 * 100 + i]->colorId != ":/Images/circlePurple.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "紫色胜利！");
        return 1;
    }

    mark = 1;
    for (int i = 0; i < 10; i++)
    {
        if (qizi[15 * 100 + i]->colorId != ":/Images/circleCyan.jpg")
        {
            mark = 0;
            break;
        }
    }
    if (mark)
    {
        QMessageBox::information(this, "游戏结束", "青色胜利！");
        return 1;
    }
}

PlayScene::PlayScene(int number)
{
    startTimer(1000);
    tit.setParent(this);
    tit.move(600, 50);
    tit.setText("剩余时间： ");
    timer.setParent(this);
    timer.move(700, 50);

    rgTimes = 0;

    void(PlayScene:: *doit)(int, int) = &PlayScene::Swap;
    connect(this, &PlayScene::move, this, doit);



    this->setFixedSize(800, 600);
    this->setWindowIcon(QPixmap(":/Images/windowIcon.jpg"));
    this->setWindowTitle("跳棋");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("菜单");

    QAction * returnAction = startMenu->addAction("返回");
    QAction * exitAction = startMenu->addAction("退出");


    connect(exitAction, &QAction::triggered, [=] () {
        this->close();
    });

    connect(returnAction, &QAction::triggered, [=] () {
        emit this->back();

    });

    MyPushButton * backBtn = new MyPushButton(":/Images/back.jpg");
    backBtn->resize(backBtn->width() * 4, backBtn->height() * 3);
    backBtn->setIconSize(QSize(backBtn->width(), backBtn->height()));
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height() - 10);
    connect(backBtn, &MyPushButton::clicked, [=] () {
        backBtn->zoom1();
        backBtn->zoom2();
        emit this->back();
    });

    playerNumber = number;

    double midX = this->width() / 2, midY = this->height() / 2;

    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        for (double x = midX - i * dx / 2; x <= midX + i * dx / 2; x += dx)
        {
            qizi[10 * 100 + cnt] = new Qizi;
            qizi[10 * 100 + cnt]->setParent(this);
            qizi[10 * 100 + cnt]->move(x - 7.5 + 2.25, midY - 8 * dy + i * dy - 7.5 + 1.5);
            qizi[10 * 100 + cnt]->id = ('A' << 16) + cnt;
            qizi[10 * 100 + cnt]->turn = 0;
            cnt++;

        }
    }

    cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 5 - i; j++)
        {
            qizi[15 * 100 + cnt] = new Qizi;
            qizi[15 * 100 + cnt]->setParent(this);
            qizi[15 * 100 + cnt]->move(midX - 6 * dx - 7.5 + 2.25 + (j - 1) * dx + (i - 1) * dx / 2, midY - (5 - i) * dy - 7.5 + 1.5);
            qizi[15 * 100 + cnt]->id = ('F' << 16) + cnt;
            qizi[15 * 100 + cnt]->turn = 5;
            cnt++;
        }
    }

    cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 5 - i; j++)
        {
            qizi[12 * 100 + cnt] = new Qizi;
            qizi[12 * 100 + cnt]->setParent(this);
            qizi[12 * 100 + cnt]->move(midX + 3 * dx + (i - 1) * dx / 2 + (j - 1) * dx - 7.5 + 2.25, midY - (5 - i) * dy - 7.5 + 1.5);
            qizi[12 * 100 + cnt]->id = ('C' << 16) + cnt;
            qizi[12 * 100 + cnt]->turn = 2;
            cnt++;
        }
    }

    cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            qizi[13 * 100 + cnt] = new Qizi;
            qizi[13 * 100 + cnt]->setParent(this);
            qizi[13 * 100 + cnt]->move(midX - 4 * dx - i * dx / 2 + (j - 1) * dx - 7.5 + 2.25, midY + i * dy - 7.5 + 1.5);
            qizi[13 * 100 + cnt]->id = ('D' << 16) + cnt;
            qizi[13 * 100 + cnt]->turn = 3;
            cnt++;
        }
    }

    cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            qizi[14 * 100 + cnt] = new Qizi;
            qizi[14 * 100 + cnt]->setParent(this);
            qizi[14 * 100 + cnt]->move(midX + 5 * dx - i * dx / 2 + (j - 1) * dx - 7.5 + 2.25, midY + i * dy - 7.5 + 1.5);
            qizi[14 * 100 + cnt]->id = ('E' << 16) + cnt;
            qizi[14 * 100 + cnt]->turn = 4;
            cnt++;
        }
    }

    cnt = 0;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 5 - i; j++)
        {
            qizi[11 * 100 + cnt] = new Qizi;
            qizi[11 * 100 + cnt]->setParent(this);
            qizi[11 * 100 + cnt]->move(midX - 3 * dx + i * dx / 2 + j * dx - 7.5 + 2.25, midY + (4 + i) * dy - 7.5 + 1.5);
            qizi[11 * 100 + cnt]->id = ('B' << 16) + cnt;
            qizi[11 * 100 + cnt]->turn = 1;
            cnt++;
        }
    }

    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4 + i; j++)
        {
            qizi[i * 100 + j] = new Qizi;
            qizi[i * 100 + j] ->setParent(this);
            qizi[i * 100 + j] ->move(midX - 2 * dx - i * dx / 2 - 7.5 + 2.25 + j * dx, midY - (4 - i) * dy - 7.5 + 1.5);
            qizi[i * 100 + j] ->id = (i << 16) + j;
            qizi[i * 100 + j]->turn = 7;
        }
    }

    for (int i = 5; i <= 8; i++)
    {
        for (int j = 0; j < 13 - i; j++)
        {
            qizi[i * 100 + j]  = new Qizi;
            qizi[i * 100 + j] ->setParent(this);
            qizi[i * 100 + j] ->move(midX - 4 * dx + (i - 4) * dx / 2 - 7.5 + 2.25 + j * dx, midY + (i - 4) * dy - 7.5 + 1.5);
            qizi[i * 100 + j] ->id = (i << 16) + j;
            qizi[i * 100 + j]->turn = 7;
        }
    }



    for (int i = 10; i <= 15; i++)
        for (cnt = 0; cnt <10; cnt++)
        {
            connect(qizi[i * 100 + cnt], &QPushButton::clicked, [=] () {
                if (flag == 0)
                {
                    st = i * 100 + cnt;
                    if (current != qizi[st]->turn && qizi[st]->turn < 7)
                    {
                        QMessageBox::information(this, "别着急！", "还没轮到你");
                        num = 0;
                        return ;
                    }
                    if (qizi[st]->colorId != ":/Images/round.jpg")
                        flag = 1;
                }
                else if (flag == 1)
                {
                    to = i * 100 + cnt;
                    if (qizi[to]->colorId != ":/Images/round.jpg")
                    {
                        QMessageBox::information(this, "请重新走棋", "这里不能走！");
                        flag = 0;
                        return ;
                    }
                    flag = 2;
                }
                if (flag == 2)
                {
                    emit this->move(st, to);
                    flag = 0;
                    rgTimes = 0;
                    check();
                    current = (current + 1) % playerNumber;
                }
            });
        }
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4 + i; j++)
        {
            connect(qizi[i * 100 + j], &QPushButton::clicked, [=] () {
                if (flag == 0)
                {
                    st = i * 100 + j;
                    if (current != qizi[st]->turn && qizi[st]->turn < 7)
                    {
                        QMessageBox::information(this, "别着急！", "还没轮到你");
                        num = 0;
                        return ;
                    }
                    if (qizi[st]->colorId != ":/Images/round.jpg")
                        flag = 1;
                }
                else if (flag == 1)
                {
                    to = i * 100 + j;
                    if (qizi[to]->colorId != ":/Images/round.jpg")
                    {
                        QMessageBox::information(this, "请重新走棋", "这里不能走！");
                        flag = 0;
                        return ;
                    }
                    flag = 2;
                }
                if (flag == 2)
                {
                    emit this->move(st, to);
                    flag = 0;
                    rgTimes = 0;
                    check();
                    current = (current + 1) % playerNumber;
                }
            });
        }
    }
    for (int i = 5; i <= 8; i++)
    {
        for (int j = 0; j < 13 - i; j++)
        {
            connect(qizi[i * 100 + j], &QPushButton::clicked, [=] () {
                if (flag == 0)
                {
                    st = i * 100 + j;
                    if (current != qizi[st]->turn && qizi[st]->turn < 7)
                    {
                        QMessageBox::information(this, "别着急！", "还没轮到你");
                        num = 0;
                        return ;
                    }
                    if (qizi[st]->colorId != ":/Images/round.jpg")
                        flag = 1;
                }
                else if (flag == 1)
                {
                    to = i * 100 + j;
                    if (qizi[to]->colorId != ":/Images/round.jpg")
                    {
                        QMessageBox::information(this, "请重新走棋", "这里不能走！");
                        flag = 0;
                        return ;
                    }
                    flag = 2;
                }
                if (flag == 2)
                {
                    emit this->move(st, to);
                    flag = 0;
                    rgTimes = 0;
                    check();
                    current = (current + 1) % playerNumber;
                }
            });
        }
    }


    QPushButton * clearBtn = new QPushButton;
    clearBtn->setParent(this);
    clearBtn->resize(100, 50);
    clearBtn->move(0, 50);
    clearBtn->setText("清除走棋信息");
    clearBtn->setStyleSheet("background-color: rgb(109, 126, 233); color: rgb(255, 174, 201)");

    connect(clearBtn, &QPushButton::clicked, [=] () {
        flag = 0;
    });

    QPushButton * rgBtn = new QPushButton;
    rgBtn->setParent(this);
    rgBtn->resize(100, 50);
    rgBtn->move(0, 150);
    rgBtn->setText("悔棋");
    rgBtn->setStyleSheet("background-color: rgb(109, 126, 233); color: rgb(255, 174, 201)");

    connect(rgBtn, &QPushButton::clicked, [=] () {
        if (flag > 0)
        {
            QMessageBox::information(this, "太晚了！！！", "人家已经在走棋了哦");
            flag = 0;
            return;
        }
        if (rgTimes > 0)
        {
            QMessageBox::information(this, "差不多得了", "只能悔一步哦！");
            return;
        }
        QString tmp;
        tmp = qizi[st]->colorId;
        qizi[st]->colorId = qizi[to]->colorId;
        qizi[to]->colorId = tmp;
        QPixmap pix;
        pix.load(qizi[st]->colorId);
        qizi[st]->setIcon(pix);
        pix.load(qizi[to]->colorId);
        qizi[to]->setIcon(pix);
        flag = 0;
        rgTimes = 1;
    });

    QPushButton * resetBtn = new QPushButton;
    resetBtn->setParent(this);
    resetBtn->resize(100, 50);
    resetBtn->move(0, 250);
    resetBtn->setText("重置棋盘");
    resetBtn->setStyleSheet("background-color: rgb(109, 126, 233); color: rgb(255, 174, 201)");

    connect(resetBtn, &QPushButton::clicked, [&] () {
        QPixmap pix;
        current = 0;
        if (playerNumber >= 2)
        {
            pix.load(":/Images/circleGreen.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[10 * 100 + i]->setIcon(pix);
                qizi[10 * 100 + i]->colorId = ":/Images/circleGreen.jpg";
                qizi[10 * 100 + i]->turn = 0;
            }

            pix.load(":/Images/circlePink.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[11 * 100 + i]->setIcon(pix);
                qizi[11 * 100 + i]->colorId = ":/Images/circlePink.jpg";
                qizi[11 * 100 + i]->turn = 1;
            }
        }
        if (playerNumber >= 3)
        {
            pix.load(":/Images/circleYellow.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[12 * 100 + i]->setIcon(pix);
                qizi[12 * 100 + i]->colorId = ":/Images/circleYellow.jpg";
                qizi[12 * 100 + i]->turn = 2;
            }
        }
        if (playerNumber >= 4)
        {
            pix.load(":/Images/circlered.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[13 * 100 + i]->setIcon(pix);
                qizi[13 * 100 + i]->colorId = ":/Images/circlered.jpg";
                qizi[13 * 100 + i]->turn = 3;
            }
        }
        if (playerNumber >= 5)
        {
            pix.load(":/Images/circleCyan.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[14 * 100 + i]->setIcon(pix);
                qizi[14 * 100 + i]->colorId = ":/Images/circleCyan.jpg";
                qizi[14 * 100 + i]->turn = 4;
            }
        }
        if (playerNumber == 6)
        {
            pix.load(":/Images/circlePurple.jpg");
            for (int i = 0; i < 10; i++)
            {
                qizi[15 * 100 + i]->setIcon(pix);
                qizi[15 * 100 + i]->colorId = ":/Images/circlePurple.jpg";
                qizi[15 * 100 + i]->turn = 5;
            }
        }

        for (int i = 0; i <= 4; i++)
        {
            for (int j = 0; j <= 4 + i; j++)
            {
                QPixmap pix;
                pix.load(":/Images/round.jpg");
                qizi[i * 100 + j]->setIcon(pix);
                qizi[i * 100 + j]->colorId = ":/Images/round.jpg";
                qizi[i * 100 + j]->turn = 7;
            }
        }

        for (int i = 5; i <= 8; i++)
        {
            for (int j = 0; j < 13 - i; j++)
            {
                QPixmap pix;
                pix.load(":/Images/round.jpg");
                qizi[i * 100 + j]->setIcon(pix);
                qizi[i * 100 + j]->colorId = ":/Images/round.jpg";
                qizi[i * 100 + j]->turn = 7;
            }
        }
    });


    QPixmap pix;
    if (playerNumber >= 2)
    {
        pix.load(":/Images/circleGreen.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[10 * 100 + i]->setIcon(pix);
            qizi[10 * 100 + i]->colorId = ":/Images/circleGreen.jpg";
        }

        pix.load(":/Images/circlePink.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[11 * 100 + i]->setIcon(pix);
            qizi[11 * 100 + i]->colorId = ":/Images/circlePink.jpg";
        }
    }
    if (playerNumber >= 3)
    {
        pix.load(":/Images/circleYellow.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[12 * 100 + i]->setIcon(pix);
            qizi[12 * 100 + i]->colorId = ":/Images/circleYellow.jpg";
        }
    }
    if (playerNumber >= 4)
    {
        pix.load(":/Images/circlered.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[13 * 100 + i]->setIcon(pix);
            qizi[13 * 100 + i]->colorId = ":/Images/circlered.jpg";
        }
    }
    if (playerNumber >= 5)
    {
        pix.load(":/Images/circleCyan.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[14 * 100 + i]->setIcon(pix);
            qizi[14 * 100 + i]->colorId = ":/Images/circleCyan.jpg";
        }
    }
    if (playerNumber == 6)
    {
        pix.load(":/Images/circlePurple.jpg");
        for (int i = 0; i < 10; i++)
        {
            qizi[15 * 100 + i]->setIcon(pix);
            qizi[15 * 100 + i]->colorId = ":/Images/circlePurple.jpg";
        }
    }
}

void PlayScene::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Images/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    QPen pen(QColor(0, 0, 0));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);


    //画圆
    QBrush brush(Qt::white);
    painter.setBrush(brush);
    double midX = this->width() / 2, midY = this->height() / 2;


    qreal startPointX1 = midX;
    qreal startPointY1 = midY + 8 * dy;

    qreal endPointX1   = midX - 2 * dx;
    qreal endPointY1   = midY + 4 * dy;

    qreal endPointX2   = midX + 2 * dx;
    qreal endPointY2   = midY + 4 * dy;

    QPainterPath path;
    path.moveTo (startPointX1, startPointY1);
    path.lineTo (endPointX1, endPointY1);
    path.lineTo (endPointX2,   endPointY2);
    path.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path, QBrush (QColor ("chartreuse")));

    QPainterPath path2;

    startPointX1 = midX + 4 * dx;
    startPointY1 = midY;

    endPointX1   = midX + 2 * dx;
    endPointY1   = midY - 4 * dy;

    endPointX2   = midX + 6 * dx;
    endPointY2   = midY - 4 * dy;

    path2.moveTo (startPointX1, startPointY1);
    path2.lineTo (endPointX1, endPointY1);
    path2.lineTo (endPointX2,   endPointY2);
    path2.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path2, QBrush (QColor ("red")));

    QPainterPath path3;

    startPointX1 = midX - 4 * dx;
    startPointY1 = midY;

    endPointX1   = midX - 2 * dx;
    endPointY1   = midY + 4 * dy;

    endPointX2   = midX - 6 * dx;
    endPointY2   = midY + 4 * dy;

    path3.moveTo (startPointX1, startPointY1);
    path3.lineTo (endPointX1, endPointY1);
    path3.lineTo (endPointX2,   endPointY2);
    path3.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path3, QBrush (QColor ("yellow")));

    QPainterPath path4;

    startPointX1 = midX - 4 * dx;
    startPointY1 = midY;

    endPointX1   = midX - 2 * dx;
    endPointY1   = midY - 4 * dy;

    endPointX2   = midX - 6 * dx;
    endPointY2   = midY - 4 * dy;

    path4.moveTo (startPointX1, startPointY1);
    path4.lineTo (endPointX1, endPointY1);
    path4.lineTo (endPointX2,   endPointY2);
    path4.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path4, QBrush (QColor ("cyan")));

    QPainterPath path5;

    startPointX1 = midX + 4 * dx;
    startPointY1 = midY;

    endPointX1   = midX + 2 * dx;
    endPointY1   = midY + 4 * dy;

    endPointX2   = midX + 6 * dx;
    endPointY2   = midY + 4 * dy;

    path5.moveTo (startPointX1, startPointY1);
    path5.lineTo (endPointX1, endPointY1);
    path5.lineTo (endPointX2,   endPointY2);
    path5.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path5, QBrush (QColor ("blueviolet")));

    QPainterPath path6;

    startPointX1 = midX;
    startPointY1 = midY - 8 *dy;

    endPointX1   = midX - 2 * dx;
    endPointY1   = midY - 4 * dy;

    endPointX2   = midX + 2 * dx;
    endPointY2   = midY - 4 * dy;

    path6.moveTo (startPointX1, startPointY1);
    path6.lineTo (endPointX1, endPointY1);
    path6.lineTo (endPointX2,   endPointY2);
    path6.lineTo (startPointX1, startPointY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (path6, QBrush (QColor ("pink")));


    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.drawEllipse(QPointF(this->width() / 2, this->height() / 2 - 8 * dy), 7.5, 7.5);
    for (int i = 1; i <= 3; i++)
    {
        for (double x = midX - i * dx / 2; x <= midX + i * dx / 2; x += dx)
        {
            painter.drawEllipse(QPointF(x, midY - 8 * dy + i * dy), 7.5, 7.5);
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        for (double x = midX- 6 * dx + (i - 1) * dx / 2; x <= midX + 6 * dx - (i - 1) * dx / 2; x += dx)
            painter.drawEllipse(QPointF(x, midY - 8 * dy + (i + 3) * dy), 7.5, 7.5);
    }
    for (int i = 1; i <= 4; i++)
    {
        for (double x = midX - 6 * dx + (4 - i) * dx / 2; x <= midX + 6 * dx - (4 - i) * dx / 2; x += dx)
            painter.drawEllipse(QPointF(x, midY + i * dy), 7.5, 7.5);
    }
    for (int i = 1; i <= 4; i++)
    {
        for (double x = midX - 3 * dx / 2 + (i - 1) * dx / 2; x <= midX + 3 * dx / 2 - (i - 1) * dx / 2; x += dx)
            painter.drawEllipse(QPointF(x, midY + (4 + i) * dy), 7.5, 7.5);
    }

    //画线
    for(int i = 1; i <= 3; i++)
    {
        double l = midX - i * dx / 2;
        for (int j = 1; j <= i; j++)
        {
            painter.drawLine(QPoint(l + 7.5, midY - (8 - i) * dy), QPoint(l + dx - 7.5, midY - (8 - i) * dy));
            l += dx;
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        double l = midX - (13 - i) * dx / 2;
        for (int j = 1; j <= 13 - i; j++)
        {
            painter.drawLine(QPoint(l + 7.5, midY - (5 - i) * dy), QPoint(l + dx - 7.5, midY - (5 - i) * dy));
            l += dx;
        }
    }
    for (int i = 1; i <= 4; i++)
    {
        double l = midX - (8 + i) * dx / 2;
        for (int j = 1; j <= 8 + i; j++)
        {
            painter.drawLine(QPoint(l + 7.5, midY + i * dy), QPoint(l + dx - 7.5, midY + i * dy));
            l += dx;
        }
    }
    for (int i = 1; i <= 3; i++)
    {
        double l = midX - (4 - i) * dx / 2;
        for (int j = 1; j <= 4 - i; j++)
        {
            painter.drawLine(QPoint(l + 7.5, midY + (4 + i) * dy), QPoint(l + dx - 7.5, midY + (4 + i) * dy));
            l += dx;
        }
    }


    for (int i = 1; i <= 3; i++)
    {
        double x0 = midX - (12 - i) * dx / 2, y0 = midY - (4 - i) * dy;
        for (int j = 1; j <= i; j++)
        {
            painter.drawLine(QPoint(x0 + 7.5 / 2, y0 - 7.5 / 2 * sqrt(3)), QPoint(x0 + dx / 2 - 7.5 / 2, y0 - dy + 7.5 / 2 * sqrt(3)));
            x0 += dx / 2;
            y0 -= dy;
        }
    }

    for (int i = 1; i <= 5; i++)
    {
        double x0 = midX - (7 - i) * dx, y0 = midY + 4 * dy;
        for (int j = 1; j <= 13 - i; j++)
        {
            painter.drawLine(QPoint(x0 + 7.5 / 2, y0 - 7.5 / 2 * sqrt(3)), QPoint(x0 + dx / 2 - 7.5 / 2, y0 - dy + 7.5 / 2 * sqrt(3)));
            x0 += dx / 2;
            y0 -= dy;
        }
    }

    for (int i = 1; i <= 4; i++)
    {
        double x0 = midX + (2 + i) * dx, y0 = midY - 4 * dy;
        for (int j = 1; j <= 8 + i; j++)
        {
            painter.drawLine(QPoint(x0 - 7.5 / 2, y0 + 7.5 / 2 * sqrt(3)), QPoint(x0 - dx / 2 + 7.5 / 2, y0 + dy - 7.5 / 2 * sqrt(3)));
            x0 -= dx / 2;
            y0 += dy;
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        double x0 = midX + (2 + i) * dx, y0 = midY + 4 * dy;
        for (int j = 1; j <= 4 - i; j++)
        {
            painter.drawLine(QPoint(x0 + 7.5 / 2, y0 - 7.5 / 2 * sqrt(3)), QPoint(x0 + dx / 2 - 7.5 / 2, y0 - dy + 7.5 / 2 * sqrt(3)));
            x0 += dx / 2;
            y0 -= dy;
        }
    }



    for (int i = 1; i <= 3; i++)
    {
        double x0 = midX - (6 - i) * dx, y0 = midY + 4 * dy;
        for (int j = 1; j <= i; j++)
        {
            painter.drawLine(QPoint(x0 - 7.5 / 2, y0 - 7.5 / 2 * sqrt(3)), QPoint(x0 - dx / 2 + 7.5 / 2, y0 - dy + 7.5 / 2 * sqrt(3)));
            x0 -= dx / 2;
            y0 -= dy;
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        double x0 = midX - (7 - i) * dx, y0 = midY - 4 * dy;
        for (int j = 1; j <= 13 - i; j++)
        {
            painter.drawLine(QPoint(x0 + 7.5 / 2, y0 + 7.5 / 2 * sqrt(3)), QPoint(x0 + dx / 2 - 7.5 / 2, y0 + dy - 7.5 / 2 * sqrt(3)));
            x0 += dx / 2;
            y0 += dy;
        }
    }

    for (int i = 1; i <= 4; i++)
    {
        double x0 = midX + (2 + i) * dx, y0 = midY + 4 * dy;
        for (int j = 1; j <= 8 + i; j++)
        {
            painter.drawLine(QPoint(x0 - 7.5 / 2, y0 - 7.5 / 2 * sqrt(3)), QPoint(x0 - dx / 2 + 7.5 / 2, y0 - dy + 7.5 / 2 * sqrt(3)));
            x0 -= dx / 2;
            y0 -= dy;
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        double x0 = midX + (2 + i) * dx, y0 = midY - 4 * dy;
        for (int j = 1; j <= 4 - i; j++)
        {
            painter.drawLine(QPoint(x0 + 7.5 / 2, y0 + 7.5 / 2 * sqrt(3)), QPoint(x0 + dx / 2 - 7.5 / 2, y0 + dy - 7.5 / 2 * sqrt(3)));
            x0 += dx / 2;
            y0 += dy;
        }
    }
}
