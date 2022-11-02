#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "qizi.h"
#include <QLabel>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int number);

    void paintEvent(QPaintEvent * ev);

    const double dx = 30, dy = 15 * sqrt(3);
    int playerNumber;

    QMap<int, Qizi*> data;
    Qizi * qizi[1700];

    int st, to, flag;
    int rgTimes;

    bool check();

    void Swap(int s, int t);

    void timerEvent(QTimerEvent *);

    QLabel timer, tit;

signals:
    void back();
    void move(int s, int t);

};

#endif // PLAYSCENE_H
