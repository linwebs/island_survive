#include "map.h"
#include "gamewindowscene.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QDebug>

Map::Map(GameWindowScene *GWscene)
{
	scene = GWscene;
	map.clear();

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);

	create();

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

bool Map::update_map()
{
	qDebug()<<"update_map";
	int i=10, j=3;
	grasses[i][j] = new QGraphicsPixmapItem();
	grasses[i][j]->setPixmap(QPixmap("://res/img/land/grass_80.png"));
	grasses[i][j]->setPos(i*80, j*80);
	scene->addItem(grasses[i][j]);
	scene->removeItem(grasses[10][4]);
	//	delete grasses[10][4];
}

bool Map::grass(int)
{
	int i=10, j=4;
	grasses[i][j] = new QGraphicsPixmapItem();
	grasses[i][j]->setPixmap(QPixmap("://res/img/land/grass_80.png"));
	grasses[i][j]->setPos(i*80, j*80);
	scene->addItem(grasses[i][j]);
}
