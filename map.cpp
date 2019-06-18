#include "map.h"
#include "gamewindowscene.h"
#include "gamewindow.h"
#include "system.h"
#include "struct.cpp"
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
#include <QTime>

Map::Map(GameWindowScene *GWscene, int *t, Player *p, GameWindow*g)
{
	scene = GWscene;
	map.clear();
	player = p;
	play_time = t;
	gamewindow = g;
	local_item = 0;
	last_local_item = 0;
	now_use_d = 0;
	fight_result = 0;
	bag_select = 0;
	show_purple_time = false;
	show_use_item_hint = false;

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);
	create_land();
	create_items(System::get_default_map());
	initialize_items(4, 0);
	generate_player(true);
	show_energy_blood(true, 100, 100);
	show_bags();
	show();
}

Map::Map(GameWindowScene *GWscene, int *t, Player *p, QString save, GameWindow*g)
{
	scene = GWscene;
	map.clear();
	player = p;
	play_time = t;
	gamewindow = g;
	local_item = 0;
	last_local_item = 0;
	now_use_d = 0;
	fight_result = 0;
	bag_select = 0;
	show_purple_time = false;
	show_use_item_hint = false;

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);
	create_land();
	create_items(System::read_save_file(save));
	// read file
	initialize_items(player->action->get_x_axis(), player->action->get_y_axis());
	generate_player(true);
	show_energy_blood(true, player->energy->get_energy(), player->blood->get_blood());
	show_bags();
	show();
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

bool Map::generate_grass()
{
	int x, y;
	while(1) {
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		x = qrand()%(size_width);
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		y = qrand()%(size_height);
		qDebug()<<"new grass: ("<<x-7<<","<<y-2<<")";
		if(x<=0 && y<=0) {
			qDebug()<<"again";
		} else if(x<(home_size_width+7) && y<(home_size_height+2)) {
			qDebug()<<"at home";
		} else {
			if(map_items[x][y].item == 0) {
				map_items[x][y].item = 3;
				map_items[x][y].size = 1;
				map_items[x][y].walk = 1;
				map_items[x][y].img = MAP_GRASS_PATH;
				qDebug()<<"add grass";
				break;
			}
		}
	}
}

bool Map::generate_wood()
{
	int x, y;
	while(1) {
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		x = qrand()%(size_width);
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		y = qrand()%(size_height);
		qDebug()<<"new wood: ("<<x-7<<","<<y-2<<")";
		if(x<=0 && y<=0) {
			qDebug()<<"again";
		} else if(x<(home_size_width+7) && y<(home_size_height+2)) {
			qDebug()<<"at home";
		} else {
			if(map_items[x][y].item == 0) {
				map_items[x][y].item = 9;
				map_items[x][y].size = 1;
				map_items[x][y].walk = 1;
				map_items[x][y].img = MAP_WOOD_PATH;
				qDebug()<<"add wood";
				break;
			}
		}
	}
}

void Map::open_bag_full_hint(bool ini)
{
	// bgm
	bag_full_hint= new QGraphicsPixmapItem();
	bag_full_hint->setPixmap(QPixmap("://res/img/frame/bag/hint/bag_full.png"));
	bag_full_hint->setPos(880, 80);
	scene->addItem(bag_full_hint);
	if(ini) {
		gamewindow->set_bag_full_show_time(3);
	}
}

void Map::close_bag_full_hint() {
	scene->removeItem(bag_full_hint);
	delete bag_full_hint;
}

void Map::open_use_item_hint(bool ini, QString img)
{
	if(show_use_item_hint) {
		scene->removeItem(use_item_hint);
		delete use_item_hint;
	}
	qDebug()<<"use: "<<img;
	// bgm
	use_item_hint= new QGraphicsPixmapItem();
	use_item_hint->setPixmap(QPixmap(img));
	use_item_hint->setPos(880, 80);
	scene->addItem(use_item_hint);
	if(ini) {
		gamewindow->set_use_item_time(3);
		gamewindow->set_use_item_img(img);
		show_use_item_hint = true;
	}
}

void Map::close_use_item_hint() {
	scene->removeItem(use_item_hint);
	show_use_item_hint = false;
	delete use_item_hint;
}

vector<vector<map_item> > *Map::get_map_items()
{
	return &map_items;
}

