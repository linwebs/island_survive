#include "player.h"
#include "gamewindow.h"
#include <QGraphicsScene>

Player::Player(GameWindow *g, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
	blood = new Blood;
	energy = new Energy;
	action = new Action;
	bag = new Bag;
	gamewindow = g;
	action->set_energy(energy);
	action->set_blood(blood);
	action->set_bag(bag);
	action->set_player(this);
	action->set_gamewindow(gamewindow);
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
	energy->set_map(map);
	blood->set_map(map);
}
