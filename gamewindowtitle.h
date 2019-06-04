#ifndef GAMEWINDOWTITLE_H
#define GAMEWINDOWTITLE_H

#include "gamewindow.h"
#include "gamewindowview.h"
#include <QGraphicsScene>

class GameWindowView;
class GameWindowScene;
class GameWindowTitle : public QGraphicsScene
{
    Q_OBJECT
public:
    GameWindowTitle(GameWindowView *view, QWidget *parent = 0);

private:
    GameWindowView *viewer;
    GameWindowScene *scene;
};

#endif // GAMEWINDOWTITLE_H