bool Map::generate_stone()
{
	int x, y;
	while(1) {
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		x = qrand()%(size_width);
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		y = qrand()%(size_height);
		qDebug()<<"new stone: ("<<x-7<<","<<y-2<<")";
		if(x<=0 && y<=0) {
			qDebug()<<"again";
		} else if(x<(home_size_width+7) && y<(home_size_height+2)) {
			qDebug()<<"at home";
		} else {
			if(map_items[x][y].item == 0) {
				map_items[x][y].item = 10;
				map_items[x][y].size = 1;
				map_items[x][y].walk = 1;
				map_items[x][y].img = MAP_STONE_PATH;
				qDebug()<<"add stone";
				break;
			}
		}
	}
}

bool Map::generate_animal()
{
	int x, y;
	while(1) {
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		x = qrand()%(size_width);
		qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
		y = qrand()%(size_height);
		qDebug()<<"new animal: ("<<x-7<<","<<y-2<<")";
		if(x<=0 && y<=0) {
			qDebug()<<"again";
		} else if(x<(home_size_width+7) && y<(home_size_height+2)) {
			qDebug()<<"at home";
		} else {
			if(map_items[x][y].item == 0) {
				map_items[x][y].item = 8;
				map_items[x][y].size = 1;
				map_items[x][y].walk = 1;
				map_items[x][y].img = MAP_ANIMAL_PATH;
				qDebug()<<"add animal";
				break;
			}
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
		show_energy_blood(false, player->energy->get_energy(), player->blood->get_blood());
		show_bags();

		if(gamewindow->get_bag_full_show_time() > 0) {
			close_bag_full_hint();
			open_bag_full_hint(false);
		}
		if(gamewindow->get_use_item_time() > 0) {
			close_use_item_hint();
			open_use_item_hint(false, gamewindow->get_use_item_img());
		}
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
			open_furnace(1, 1);
			// enter furnace
			break;
		case 6:
			open_bbq();
			// enter bbq
			break;
		case 7:
			// enter stove
			open_stove();
			break;
		case 8:
			// action fight
			if(last_local_item == 8) {
				scene->removeItem(hint_text);
				delete  hint_text;
			}
			hint_text= new QGraphicsPixmapItem();
			hint_text->setPixmap(QPixmap("://res/img/action/f_fight_animal.png"));
			hint_text->setPos(660, 500);
			scene->addItem(hint_text);
			break;
		case 9:
			// pick wood
			if(last_local_item == 9) {
				scene->removeItem(hint_text);
				delete  hint_text;
			}
			hint_text= new QGraphicsPixmapItem();
			hint_text->setPixmap(QPixmap("://res/img/action/f_pick_wood_30.png"));
			hint_text->setPos(660, 500);
			scene->addItem(hint_text);
			break;
		case 10:
			// pick stone
			if(last_local_item == 10) {
				scene->removeItem(hint_text);
				delete  hint_text;
			}
			hint_text= new QGraphicsPixmapItem();
			hint_text->setPixmap(QPixmap("://res/img/action/f_pick_stone_30.png"));
			hint_text->setPos(660, 500);
			scene->addItem(hint_text);
			break;
	}

	if(last_local_item == 3 && local_item != 3) {
		scene->removeItem(hint_text);
		delete hint_text;
	} else if(last_local_item == 8 && local_item != 8) {
		scene->removeItem(hint_text);
		delete hint_text;
	} else if(last_local_item == 9 && local_item != 9) {
		scene->removeItem(hint_text);
		delete hint_text;
	} else if(last_local_item == 10 && local_item != 10) {
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
			qDebug()<<"map::play to bbq change status error!";
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
			qDebug()<<"map::bbq to play change status error!";
		}
		scene->removeItem(bbq_bgm);
		scene->removeItem(bbq_exit);
		scene->removeItem(bbq_flesh_text);
		scene->removeItem(bbq_meat_text);
		delete bbq_bgm;
		delete  bbq_exit;
		delete bbq_meat_text;
		delete  bbq_flesh_text;
		update_map(player->action->get_x_axis(), player->action->get_y_axis(), player->action->get_direction());
	}
}

