#include "map.h"
#include "gamewindowscene.h"
#include "system.h"
#include "player.h"
#include "bag.h"
#include "struct.cpp"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

Map::Map(GameWindowScene *GWscene, int *p)
{
	scene = GWscene;
	map.clear();

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);
	create_land();
	create_items(System::get_default_map());
	initialize_items();
	generate_player(true);
	show_energy_blood(100, 100);
	play_time = p;
	local_item = 0;
	last_local_item = 0;
	// update_map(8, 3, 1);
	show();
}

Map::Map(vector<maps> maps)
{
	map = maps;
}

bool Map::set_player(Player *p)
{
	player = p;
	player->bag->put(9);
	player->bag->put(9);
	player->bag->put(9);
	player->bag->put(9);
	player->bag->put(9);
	/* test bag items
	player->bag->put(3);
	player->bag->put(2);
	player->bag->put(3);
	player->bag->put(6);
	player->bag->put(4);
	player->bag->put(1);
	player->bag->put(4);
	player->bag->take(5);
	player->bag->put(1);
	player->bag->put(2);
	player->bag->put(3);
	player->bag->put(4);
	player->bag->put(5);
	player->bag->put(6);
	player->bag->put(7);
	player->bag->put(8);
	player->bag->put(9);
	player->bag->put(10);
*/
	show_bags();
}

bool Map::create_land()
{
	for(int i=0; i<16; i++) {
		for(int j=0; j<9; j++) {
			background[i][j] = new QGraphicsPixmapItem();
			background[i][j]->setPixmap(QPixmap("://res/img/land/soil_80.png"));
			background[i][j]->setPos(i*80, j*80);
			scene->addItem(background[i][j]);
		}
	}
}

bool Map::update_map(int &player_x, int &player_y, int &player_di)
{
	last_local_item = local_item;
	local_item = map_items[player_x+7][player_y+2].item;
	qDebug()<<"("<<player_x<<", "<<player_y<<")"<<local_item;

	if(map_items[player_x+7][player_y+2].walk==0) {
		items_event();
		return false;
	} else {
		for(int i=0; i<16; i++) {
			for(int j=0; j<9; j++) {
				scene->removeItem(map_now[i][j]);
				map_now[i][j]= new QGraphicsPixmapItem();
				map_now[i][j]->setPixmap(QPixmap(map_items[i+player_x][j+player_y].img));
				map_now[i][j]->setPos(i*80, 640-j*80);
				scene->addItem(map_now[i][j]);
			}
		}
		generate_player(false);
		items_event();
		show_energy_blood(player->energy->get_energy(), player->blood->get_blood());
		show_bags();

		return true;
	}
}


bool Map::items_event()
{
	switch (local_item) {
		case 3:
			// grass
			if(last_local_item == 3) {
				scene->removeItem(hint_text);
				delete  hint_text;
			}
			hint_text= new QGraphicsPixmapItem();
			hint_text->setPixmap(QPixmap("://res/img/action/f_pick_grass_30.png"));
			hint_text->setPos(660, 500);
			scene->addItem(hint_text);
			break;
		case 4:
			// home
			save_file();
			break;
		case 5:
			// enter furnace
			break;
		case 6:
			open_bbq();
			// enter bbq
			break;
		case 7:
			// enter stove
			break;
		case 8:
			// action fight
			break;
		case 9:
			// pick wood
			break;
		case 10:
			// pick stone
			break;
	}

	if(last_local_item == 3 && local_item != 3) {
		scene->removeItem(hint_text);
		delete hint_text;
	}
}

bool Map::save_file()
{
	pause_game();
	player->action->change_status(3);
	//	qDebug()<<"save";

	//return true;
}

bool Map::exit_pause()
{
	if(player->action->get_status() == 1 || player->action->get_status() == 3) {
		scene->removeItem(save_bgm);
		scene->removeItem(pause_text);
		scene->removeItem(pause_time);
		delete save_bgm;
		delete  pause_text;
		delete  pause_time;
		player->action->change_status(0);
	}
}

