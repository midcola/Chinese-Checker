#ifndef QIZI_H
#define QIZI_H

#include <QWidget>
#include <QPushButton>

class Qizi : public QPushButton
{
    Q_OBJECT
public:
    explicit Qizi(QWidget *parent = nullptr);

    int id;

    QString colorId;

    int turn;

signals:
    void myClick1();
    void myClick2();

};

#endif // QIZI_H
