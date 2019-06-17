#include "gamewindowscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "player.h"
#include "map.h"
#include "gamewindow.h"

GameWindowScene::GameWindowScene(Player *p, GameWindow *g, QObject *parent) : QGraphicsScene(0,0,8000,720, parent) {
	player = p;
	gamewindow = g;
}

void GameWindowScene::set_map(Map *m) {
	map = m;
}

void GameWindowScene::keyPressEvent(QKeyEvent *event) {
	switch (event->key()){
		case Qt::Key_Right:
			//qDebug()<<"Press Right";
			player->action->move(4);
			right_event();
			break;
		case Qt::Key_Left:
			//qDebug()<<"Press Left";
			player->action->move(3);
			left_event();
			break;
		case Qt::Key_Up:
			//qDebug()<<"Press Up";
			player->action->move(1);
			up_event();
			break;
		case Qt::Key_Down:
			//qDebug()<<"Press Down";
			player->action->move(2);
			down_event();
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

void GameWindowScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	qreal x = event->scenePos().x(), y = event->scenePos().y();
	qDebug()<<"Mouse Event: ("<<x<<","<<y<<")";
	if((player->action->get_status() == 0 || player->action->get_status() == 2) && x >= 800 && y >= 560) {
		map->open_bag(0, 0);
	} else if(player->action->get_status() == 6 && x >= 1080 && y <= 70) {
		map->close_bbq();
	} else if(player->action->get_status() == 6 && x >= 540 && x <= 720 && y >= 280 && y <= 430 && player->bag->get_item_num(9)) {
		player->action->bbq();
	} else if(player->action->get_status() == 7 && x >= 1080 && y <= 70) {
		map->close_stove();
	} else if(player->action->get_status() == 7 && x >= 550 && x <= 720 && y >= 300 && y <= 440 && player->bag->get_item_num(1) && player->bag->get_item_num(2)) {
		player->action->stove();
	} else if(player->action->get_status() == 5 && x >= 1080 && y <= 70) {
		map->close_furnace();
	} else if(player->action->get_status() == 5 && x >= 640 && x <= 790 && y >= 340 && y <= 490) {
		player->action->furnace(map->get_now_use_d());
	} else if(player->action->get_status() == 5 && x >= 0 && x <= 220 && y >= 0 && y <= 170) {
		map->open_furnace(1, 0);
	} else if(player->action->get_status() == 5 && x >= 0 && x <= 220 && y >= 171 && y <= 340) {
		map->open_furnace(2, 0);
	} else if(player->action->get_status() == 5 && x >= 0 && x <= 220 && y >= 341 && y <= 510) {
		map->open_furnace(3, 0);
	} else if(player->action->get_status() == 8 && map->get_fight_result() == 0) {

//		qDebug()<<"fight: "<<map->get_fight_result();
		if(x>=240 && x<=400 && y>=515 && y<= 710) {
			map->open_fight(1, 0, 0);
		} else if(x>=560 && x<=720 && y>=515 && y<= 710) {
			map->open_fight(2, 0, 0);
		} else if(x>=880 && x<=1040 && y>=515 && y<= 710) {
			map->open_fight(3, 0, 0);
		} else if(x>=430 && x<=800 && y>=140 && y<= 420) {
			player->action->attack();
		}
	} else if(player->action->get_status() == 8 && x >= 1080 && y <= 70) {
		if(player->action->exit_attack(map->get_fight_result())) {
			map->close_fight();
		}
	} else if(player->action->get_status() == 9) {
		if(x>=60 && x<=260 && y>=180 && y<= 380) {
			map->open_bag(0, 0);
		} else if(x>=300 && x<=500 && y>=180 && y<= 380) {
			map->open_bag(1, 0);
		} else if(x>=540 && x<=740 && y>=180 && y<= 380) {
			map->open_bag(2, 0);
		} else if(x>=780 && x<=980 && y>=180 && y<= 380) {
			map->open_bag(3, 0);
		} else if(x>=1020 && x<=1220 && y>=180 && y<= 380) {
			map->open_bag(4, 0);
		} else if(x>=60 && x<=260 && y>=420 && y<= 620) {
			map->open_bag(5, 0);
		} else if(x>=300 && x<=500 && y>=420 && y<= 620) {
			map->open_bag(6, 0);
		} else if(x>=540 && x<=740 && y>=420 && y<= 620) {
			map->open_bag(7, 0);
		} else if(x>=780 && x<=980 && y>=420 && y<= 620) {
			map->open_bag(8, 0);
		} else if(x>=1020 && x<=1220 && y>=420 && y<= 620) {
			map->open_bag(9, 0);
		} else if(x >= 1080 && y <= 70) {
			map->close_bag();
		}
	}/* else if(player->action->get_status() == 4 && x >= 1080 && y <= 70) {
		gamewindow->back_to_main_window(true);
	}*/
}

void GameWindowScene::space_event() {
	//qDebug()<<"space event";
	map->exit_pause();
}

void GameWindowScene::f_event() {
	if((player->action->get_status() == 0 || player->action->get_status() == 2) && map->get_local_item() == 3) {
		player->action->pick(3);
	} else if((player->action->get_status() == 0 || player->action->get_status() == 2) && map->get_local_item() == 9) {
		player->action->pick(9);
	} else if((player->action->get_status() == 0 || player->action->get_status() == 2) && map->get_local_item() == 10) {
		player->action->pick(10);
	} else if((player->action->get_status() == 0 || player->action->get_status() == 2) && map->get_local_item() == 8) {
		map->open_fight(1, 1, 0);
	} else if(player->action->get_status() == 8 && map->get_fight_result() == 0) {
		qDebug()<<"fight"<<map->get_fight_result();
		player->action->attack();
	} else if(player->action->get_status() == 6 && player->bag->get_item_num(9)) {
		player->action->bbq();
	} else if(player->action->get_status() == 7 && player->bag->get_item_num(1) && player->bag->get_item_num(2)) {
		player->action->stove();
	} else if(player->action->get_status() == 5) {
		player->action->furnace(map->get_now_use_d());
	} else if(player->action->get_status() == 9) {
		player->action->use_item();
	}
}

void GameWindowScene::q_event() {
	if(player->action->get_status() == 6) {
		map->close_bbq();
	} else if(player->action->get_status() == 9) {
		map->close_bag();
	} else if(player->action->get_status() == 7) {
		map->close_stove();
	} else if(player->action->get_status() == 5) {
		map->close_furnace();
	} else if(player->action->get_status() == 8) {
		if(player->action->exit_attack(map->get_fight_result())) {
			map->close_fight();
		}
	} else if(player->action->get_status() == 4) {
		gamewindow->back_to_main_window();
	}
}

void GameWindowScene::up_event() {
	if(player->action->get_status() == 5) {
		qDebug()<<"up 5";
		int ini;
		if(map->get_now_use_d() == 0) {
			ini = 1;
		} else {
			ini = 0;
		}
		if(map->get_now_use_d() == 1) {
			map->open_furnace(3, ini);
		} else if(map->get_now_use_d() == 2) {
			map->open_furnace(1, ini);
		} else if (map->get_now_use_d() == 3) {
			map->open_furnace(2, ini);
		}
	} else if(player->action->get_status() == 9) {
		qDebug()<<"bag up";
		if(map->get_bag_select() < 5) {
			map->open_bag(map->get_bag_select()+5, 0);
		} else {
			map->open_bag(map->get_bag_select()-5, 0);
		}
	}
}

void GameWindowScene::down_event() {
	if(player->action->get_status() == 5) {
		qDebug()<<"down 5";
		int ini;
		if(map->get_now_use_d() == 0) {
			ini = 1;
		} else {
			ini = 0;
		}
		if(map->get_now_use_d() == 1) {
			map->open_furnace(2, ini);
		} else if(map->get_now_use_d() == 2) {
			map->open_furnace(3, ini);
		} else if (map->get_now_use_d() == 3) {
			map->open_furnace(1, ini);
		}
	} else if(player->action->get_status() == 9) {
		qDebug()<<"bag down";
		if(map->get_bag_select() < 5) {
			map->open_bag(map->get_bag_select()+5, 0);
		} else {
			map->open_bag(map->get_bag_select()-5, 0);
		}
	}
}

void GameWindowScene::left_event() {
	if(player->action->get_status() == 8 && map->get_fight_result() == 0) {
		qDebug()<<"left 8";
		int ini;
		if(map->get_now_use_d() == 0) {
			ini = 1;
		} else {
			ini = 0;
		}
		if(map->get_now_use_d() == 1) {
			map->open_fight(3, ini, 0);
		} else if(map->get_now_use_d() == 2) {
			map->open_fight(1, ini, 0);
		} else if (map->get_now_use_d() == 3) {
			map->open_fight(2, ini, 0);
		}
	} else if(player->action->get_status() == 9) {
		qDebug()<<"bag left";
		if(map->get_bag_select() == 0) {
			map->open_bag(9, 0);
		} else {
			map->open_bag(map->get_bag_select()-1, 0);
		}
	}
}

void GameWindowScene::right_event() {
	if(player->action->get_status() == 8 && map->get_fight_result() == 0) {
		qDebug()<<"left 8";
		int ini;
		if(map->get_now_use_d() == 0) {
			ini = 1;
		} else {
			ini = 0;
		}
		if(map->get_now_use_d() == 1) {
			map->open_fight(2, ini, 0);
		} else if(map->get_now_use_d() == 2) {
			map->open_fight(3, ini, 0);
		} else if (map->get_now_use_d() == 3) {
			map->open_fight(1, ini, 0);
		}
	} else if(player->action->get_status() == 9) {
		qDebug()<<"bag right";
		if(map->get_bag_select() == 9) {
			map->open_bag(0, 0);
		} else {
			map->open_bag(map->get_bag_select()+1, 0);
		}
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