void Map::pause_game()
{
	player->action->change_status(1);
	save_bgm = new QGraphicsRectItem();
	save_bgm->setRect(0, 0, 1280, 720);
	save_bgm->setPen(Qt::NoPen);
	save_bgm->setBrush(QColor(0, 0, 0, 200));
	scene->addItem(save_bgm);

	pause_text= new QGraphicsPixmapItem();
	pause_text->setPixmap(QPixmap("://res/img/frame/game_pause_text.png"));
	pause_text->setPos(320, 200);
	scene->addItem(pause_text);
	pause_time = new QGraphicsTextItem();
	pause_time->setPos(410, 400);
	pause_time->setDefaultTextColor(Qt::white);
	pause_time->setFont(QFont("Microsoft JhengHei", 20));
	pause_time->setPlainText(QString("目前存活時間: ")+QString::number(*play_time)+QString("秒，按空白鍵繼續遊戲"));
	scene->addItem(pause_time);
}

void Map::open_bbq()
{
	if(player->action->get_status() != 6) {
		if(!player->action->change_status(6)) {
			qDebug()<<"map::bbq change status error!";
		}
	} else {
		scene->removeItem(bbq_bgm);
		scene->removeItem(bbq_exit);
		scene->removeItem(bbq_flesh_text);
		scene->removeItem(bbq_meat_text);
		delete bbq_bgm;
		delete  bbq_exit;
		delete bbq_meat_text;
		delete  bbq_flesh_text;
	}
	qDebug()<<"bbq";

	// bgm
	bbq_bgm= new QGraphicsPixmapItem();
	bbq_bgm->setPixmap(QPixmap("://res/img/frame/bbq/bbq_bgm.png"));
	bbq_bgm->setPos(0, 0);
	scene->addItem(bbq_bgm);

	// exit btn
	bbq_exit= new QGraphicsPixmapItem();
	bbq_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	bbq_exit->setPos(1090, 10);
	scene->addItem(bbq_exit);

	// bbq_flesh_text
	bbq_flesh_text = new QGraphicsTextItem();
	bbq_flesh_text->setPos(388, 460);
	bbq_flesh_text->setDefaultTextColor(Qt::black);
	bbq_flesh_text->setFont(QFont("Microsoft JhengHei", 20));
	bbq_flesh_text->setPlainText(QString::number(player->bag->get_item_num(9)));
	scene->addItem(bbq_flesh_text);

	// bbq_meat_text
	bbq_meat_text = new QGraphicsTextItem();
	bbq_meat_text->setPos(1048, 460);
	bbq_meat_text->setDefaultTextColor(Qt::black);
	bbq_meat_text->setFont(QFont("Microsoft JhengHei", 20));
	bbq_meat_text->setPlainText(QString::number(player->bag->get_item_num(10)));
	scene->addItem(bbq_meat_text);
}

void Map::close_bbq() {
	if(player->action->get_status() == 6) {
		if(!player->action->change_status(0)) {
			qDebug()<<"map::bbq change status error!";
		}
		scene->removeItem(bbq_bgm);
		scene->removeItem(bbq_exit);
		scene->removeItem(bbq_flesh_text);
		scene->removeItem(bbq_meat_text);
		delete bbq_bgm;
		delete  bbq_exit;
		delete bbq_meat_text;
		delete  bbq_flesh_text;
	}
}


