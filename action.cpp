#include <QKeyEvent>
#include <QDebug>
#include "action.h"
#include "map.h"
Action::Action()
{
	direction = 1;
	setPixmap(QPixmap("://res/img/character/people.png"));
}

Action::Action(int n)
{
	direction = n;
}

bool Action::move(int n) {
	int step = 100;
	qDebug()<<"move";
	if (n==2) {
		return go_down(step);
	} else if (n==3) {
		return go_left(step);
	} else if (n==4) {
		return go_right(step);
	} else {
		return go_up(step);
	}
}
/*
void Action::keyPressEvent(QKeyEvent *event) {
	qDebug()<<"key press";
	if(event->key() == Qt::Key_Up) {
		qDebug()<<"up";
		move(1);
	} else if(event->key() == Qt::Key_Down) {
		qDebug()<<"down";
		move(2);
	} else if(event->key() == Qt::Key_Left) {
		qDebug()<<"left";
		move(4);
	} else if(event->key() == Qt::Key_Right) {
		qDebug()<<"right";
		move(3);
	}
}
*/
bool Action::go_up(int step) {
	if((y()+step) <= 900)
		setPos(x(), y()+step);
	return true;
}

bool Action::go_down(int step) {
	qDebug()<<"down lo ki";
	map->update_map();
	return true;
}

bool Action::go_left(int step) {
	if((x()-step) >= 0)
		setPos(x()-step, y());
	return true;
}

bool Action::go_right(int step) {
	if((x()+step) <= 1500)
		setPos(x()+step, y());
	return true;
}

void Action::setMap(Map *m)
{
	map = m;
}

