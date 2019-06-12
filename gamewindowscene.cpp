#include "gamewindowscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "player.h"
#include "map.h"

GameWindowScene::GameWindowScene(Player *p, QObject *parent) : QGraphicsScene(0,0,8000,720, parent)
{
	player = p;
	//qDebug()<<"create scene";

}

void GameWindowScene::set_map(Map *m)
{
	map = m;
}

void GameWindowScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()){
		case Qt::Key_Right:
			//qDebug()<<"Press Right";
			player->action->move(4);
			break;
		case Qt::Key_Left:
			//qDebug()<<"Press Left";
			player->action->move(3);
			break;
		case Qt::Key_Up:
			//qDebug()<<"Press Up";
			player->action->move(1);
			break;
		case Qt::Key_Down:
			//qDebug()<<"Press Down";
			player->action->move(2);
			break;
		case Qt::Key_Space:
			space_event();
			break;
		case Qt::Key_F:
			f_event();
			break;
	}
}

void GameWindowScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qreal x = event->scenePos().x(), y = event->scenePos().y();
	//qDebug()<<"Mouse Event: ("<<x<<","<<y<<")";
	if(x >= 800 && y >= 560) {
		map->open_bag();
	}
}

void GameWindowScene::space_event()
{
	//qDebug()<<"space event";
	map->exit_pause();
}

void GameWindowScene::f_event()
{
	if(map->get_local_item() == 3) {
		player->action->pick();
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
