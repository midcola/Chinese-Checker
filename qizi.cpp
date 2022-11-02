#include "qizi.h"
#include <QPixmap>
#include <QDebug>

Qizi::Qizi(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("background-color: rgb(255, 255, 255)");
    this->setStyleSheet("QPushButton{border:0px}");
    this->setFixedSize(11, 11);
    colorId = ":/Images/round.jpg";


    QPixmap pix;
    bool ret = pix.load(":/Images/round.jpg");
    if (!ret)
    {
        qDebug() << "加载失败";
    }

    this->resize(15, 15);
    //this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(15, 15));

//    connect(this, &QPushButton::clicked, [=] () {
//        if (Qizi::flag == 0)
//        {
//            Qizi::st = this->id;
//            Qizi::flag = 1;
//        }
//        else if (Qizi::flag == 1)
//        {
//            Qizi::to = this->id;
//            Qizi::flag = 2;
//        }
//    });
    //this->setStyleSheet("background-image:circle");
}
