#include "map.h"
#include "gamewindowscene.h"
#include "system.h"
#include "player.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

Map::Map(GameWindowScene *GWscene)
{
	scene = GWscene;
	map.clear();

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);
	create();
	create_items(System::get_default_map());

	show();
}

Map::Map(vector<maps> maps)
{
	map = maps;
}

bool Map::create()
{
	for(int i=0; i<16; i++) {
		for(int j=0; j<9; j++) {
			background[i][j] = new QGraphicsPixmapItem();
			background[i][j]->setPixmap(QPixmap("://res/img/land/soil_80.jpg"));
			background[i][j]->setPos(i*80, j*80);
			scene->addItem(background[i][j]);
		}
	}

	grass(0);
}

bool Map::update_map(int &player_x, int &player_y, int &player_di)
{
	qDebug()<<"("<<player_x<<", "<<player_y<<")";
	//for(int i=)
	/*
	qDebug()<<"update_map";
	int i=10, j=3;
	grasses[i][j] = new QGraphicsPixmapItem();
	grasses[i][j]->setPixmap(QPixmap("://res/img/land/grass_80.png"));
	grasses[i][j]->setPos(i*80, j*80);
	scene->addItem(grasses[i][j]);
	scene->removeItem(grasses[10][4]);
	//	delete grasses[10][4];*/

}

bool Map::grass(int)
{
	int i=10, j=4;
	grasses[i][j] = new QGraphicsPixmapItem();
	grasses[i][j]->setPixmap(QPixmap("://res/img/land/grass_80.png"));
	grasses[i][j]->setPos(i*80, j*80);
	scene->addItem(grasses[i][j]);
}

bool Map::furnace(int)
{

}

bool Map::create_items(QJsonObject json)
{
	QJsonObject map_size = json["size"].toObject();
	size_height = map_size["height"].toInt() + 8;
	size_width = map_size["width"].toInt() + 15;
	/*
	 * up: 6 ;  down: 2 ;  right: 7 ;  left: 8
	 * /

	/* Initialize map_items */
	map_item mi;
	mi.item = 0;
	mi.size = 1;
	mi.img  = "";
	vector<map_item> md;
	md.assign(map_size["height"].toInt(), mi);
	map_items.assign(map_size["width"].toInt(), md);

	//qDebug()<<map_items[3][4].img;

	/* put item in to map_items */
	QJsonArray map_item_json = json["items"].toArray();
	int map_x, map_y, map_it, map_si;
	QString map_img;
	for(int i=0; i<map_item_json.size(); i++) {
		map_x = map_item_json[i].toObject()["x_axis"].toInt();
		map_y = map_item_json[i].toObject()["y_axis"].toInt();
		map_it = map_item_json[i].toObject()["item"].toInt();
		map_items[map_x][map_y].item = map_it;
		map_si = map_item_json[i].toObject()["size"].toInt();
		map_items[map_x][map_y].size = map_si;
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