void Map::open_stove()
{
	if(player->action->get_status() != 7) {
		if(!player->action->change_status(7)) {
			qDebug()<<"map::play to stove change status error!";
		}
	} else {
		scene->removeItem(stove_bgm);
		scene->removeItem(stove_exit);
		scene->removeItem(red_grass_text);
		scene->removeItem(blue_grass_text);
		scene->removeItem(purple_grass_text);
		delete stove_bgm;
		delete stove_exit;
		delete red_grass_text;
		delete blue_grass_text;
		delete purple_grass_text;
	}
	qDebug()<<"stove";

	// bgm
	stove_bgm= new QGraphicsPixmapItem();
	stove_bgm->setPixmap(QPixmap("://res/img/frame/stove/stove_bgm.png"));
	stove_bgm->setPos(0, 0);
	scene->addItem(stove_bgm);

	// exit btn
	stove_exit= new QGraphicsPixmapItem();
	stove_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	stove_exit->setPos(1090, 10);
	scene->addItem(stove_exit);

	// red_grass_text
	red_grass_text = new QGraphicsTextItem();
	red_grass_text->setPos(454, 224);
	red_grass_text->setDefaultTextColor(Qt::black);
	red_grass_text->setFont(QFont("Microsoft JhengHei", 20));
	red_grass_text->setPlainText(QString::number(player->bag->get_item_num(2)));
	scene->addItem(red_grass_text);

	// blue_grass_text
	blue_grass_text = new QGraphicsTextItem();
	blue_grass_text->setPos(924, 224);
	blue_grass_text->setDefaultTextColor(Qt::black);
	blue_grass_text->setFont(QFont("Microsoft JhengHei", 20));
	blue_grass_text->setPlainText(QString::number(player->bag->get_item_num(1)));
	scene->addItem(blue_grass_text);

	// purple_grass_text
	purple_grass_text = new QGraphicsTextItem();
	purple_grass_text->setPos(690, 644);
	purple_grass_text->setDefaultTextColor(Qt::black);
	purple_grass_text->setFont(QFont("Microsoft JhengHei", 20));
	purple_grass_text->setPlainText(QString::number(player->bag->get_item_num(3)));
	scene->addItem(purple_grass_text);
}

void Map::close_stove() {
	if(player->action->get_status() == 7) {
		if(!player->action->change_status(0)) {
			qDebug()<<"map::stove to play change status error!";
		}
		scene->removeItem(stove_bgm);
		scene->removeItem(stove_exit);
		scene->removeItem(red_grass_text);
		scene->removeItem(blue_grass_text);
		scene->removeItem(purple_grass_text);
		delete stove_bgm;
		delete stove_exit;
		delete red_grass_text;
		delete blue_grass_text;
		delete purple_grass_text;
		update_map(player->action->get_x_axis(), player->action->get_y_axis(), player->action->get_direction());
	}
}

