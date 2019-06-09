#include <QKeyEvent>
#include <QDebug>
#include "action.h"
#include "map.h"
Action::Action()
{
	reverse = false;
	x_axis = 7;
	y_axis = 2;
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
	qDebug()<<map->get_size_height();
	if(reverse) {
		if(y_axis-1 >= 0) {
			y_axis -= 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				y_axis += 1;
			}
		}
	} else {
		if(y_axis+1 < map->get_size_height()-8) {
			y_axis += 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				y_axis -= 1;
			}
		}
	}
	return true;
}

bool Action::go_down(int step) {
	if(reverse) {
		if(y_axis+1 < map->get_size_height()-8) {
			y_axis += 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				y_axis -= 1;
			}
		}
	} else {
		if(y_axis-1 >= 0) {
			y_axis -= 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				y_axis += 1;
			}
		}
	}
	return true;
}

bool Action::go_left(int step) {
	if(reverse) {
		if(x_axis+1 < map->get_size_width()-15) {
			x_axis += 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				x_axis -= 1;
			}
		}
	} else {
		if(x_axis-1 >= 0) {
			x_axis -= 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				x_axis += 1;
			}
		}
	}
	return true;
}

bool Action::go_right(int step) {
	if(reverse) {
		if(x_axis-1 >= 0) {
			x_axis -= 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				x_axis += 1;
			}
		}
	} else {
		if(x_axis+1 < map->get_size_width()-15) {
			x_axis += 1;
			if(map->update_map(x_axis, y_axis, direction) == false) {
				x_axis -= 1;
			}
		}
	}
	return true;
}

void Action::setMap(Map *m)
{
	map = m;
}

int Action::get_x_axis()
{
	return x_axis;
}

int Action::get_y_axis()
{
	return y_axis;
}

