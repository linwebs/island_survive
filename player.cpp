#include "player.h"
#include <QGraphicsScene>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
	blood = new Blood;
	energy = new Energy;
	action = new Action;
	bag = new Bag;

	action->set_energy(energy);
	action->set_bag(bag);
	setPixmap(QPixmap("://res/img/character/people_80.png"));
}

Player::~Player()
{
	delete  blood;
	delete  energy;
	delete  action;
	delete  bag;
}

void Player::set_map(Map *m)
{
	map = m;
}