void Map::open_bag()
{
	if(player->action->get_status() == 9) {
		close_bag();
	} else {
		player->action->change_status(9);
		bag_bgm= new QGraphicsPixmapItem();
		bag_bgm->setPixmap(QPixmap("://res/img/frame/bag/bags_bgm.png"));
		bag_bgm->setPos(0, 0);
		scene->addItem(bag_bgm);

		const vector<bags> bag = *player->bag->get_items();

		for(int i=0; i<bag.size(); i++) {
			// img
			bag_items[i] = new QGraphicsPixmapItem();

			// text
			bag_items_text[i] = new QGraphicsTextItem();
			if(i==0) {
				bag_items[i]->setPos(69, 190);
				bag_items_text[i]->setPos(210, 334);
			} else if(i==1) {
				bag_items[i]->setPos(309, 190);
				bag_items_text[i]->setPos(450, 334);
			} else if(i==2) {
				bag_items[i]->setPos(550, 190);
				bag_items_text[i]->setPos(690, 334);
			} else if(i==3) {
				bag_items[i]->setPos(790, 190);
				bag_items_text[i]->setPos(930, 334);
			} else if(i==4) {
				bag_items[i]->setPos(1030, 190);
				bag_items_text[i]->setPos(1170, 334);
			} else if(i==5) {
				bag_items[i]->setPos(69, 430);
				bag_items_text[i]->setPos(210, 574);
			} else if(i==6) {
				bag_items[i]->setPos(309, 430);
				bag_items_text[i]->setPos(450, 574);
			} else if(i==7) {
				bag_items[i]->setPos(550, 430);
				bag_items_text[i]->setPos(690, 574);
			} else if(i==8) {
				bag_items[i]->setPos(790, 430);
				bag_items_text[i]->setPos(930, 574);
			} else if(i==9) {
				bag_items[i]->setPos(1030, 430);
				bag_items_text[i]->setPos(1170, 574);
			}
			bag_items[i]->setPixmap(QPixmap(System::get_bag_item_file_path(bag[i].item)));
			bag_items_text[i]->setPlainText(QString::number(bag[i].quantity));
			bag_items_text[i]->setDefaultTextColor(Qt::black);
			bag_items_text[i]->setFont(QFont("Microsoft JhengHei", 24));
			scene->addItem(bag_items[i]);
			scene->addItem(bag_items_text[i]);
		}
	}
}

void Map::close_bag()
{
	scene->removeItem(bag_bgm);
	delete bag_bgm;
	const vector<bags> bag = *player->bag->get_items();
	for(int i=0; i<bag.size(); i++) {
		scene->removeItem(bag_items[i]);
		scene->removeItem(bag_items_text[i]);
		delete bag_items[i];
		delete bag_items_text[i];
	}
	player->action->change_status(0);
}

int Map::get_local_item()
{
	return local_item;
}

bool Map::remove_pick_item(int player_x, int player_y, int player_di)
{
	map_items[player_x+7][player_y+2].item = 0;
	map_items[player_x+7][player_y+2].size = 1;
	map_items[player_x+7][player_y+2].walk = 1;
	map_items[player_x+7][player_y+2].img  = "";
	local_item = 0;
	update_map(player_x, player_y, player_di);
	scene->removeItem(hint_text);
	delete hint_text;
}

bool Map::generate_player(bool ini)
{
	if(!ini) {
		scene->removeItem(player_show);
		delete player_show;
	}
	player_show= new QGraphicsPixmapItem();
	player_show->setPixmap(QPixmap("://res/img/character/people_80.png"));
	player_show->setPos(560, 453);
	scene->addItem(player_show);
}

bool Map::initialize_items()
{
	for(int i=0; i<16; i++) {
		for(int j=0; j<9; j++) {
			map_now[i][j]= new QGraphicsPixmapItem();
			map_now[i][j]->setPixmap(QPixmap(map_items[i+7][j+2].img));
			map_now[i][j]->setPos(i*80, 640-j*80);
			scene->addItem(map_now[i][j]);
		}
	}
}