void Map::open_furnace(int result, int ini)
{
	if(ini == 1) {
		now_use_d = 1;
	} else {
		now_use_d = result;
	}
	if(player->action->get_status() != 5 || ini == 1) {
		if(!player->action->change_status(5)) {
			qDebug()<<"map::play to furnace change status error!";
		}
	} else {
		scene->removeItem(furnace_bgm);
		scene->removeItem(furnace_exit);
		scene->removeItem(now_use);
		scene->removeItem(wood_text);
		scene->removeItem(stone_text);
		scene->removeItem(result_item);
		scene->removeItem(result_text);
		scene->removeItem(paper_card_text);
		scene->removeItem(scissor_card_text);
		scene->removeItem(stone_card_text);
		delete furnace_bgm;
		delete furnace_exit;
		delete now_use;
		delete wood_text;
		delete stone_text;
		delete result_item;
		delete result_text;
		delete paper_card_text;
		delete scissor_card_text;
		delete stone_card_text;
	}
	qDebug()<<"stove";

	// bgm
	furnace_bgm= new QGraphicsPixmapItem();
	furnace_bgm->setPixmap(QPixmap("://res/img/frame/furnace/furnace_bgm.png"));
	furnace_bgm->setPos(0, 0);
	scene->addItem(furnace_bgm);

	// exit btn
	furnace_exit= new QGraphicsPixmapItem();
	furnace_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	furnace_exit->setPos(1090, 10);
	scene->addItem(furnace_exit);

	// now use
	now_use = new QGraphicsPixmapItem();
	now_use->setPixmap(QPixmap("://res/img/frame/furnace/now_use.png"));
	if(now_use_d == 1) {
		now_use->setPos(220, 64);
	} else if(now_use_d == 2) {
		now_use->setPos(220, 234);
	} else if(now_use_d == 3) {
		now_use->setPos(220, 404);
	}
	scene->addItem(now_use);

	// wood_text
	wood_text = new QGraphicsTextItem();
	wood_text->setPos(540, 226);
	wood_text->setDefaultTextColor(Qt::black);
	wood_text->setFont(QFont("Microsoft JhengHei", 20));
	if(now_use_d == 1) {
		wood_text->setPlainText(QString::number(player->bag->get_item_num(4)) + QString("/") + QString::number(WEAPON_SCISSOR_WOOD));
	} else if(now_use_d == 2) {
		wood_text->setPlainText(QString::number(player->bag->get_item_num(4)) + QString("/") + QString::number(WEAPON_STONE_WOOD));
	} else if(now_use_d == 3) {
		wood_text->setPlainText(QString::number(player->bag->get_item_num(4)) + QString("/") + QString::number(WEAPON_PAPER_WOOD));
	}
	scene->addItem(wood_text);

	// stone_text
	stone_text = new QGraphicsTextItem();
	stone_text->setPos(860, 226);
	stone_text->setDefaultTextColor(Qt::black);
	stone_text->setFont(QFont("Microsoft JhengHei", 20));
	if(now_use_d == 1) {
		stone_text->setPlainText(QString::number(player->bag->get_item_num(5)) + QString("/") + QString::number(WEAPON_SCISSOR_STONE));
	} else if(now_use_d == 2) {
		stone_text->setPlainText(QString::number(player->bag->get_item_num(5)) + QString("/") + QString::number(WEAPON_STONE_STONE));
	} else if(now_use_d == 3) {
		stone_text->setPlainText(QString::number(player->bag->get_item_num(5)) + QString("/") + QString::number(WEAPON_PAPER_STONE));
	}
	scene->addItem(stone_text);

	// result_item
	result_item= new QGraphicsPixmapItem();
	if(now_use_d == 1) {
		result_item->setPixmap(QPixmap("://res/img/frame/furnace/weapon_scissor_140.png"));
	} else if(now_use_d == 2) {
		result_item->setPixmap(QPixmap("://res/img/frame/furnace/weapon_stone_140.png"));
	} else if(now_use_d == 3) {
		result_item->setPixmap(QPixmap("://res/img/frame/furnace/weapon_paper_140.png"));
	}
	result_item->setPos(652, 350);
	scene->addItem(result_item);

	// result_text
	result_text = new QGraphicsTextItem();
	result_text->setPos(756, 460);
	result_text->setDefaultTextColor(Qt::black);
	result_text->setFont(QFont("Microsoft JhengHei", 20));
	if(now_use_d == 1) {
		result_text->setPlainText(QString::number(player->bag->get_item_num(6)));
	} else if(now_use_d == 2) {
		result_text->setPlainText(QString::number(player->bag->get_item_num(7)));
	} else if(now_use_d == 3) {
		result_text->setPlainText(QString::number(player->bag->get_item_num(8)));
	}
	scene->addItem(result_text);

	// scissor_card_text
	scissor_card_text = new QGraphicsTextItem();
	scissor_card_text->setPos(440, 670);
	scissor_card_text->setDefaultTextColor(Qt::black);
	scissor_card_text->setFont(QFont("Microsoft JhengHei", 20));
	scissor_card_text->setPlainText(QString::number(player->bag->get_item_num(6)));
	scene->addItem(scissor_card_text);

	// stone_card_text
	stone_card_text = new QGraphicsTextItem();
	stone_card_text->setPos(740, 670);
	stone_card_text->setDefaultTextColor(Qt::black);
	stone_card_text->setFont(QFont("Microsoft JhengHei", 20));
	stone_card_text->setPlainText(QString::number(player->bag->get_item_num(7)));
	scene->addItem(stone_card_text);

	// paper_card_text
	paper_card_text = new QGraphicsTextItem();
	paper_card_text->setPos(1040, 670);
	paper_card_text->setDefaultTextColor(Qt::black);
	paper_card_text->setFont(QFont("Microsoft JhengHei", 20));
	paper_card_text->setPlainText(QString::number(player->bag->get_item_num(8)));
	scene->addItem(paper_card_text);
}

void Map::close_furnace() {
	if(player->action->get_status() == 5) {
		if(!player->action->change_status(0)) {
			qDebug()<<"map::furnace to play change status error!";
		}
		scene->removeItem(furnace_bgm);
		scene->removeItem(furnace_exit);
		scene->removeItem(now_use);
		scene->removeItem(wood_text);
		scene->removeItem(stone_text);
		scene->removeItem(result_item);
		scene->removeItem(result_text);
		scene->removeItem(scissor_card_text);
		scene->removeItem(stone_card_text);
		scene->removeItem(paper_card_text);
		delete furnace_bgm;
		delete furnace_exit;
		delete now_use;
		delete wood_text;
		delete stone_text;
		delete result_item;
		delete result_text;
		delete scissor_card_text;
		delete stone_card_text;
		delete paper_card_text;
		now_use_d = 0;
		update_map(player->action->get_x_axis(), player->action->get_y_axis(), player->action->get_direction());
	}
}

