#ifndef CHOOSEPLAYERSCENE_H
#define CHOOSEPLAYERSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "playscene.h"

class ChoosePlayerScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoosePlayerScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * ev);

    PlayScene * play = NULL;

signals:
    void chooseBack();
};

#endif // CHOOSEPLAYERSCENE_H