bool Map::create_items(QJsonObject json)
{
	QJsonObject map_size = json["size"].toObject();
	size_height = map_size["height"].toInt() + 8;
	size_width = map_size["width"].toInt() + 15;
	/*
	 * up: 6 ;  down: 2 ;  right: 8 ;  left: 7
	 */

	/* Initialize map_items */
	map_item mi;
	mi.item = 0;
	mi.size = 1;
	mi.walk = 1;
	mi.img  = "";
	vector<map_item> md;
	md.assign(static_cast<unsigned long long int>(size_height), mi);
	map_items.assign(static_cast<unsigned long long int>(size_width), md);

	//qDebug()<<size_height<<"*"<<size_width;

	// left
	for(int i=0; i<size_height; i++) {
		for(int j=0; j<7; j++) {
			//qDebug()<<j<<","<<i;
			map_items[j][i].item = 1;
			map_items[j][i].img = "://res/img/land/sea_80.png";
		}
	}
	for(int i=2; i<size_height-6; i++) {
		map_items[6][i].item = 2;
		map_items[6][i].img = "://res/img/land/box_80.png";
	}

	// right
	for(int i=0; i<size_height; i++) {
		for(int j=size_width-8; j<size_width; j++) {
			//qDebug()<<j<<","<<i;
			map_items[j][i].item = 1;
			map_items[j][i].img = "://res/img/land/sea_80.png";
		}
	}
	for(int i=2; i<size_height-6; i++) {
		map_items[size_width-8][i].item = 2;
		map_items[size_width-8][i].img = "://res/img/land/box_80.png";
	}
	// bottom
	for(int i=7; i<size_width-8; i++) {
		for(int j=0; j<1; j++) {
			//qDebug()<<i<<","<<j;
			map_items[i][j].item = 1;
			map_items[i][j].img = "://res/img/land/sea_80.png";
		}
	}
	for(int i=6; i<size_width-7; i++) {
		map_items[i][1].item = 2;
		map_items[i][1].img = "://res/img/land/box_80.png";
	}

	// top
	for(int i=7; i<size_width-8; i++) {
		for(int j=size_height-5; j<size_height; j++) {
			//qDebug()<<i<<","<<j;
			map_items[i][j].item = 1;
			map_items[i][j].img = "://res/img/land/sea_80.png";
		}
	}
	for(int i=6; i<size_width-7; i++) {
		//qDebug()<<i<<","<<size_height-6;
		map_items[i][size_height-6].item = 2;
		map_items[i][size_height-6].img = "://res/img/land/box_80.png";
	}

	//qDebug()<<map_items[3][4].img;

	/* put item in to map_items */
	QJsonArray map_item_json = json["items"].toArray();
	int map_x, map_y, map_it, map_si, map_wa;
	QString map_img;
	for(int i=0; i<map_item_json.size(); i++) {
		map_x = map_item_json[i].toObject()["x_axis"].toInt()+7;
		map_y = map_item_json[i].toObject()["y_axis"].toInt()+2;
		map_it = map_item_json[i].toObject()["item"].toInt();
		map_items[map_x][map_y].item = map_it;
		map_si = map_item_json[i].toObject()["size"].toInt();
		map_items[map_x][map_y].size = map_si;
		map_wa = map_item_json[i].toObject()["walk"].toInt();
		map_items[map_x][map_y].walk = map_wa;
		map_img = map_item_json[i].toObject()["img"].toString().toStdString().data();
		map_items[map_x][map_y].img = map_img;
		//		qDebug()<<map_x<<", "<<map_y;
		//		qDebug()<<map_item_json[i].toObject()["img"].toString().toStdString().data();
	}
}

int Map::get_size_height()
{
	return size_height;
}

int Map::get_size_width()
{
	return size_width;
}