int Map::get_now_use_d()
{
	return now_use_d;
}

void Map::show_die()
{
	player->action->change_status(4);

	// bgm
	die_bgm= new QGraphicsPixmapItem();
	die_bgm->setPixmap(QPixmap("://res/img/frame/die/die_bgm.png"));
	die_bgm->setPos(0, 0);
	scene->addItem(die_bgm);
/*
	// exit btn
	die_exit= new QGraphicsPixmapItem();
	die_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	die_exit->setPos(1100, 0);
	scene->addItem(die_exit);
*/
	// survive_time
	survive_time = new QGraphicsTextItem();
	survive_time->setPos(560, 30);
	survive_time->setDefaultTextColor(Qt::black);
	survive_time->setFont(QFont("Microsoft JhengHei", 20));
	survive_time->setPlainText(QString("掙扎時間: ") + QString::number(*play_time) + QString("秒"));
	scene->addItem(survive_time);
	player->action->change_status(4);
	qDebug()<<"die";

}

void Map::open_fight(int card, int ini, int result)
{
	fight_result = result;
	if(ini == 1) {
		now_use_d = 1;
	} else {
		now_use_d = card;
	}
	if(player->action->get_status() != 8 || ini == 1) {
		if(!player->action->change_status(8)) {
			qDebug()<<"map::play to furnace change status error!";
		}
	} else {
		scene->removeItem(fight_bgm);
		scene->removeItem(fight_exit);
		scene->removeItem(fight_people);
		scene->removeItem(fight_animal);
		scene->removeItem(fight_text);
		scene->removeItem(fight_now_use_card);
		scene->removeItem(fight_paper_card_text);
		scene->removeItem(fight_scissor_card_text);
		scene->removeItem(fight_stone_card_text);
		delete fight_bgm;
		delete fight_exit;
		delete fight_people;
		delete fight_animal;
		delete fight_text;
		delete fight_now_use_card;
		delete fight_paper_card_text;
		delete fight_scissor_card_text;
		delete fight_stone_card_text;
		scene->removeItem(fight_sword);
		delete fight_sword;/*
		if(fight_result == 0) {
			scene->removeItem(fight_sword);
			delete fight_sword;
		} else {
			scene->removeItem(fight_card_people_bgm);
			scene->removeItem(fight_card_animal_bgm);
			scene->removeItem(fight_card_people);
			scene->removeItem(fight_card_animal);
			delete fight_card_people_bgm;
			delete fight_card_animal_bgm;
			delete fight_card_people;
			delete fight_card_animal;
		}*/
	}
	qDebug()<<"fight";

	// bgm
	fight_bgm= new QGraphicsPixmapItem();
	fight_bgm->setPixmap(QPixmap("://res/img/frame/fight/fight_bgm.png"));
	fight_bgm->setPos(0, 0);
	scene->addItem(fight_bgm);

	// exit btn
	fight_exit= new QGraphicsPixmapItem();
	fight_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	fight_exit->setPos(1090, 10);
	scene->addItem(fight_exit);

	// fight text
	fight_text= new QGraphicsPixmapItem();
	if(fight_result == 0) {
		fight_text->setPixmap(QPixmap("://res/img/frame/fight/fight_text.png"));
	} else if((now_use_d == 1 && fight_result == 2) || (now_use_d == 2 && fight_result == 3) || (now_use_d == 3 && fight_result == 1)) {
		fight_text->setPixmap(QPixmap("://res/img/frame/fight/fight_fail_text.png"));
	} else if((now_use_d == 1 && fight_result == 3) || (now_use_d == 2 && fight_result == 1) || (now_use_d == 3 && fight_result == 2)) {
		fight_text->setPixmap(QPixmap("://res/img/frame/fight/people_success.png"));
	} else {
		fight_text->setPixmap(QPixmap("://res/img/frame/fight/people_flat.png"));
	}
	fight_text->setPos(500, 26);
	scene->addItem(fight_text);

	// fight people
	fight_people= new QGraphicsPixmapItem();
	if((now_use_d == 1 && fight_result == 2) || (now_use_d == 2 && fight_result == 3) || (now_use_d == 3 && fight_result == 1)) {
		fight_people->setPixmap(QPixmap("://res/img/frame/fight/people_fail.png"));
		fight_people->setPos(40, 250);
	} else {
		fight_people->setPixmap(QPixmap("://res/img/frame/fight/people.png"));
		fight_people->setPos(60, 170);
	}
	scene->addItem(fight_people);

	// fight animal
	fight_animal= new QGraphicsPixmapItem();
	if((now_use_d == 1 && fight_result == 3) || (now_use_d == 2 && fight_result == 1) || (now_use_d == 3 && fight_result == 2)) {
		fight_animal->setPixmap(QPixmap("://res/img/frame/fight/animal_fail.png"));
		fight_animal->setPos(930, 230);
	} else {
		fight_animal->setPixmap(QPixmap("://res/img/frame/fight/animal.png"));
		fight_animal->setPos(930, 230);
	}
	scene->addItem(fight_animal);

	if(fight_result == 0) {
		// fight sword
		fight_sword= new QGraphicsPixmapItem();
		fight_sword->setPixmap(QPixmap("://res/img/frame/fight/fight_sword.png"));
		fight_sword->setPos(400, 130);
		scene->addItem(fight_sword);
	} else {
		fight_card_people_bgm= new QGraphicsPixmapItem();
		fight_card_people_bgm->setPixmap(QPixmap("://res/img/frame/fight/fight_card.png"));
		fight_card_people_bgm->setPos(380, 280);
		scene->addItem(fight_card_people_bgm);

		fight_card_animal_bgm= new QGraphicsPixmapItem();
		fight_card_animal_bgm->setPixmap(QPixmap("://res/img/frame/fight/fight_card.png"));
		fight_card_animal_bgm->setPos(730, 280);
		scene->addItem(fight_card_animal_bgm);

		fight_card_people= new QGraphicsPixmapItem();
		if(now_use_d == 1) {
			fight_card_people->setPixmap(QPixmap("://res/img/frame/fight/card_scissor_120.png"));
		} else if (now_use_d == 2) {
			fight_card_people->setPixmap(QPixmap("://res/img/frame/fight/card_stone_120.png"));
		} else if(now_use_d == 3) {
			fight_card_people->setPixmap(QPixmap("://res/img/frame/fight/card_paper_120.png"));
		}
		fight_card_people->setPos(400, 340);
		scene->addItem(fight_card_people);

		fight_card_animal= new QGraphicsPixmapItem();
		if(fight_result == 1) {
			fight_card_animal->setPixmap(QPixmap("://res/img/frame/fight/card_scissor_120.png"));
		} else if (fight_result == 2) {
			fight_card_animal->setPixmap(QPixmap("://res/img/frame/fight/card_stone_120.png"));
		} else if(fight_result == 3) {
			fight_card_animal->setPixmap(QPixmap("://res/img/frame/fight/card_paper_120.png"));
		}
		fight_card_animal->setPos(750, 340);
		scene->addItem(fight_card_animal);
	}

	// fight now use card
	fight_now_use_card= new QGraphicsPixmapItem();
	fight_now_use_card->setPixmap(QPixmap("://res/img/frame/fight/now_use_card.png"));
	if(now_use_d == 1) {
		fight_now_use_card->setPos(140, 600);
	} else if (now_use_d == 2) {
		fight_now_use_card->setPos(460, 600);
	} else if(now_use_d == 3) {
		fight_now_use_card->setPos(780, 600);
	}
	scene->addItem(fight_now_use_card);


	// fight_paper_card_text
	fight_paper_card_text = new QGraphicsTextItem();
	fight_paper_card_text->setPos(340, 670);
	fight_paper_card_text->setDefaultTextColor(Qt::black);
	fight_paper_card_text->setFont(QFont("Microsoft JhengHei", 20));
	fight_paper_card_text->setPlainText(QString::number(player->bag->get_item_num(6)));
	scene->addItem(fight_paper_card_text);

	// fight_paper_card_text
	fight_scissor_card_text = new QGraphicsTextItem();
	fight_scissor_card_text->setPos(660, 670);
	fight_scissor_card_text->setDefaultTextColor(Qt::black);
	fight_scissor_card_text->setFont(QFont("Microsoft JhengHei", 20));
	fight_scissor_card_text->setPlainText(QString::number(player->bag->get_item_num(7)));
	scene->addItem(fight_scissor_card_text);

	// fight_paper_card_text
	fight_stone_card_text = new QGraphicsTextItem();
	fight_stone_card_text->setPos(980, 670);
	fight_stone_card_text->setDefaultTextColor(Qt::black);
	fight_stone_card_text->setFont(QFont("Microsoft JhengHei", 20));
	fight_stone_card_text->setPlainText(QString::number(player->bag->get_item_num(8)));
	scene->addItem(fight_stone_card_text);

}

