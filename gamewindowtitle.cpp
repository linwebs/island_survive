#include "gamewindowtitle.h"
#include "gamewindowscene.h"
#include <QDebug>

GameWindowTitle::GameWindowTitle(GameWindowView *view, QWidget *parent) : QGraphicsScene(parent)
{
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);

    viewer = view;

    scene = new GameWindowScene(this);
    scene->setFocus();
    viewer->sceneSet(scene);
    qDebug()<<"create title";
}
