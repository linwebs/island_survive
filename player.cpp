#include "player.h"
#include <QGraphicsScene>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
	blood = new Blood;
	energy = new Energy;
	action = new Action;
	bag = new Bag;

	setPixmap(QPixmap("://res/img/character/people_80.png"));
}

void Player::setMap(Map *m)
{
	map = m;
}