void Map::close_fight()
{
	if(player->action->get_status() == 8) {
		if(!player->action->change_status(0)) {
			qDebug()<<"map::fight to play change status error!";
		}
		scene->removeItem(fight_bgm);
		scene->removeItem(fight_exit);
		scene->removeItem(fight_people);
		scene->removeItem(fight_animal);
		scene->removeItem(fight_text);
		scene->removeItem(fight_now_use_card);
		scene->removeItem(fight_paper_card_text);
		scene->removeItem(fight_scissor_card_text);
		scene->removeItem(fight_stone_card_text);
		delete fight_bgm;
		delete fight_exit;
		delete fight_people;
		delete fight_animal;
		delete fight_text;
		delete fight_now_use_card;
		delete fight_paper_card_text;
		delete fight_scissor_card_text;
		delete fight_stone_card_text;
		if(fight_result == 0) {
			scene->removeItem(fight_sword);
			delete fight_sword;
		} else {
			scene->removeItem(fight_card_people_bgm);
			scene->removeItem(fight_card_animal_bgm);
			scene->removeItem(fight_card_people);
			scene->removeItem(fight_card_animal);
			delete fight_card_people_bgm;
			delete fight_card_animal_bgm;
			delete fight_card_people;
			delete fight_card_animal;
		}
		now_use_d = 0;
		update_map(player->action->get_x_axis(), player->action->get_y_axis(), player->action->get_direction());
	}
}

