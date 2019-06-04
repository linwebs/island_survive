#ifndef GAMEWINDOWVIEW_H
#define GAMEWINDOWVIEW_H

#include "gamewindow.h"
#include "gamewindowscene.h"
#include <QLabel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

//class GameWindowScene;

class GameWindowView : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindowView();
    void sceneSet(QGraphicsScene *);
private:
	QGraphicsScene *scene;
//	GameWindowScene * scene;
	//Player * player;

};

#endif // GAMEWINDOWVIEW_H
