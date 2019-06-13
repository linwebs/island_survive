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
		case Qt::Key_Q:
			q_event();
			break;
	}
}

void GameWindowScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qreal x = event->scenePos().x(), y = event->scenePos().y();
	qDebug()<<"Mouse Event: ("<<x<<","<<y<<")";
	if(player->action->get_status() == 0 && x >= 800 && y >= 560) {
		map->open_bag();
	} else if(player->action->get_status() == 6 && x >= 1080 && y <= 70) {
		map->close_bbq();
	} else if(player->action->get_status() == 6 && x >= 539 && x <= 720 && y >= 280 && y <= 430 && player->bag->get_item_num(9)) {
		player->action->bbq();
	}
}

void GameWindowScene::space_event()
{
	//qDebug()<<"space event";
	map->exit_pause();
}

void GameWindowScene::f_event()
{
	if(player->action->get_status() == 0 && map->get_local_item() == 3) {
		player->action->pick();
	} else if(player->action->get_status() == 6 && player->bag->get_item_num(9)) {
		player->action->bbq();
	}
}

void GameWindowScene::q_event() {
	if(player->action->get_status() == 6) {
		map->close_bbq();
	} else if(player->action->get_status() == 9) {
		map->close_bag();
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