int Map::get_fight_result()
{
	return fight_result;
}

void Map::open_bag(int select, int use)
{
	bag_select = select;
	qDebug()<<bag_select;
	if(player->action->get_status() != 9) {
		if(!player->action->change_status(9)) {
			qDebug()<<"map::bag change status error!";
		}
	} else {
		scene->removeItem(bag_bgm);
		scene->removeItem(bag_exit);
		scene->removeItem(bag_selected);
		delete bag_bgm;
		delete bag_exit;
		delete bag_selected;
		const vector<bags> bag = *player->bag->get_items();
		for(int i=0; i<bag.size()+use; i++) {
			scene->removeItem(bag_items[i]);
			scene->removeItem(bag_items_text[i]);
			delete bag_items[i];
			delete bag_items_text[i];
		}
	}

	// bgm
	bag_bgm= new QGraphicsPixmapItem();
	bag_bgm->setPixmap(QPixmap("://res/img/frame/bag/bags_bgm.png"));
	bag_bgm->setPos(0, 0);
	scene->addItem(bag_bgm);

	// exit btn
	bag_exit= new QGraphicsPixmapItem();
	bag_exit->setPixmap(QPixmap("://res/img/frame/exit/exit_60.png"));
	bag_exit->setPos(1090, 10);
	scene->addItem(bag_exit);

	// bag_selected
	bag_selected= new QGraphicsPixmapItem();
	bag_selected->setPixmap(QPixmap("://res/img/frame/bag/bag_selected.png"));
	if(bag_select == 0) {
		bag_selected->setPos(12, 133);
	} else if(bag_select == 1) {
		bag_selected->setPos(252, 133);
	}
	else if(bag_select == 2) {
		bag_selected->setPos(493, 133);
	}else if(bag_select == 3) {
		bag_selected->setPos(733, 133);
	}else if(bag_select == 4) {
		bag_selected->setPos(973, 133);
	}else if(bag_select == 5) {
		bag_selected->setPos(12, 373);
	}else if(bag_select == 6) {
		bag_selected->setPos(252, 373);
	}else if(bag_select == 7) {
		bag_selected->setPos(493, 373);
	}else if(bag_select == 8) {
		bag_selected->setPos(733, 373);
	}else if(bag_select == 9) {
		bag_selected->setPos(973, 373);
	}
	scene->addItem(bag_selected);

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


void Map::close_bag()
{
	//scene->removeItem(bag_exit);
	//delete bag_exit;
	qDebug()<<"close bag";

	scene->removeItem(bag_bgm);
	scene->removeItem(bag_exit);
	scene->removeItem(bag_selected);
	delete bag_bgm;
	delete bag_exit;
	delete bag_selected;
	const vector<bags> bag = *player->bag->get_items();
	for(int i=0; i<bag.size(); i++) {
		scene->removeItem(bag_items[i]);
		scene->removeItem(bag_items_text[i]);
		delete bag_items[i];
		delete bag_items_text[i];
	}
	player->action->change_status(0);
	update_map(player->action->get_x_axis(), player->action->get_y_axis(), player->action->get_direction());
}

int Map::get_bag_select()
{
	return bag_select;
}

int Map::get_local_item()
{
	return local_item;
}

bool Map::remove_pick_item(int player_x, int player_y, int player_di)
{
	if(map_items[player_x+7][player_y+2].item== 3) {
		generate_grass();
	} else if(map_items[player_x+7][player_y+2].item== 9) {
		generate_wood();
	} else if(map_items[player_x+7][player_y+2].item== 10) {
		generate_stone();
	} else if(map_items[player_x+7][player_y+2].item== 8) {
		generate_animal();
	}
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

bool Map::initialize_items(int x, int y)
{
	for(int i=0; i<16; i++) {
		for(int j=0; j<9; j++) {
			map_now[i][j]= new QGraphicsPixmapItem();
			map_now[i][j]->setPixmap(QPixmap(map_items[i+x][j+y].img));
			map_now[i][j]->setPos(i*80, 640-j*80);
			scene->addItem(map_now[i][j]);
		}
	}
}

bool Map::create_items(QJsonObject json)
{
	if(json["type"] == "save") {
		QJsonObject player_save = json["player"].toObject();
		player->energy->set_energy(player_save["energy"].toInt());
		player->blood->set_blood(player_save["blood"].toInt());
		player->action->set_x_axis(player_save["x_axis"].toInt());
		player->action->set_y_axis(player_save["y_axis"].toInt());
		player->action->set_direction(player_save["direction"].toInt());
		player->action->change_reverse(player_save["reverse"].toBool());
		player->action->set_play_time(player_save["time"].toInt());
		player->action->set_invincible_time(player_save["invincible"].toInt());
		player->action->change_status(player_save["status"].toInt());

		QJsonArray bag_save = json["bag"].toArray();
		for(int i=0; i<bag_save.size(); i++) {
			QJsonObject bag_item_save = bag_save[i].toObject();
			for(int j=0; j<bag_item_save["quantity"].toInt(); j++) {
				player->bag->put(bag_item_save["item"].toInt());
			}
		}
		qDebug()<<"read save ("<<player->action->get_x_axis()<<","<<player->action->get_y_axis()<<")";
	} else {
		qDebug()<<"no save";
	}
	QJsonObject map_size = json["size"].toObject();
	size_height = map_size["height"].toInt() + 8;
	size_width = map_size["width"].toInt() + 15;
	home_size_height = json["home"].toObject()["height"].toInt();
	home_size_width = json["home"].toObject()["width"].toInt();
	qDebug()<<home_size_width<<home_size_height;
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

int Map::get_home_size_height()
{
	return home_size_height;
}

int Map::get_home_size_width()
{
	return home_size_width;
}

int Map::show_energy_blood(bool ini, int energy_v, int blood_v, QString avatar_v)
{
	if(!ini) {
		scene->removeItem(frame);
		scene->removeItem(blood);
		scene->removeItem(blood_t);
		scene->removeItem(energy);
		scene->removeItem(energy_t);
		scene->removeItem(avatar);
		delete frame;
		delete blood;
		delete blood_t;
		delete energy;
		delete energy_t;
		delete avatar;
		qDebug()<<"debug 2";
		if(show_purple_time) {
			qDebug()<<"debug 3";
			scene->removeItem(purple_time);
			scene->removeItem(purple_time_t);
			delete purple_time;
			delete  purple_time_t;
		}
	}
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

	qDebug()<<"debug 4";
	if(gamewindow->get_invincible_time() > 1) {
		qDebug()<<"debug 55";
		purple_time = new QGraphicsPixmapItem();
		purple_time->setPixmap(QPixmap("://res/img/bag/grass_purple_54.png"));
		purple_time->setPos(475, 80);
		scene->addItem(purple_time);

		purple_time_t = new QGraphicsTextItem();
		purple_time_t->setDefaultTextColor(Qt::black);
		purple_time_t->setFont(QFont("Microsoft JhengHei", 12));
		if(gamewindow->get_invincible_time() < 10) {
			purple_time_t->setPos(492, 98);
		} else if(gamewindow->get_invincible_time() < 100) {
			purple_time_t->setPos(488, 98);
		} else {
			purple_time_t->setPos(484, 98);
		}
		purple_time_t->setPlainText(QString::number(gamewindow->get_invincible_time()));
		scene->addItem(purple_time_t);
		show_purple_time = true;
		qDebug()<<"debug 5";
	} else if(gamewindow->get_invincible_time() == 1) {
		qDebug()<<"debug 66";
		show_purple_time = false;
		qDebug()<<"debug 6";
	}
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