int Map::show_energy_blood(int energy_v, int blood_v, QString avatar_v)
{
	QGraphicsPixmapItem *frame, *avatar;
	QGraphicsRectItem *energy, *blood;
	QGraphicsTextItem *energy_t, *blood_t;

	frame= new QGraphicsPixmapItem();
	frame->setPixmap(QPixmap("://res/img/frame/ebh.png"));
	frame->setPos(10, 10);
	scene->addItem(frame);

	blood = new QGraphicsRectItem();
	blood->setRect(183, 61, blood_v*283/100, 38);
	blood->setPen(Qt::NoPen);
	blood->setBrush(QColor(241, 80, 88));
	scene->addItem(blood);
	blood_t = new QGraphicsTextItem();
	if(blood_v>=100) {
		blood_t->setPos(300, 64);
	} else if (blood_v>=10) {
		blood_t->setPos(312, 64);
	} else {
		blood_t->setPos(324, 64);
	}
	blood_t->setDefaultTextColor(Qt::black);
	blood_t->setFont(QFont("Microsoft JhengHei", 16));
	blood_t->setPlainText(QString::number(blood_v)+QString("%"));
	scene->addItem(blood_t);

	energy = new QGraphicsRectItem();
	energy->setRect(184, 108, energy_v*282/100, 43);
	energy->setPen(Qt::NoPen);
	energy->setBrush(QColor(0, 162, 232));
	scene->addItem(energy);
	energy_t = new QGraphicsTextItem();
	if(energy_v>=100) {
		energy_t->setPos(300, 114);
	} else if (energy_v>=10) {
		energy_t->setPos(312, 114);
	} else {
		energy_t->setPos(324, 114);
	}
	energy_t->setDefaultTextColor(Qt::black);
	energy_t->setFont(QFont("Microsoft JhengHei", 16));
	energy_t->setPlainText(QString::number(energy_v)+QString("%"));
	scene->addItem(energy_t);

	avatar = new QGraphicsPixmapItem();
	avatar->setPixmap(QPixmap(avatar_v));
	avatar->setPos(36, 26);
	scene->addItem(avatar);
}

void Map::show_bags()
{
	bags_bgm = new QGraphicsPixmapItem();
	bags_bgm->setPixmap(QPixmap("://res/img/bag/bags.png"));
	bags_bgm->setPos(880, 560);
	scene->addItem(bags_bgm);

	const vector<bags> bag = *player->bag->get_items();
	for(int i=0; i<bag.size(); i++) {
		// img
		bags_items[i] = new QGraphicsPixmapItem();

		// text
		bags_items_text[i] = new QGraphicsTextItem();
		if(i==0) {
			bags_items[i]->setPos(891, 571);
			bags_items_text[i]->setPos(923, 603);
		} else if(i==1) {
			bags_items[i]->setPos(967, 571);
			bags_items_text[i]->setPos(1000, 603);
		} else if(i==2) {
			bags_items[i]->setPos(1044, 571);
			bags_items_text[i]->setPos(1077, 603);
		} else if(i==3) {
			bags_items[i]->setPos(1120, 571);
			bags_items_text[i]->setPos(1153, 603);
		} else if(i==4) {
			bags_items[i]->setPos(1197, 571);
			bags_items_text[i]->setPos(1230, 603);
		} else if(i==5) {
			bags_items[i]->setPos(891, 646);
			bags_items_text[i]->setPos(923, 678);
		} else if(i==6) {
			bags_items[i]->setPos(967, 646);
			bags_items_text[i]->setPos(1000, 678);
		} else if(i==7) {
			bags_items[i]->setPos(1044, 646);
			bags_items_text[i]->setPos(1077, 678);
		} else if(i==8) {
			bags_items[i]->setPos(1120, 646);
			bags_items_text[i]->setPos(1153, 678);
		} else if(i==9) {
			bags_items[i]->setPos(1197, 646);
			bags_items_text[i]->setPos(1230, 678);
		}
		bags_items[i]->setPixmap(QPixmap(System::get_bags_item_file_path(bag[i].item)));
		bags_items_text[i]->setPlainText(QString::number(bag[i].quantity));
		bags_items_text[i]->setDefaultTextColor(Qt::black);
		bags_items_text[i]->setFont(QFont("Microsoft JhengHei", 12));
		scene->addItem(bags_items[i]);
		scene->addItem(bags_items_text[i]);
	}
}
