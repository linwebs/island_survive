#include <QKeyEvent>
#include <QDebug>
#include <qrandom.h>
#include "action.h"
#include "map.h"
#include "bag.h"
#include "energy.h"
Action::Action()
{
	reverse = false;
	x_axis = 7;
	y_axis = 2;
	direction = 1;
	pause = 0;
	status = 0;
	setPixmap(QPixmap("://res/img/character/people.png"));
}

Action::Action(int n)
{
	direction = n;
}

bool Action::move(int n) {
	int step = 100;
	//	qDebug()<<"move";
	if(pause==0 || pause==2) {
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
}

bool Action::pick()
{
	qDebug()<<"pick grass";
	if(qrand()%2 == 1) {
		if(bag->put(1)) {
			map->remove_pick_item(x_axis, y_axis, direction);

			qDebug()<<"put_1";
		}
	} else {
		if(bag->put(2)) {
			map->remove_pick_item(x_axis, y_axis, direction);
			qDebug()<<"put_2";
		}
	}
}

bool Action::bbq()
{
	if(bag->get_item_num(9)) {
		bag->take(9);
		bag->put(10);
		map->open_bbq();
	}
}

bool Action::go_up(int step) {
	//qDebug()<<map->get_size_height();
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

void Action::set_map(Map *m)
{
	map = m;
}

void Action::set_energy(Energy *e)
{
	energy = e;
}

void Action::set_bag(Bag *b)
{
	bag = b;
}

int Action::get_x_axis()
{
	return x_axis;
}

int Action::get_y_axis()
{
	return y_axis;
}

bool Action::energy_update()
{
	energy->sub_time();
}

bool Action::change_status(int s)
{
	switch (s) {
		case 0:
			status = 0;
			pause = 0;
			return true;
		case 1:
			status = 1;
			pause = 1;
			return true;
		case 2:
			status = 2;
			return true;
		case 3:
			status = 3;
			pause = 1;	// 存檔中
			return true;
		case 4:
			status = 4;
			return true;
		case 5:
			status = 5;
			return true;
		case 6:
			status = 6;
			pause = 1;
			return true;
		case 7:
			status = 7;
            return true;
        case 8:
            status = 8;
            return true;
        case 9:
            pause = 1;
            status = 9;
            return true;
		default:
			return false;
	}
}

int Action::get_status()
{
	return status;
}

int Action::get_pause()
{
	return pause;
}
