#include "gamewindowscene.h"
#include <QGraphicsScene>
#include <QDebug>
#include "player.h"

GameWindowScene::GameWindowScene(Player *p, QObject *parent) : QGraphicsScene(0,0,8000,720, parent)
{
	player = p;
	qDebug()<<"create scene";
}

void GameWindowScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()){
		case Qt::Key_Right:
			qDebug()<<"Press Right";
			break;
		case Qt::Key_Left:
			qDebug()<<"Press Left";

			break;
		case Qt::Key_Up:
			qDebug()<<"Press Up";

			break;
		case Qt::Key_Down:
			qDebug()<<"Press Down";
			player->action->move(2);

			break;
	}
}
/*
void GameWindowScene::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()){
	case Qt::Key_Right:
		qDebug()<<"Release Right";
		break;
	}
}
*/
