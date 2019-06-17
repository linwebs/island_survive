#include <QKeyEvent>
#include <QDebug>
#include <QTime>
#include "struct.cpp"
#include "action.h"
#include "map.h"
#include "bag.h"
#include "energy.h"
#include "blood.h"
#include "gamewindow.h"
#include "system.h"
#include "player.h"
Action::Action()
{
	reverse = false;
	x_axis = 4;
	y_axis = 0;
	direction = 1;
	pause = 0;
	status = 0;
	system = new System;
	setPixmap(QPixmap("://res/img/character/people.png"));
}

bool Action::move(int n) {
	int step = 100;
	//	qDebug()<<"move";
	if(status==0 || status==2) {
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

bool Action::pick(int item)
{
	qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
	if(item == 3) {
		qDebug()<<"pick grass";
		if(qrand()%2 == 1) {
			if(bag->put(1)) {
				if(energy->pick()) {
					map->remove_pick_item(x_axis, y_axis, direction);
				} else {
					change_status(4);
				}
				qDebug()<<"put_1";
				return true;
			} else {
				// bag item 1 full
				return false;
			}
		} else {
			if(bag->put(2)) {
				if(energy->pick()) {
					map->remove_pick_item(x_axis, y_axis, direction);
				} else {
					change_status(4);
				}
				qDebug()<<"put_2";
				return true;
			} else {
				// bag item 2 full
				return false;
			}
		}
	} else if(item == 9) {
		qDebug()<<"pick wood";
		if(bag->put(4)) {
			if(energy->pick()) {
				map->remove_pick_item(x_axis, y_axis, direction);
			} else {
				change_status(4);
			}
			return true;
		} else {
			// bag item 4 full
			return false;
		}
	} else if(item == 10) {
		qDebug()<<"pick stone";
		if(bag->put(5)) {
			if(energy->pick()) {
				map->remove_pick_item(x_axis, y_axis, direction);
			} else {
				change_status(4);
			}
			return true;
		} else {
			// bag item 5 full
			return false;
		}
	}
}

bool Action::attack()
{
	if(map->get_now_use_d() == 1 && bag->get_item_num(6)) {
		bag->take(6);
	} else if (map->get_now_use_d() == 2 && bag->get_item_num(7)) {
		bag->take(7);
	}  else if (map->get_now_use_d() == 3 && bag->get_item_num(8)) {
		bag->take(8);
	} else {
		return false;
	}
	qsrand(static_cast<unsigned int>(QTime::currentTime().msecsSinceStartOfDay()));
	int result = qrand()%3;
	if(result == 0) {
		result = 3;
	}

	map->open_fight(map->get_now_use_d(), 0, result);
	return true;
}

bool Action::exit_attack(int result)
{
	energy->attack();
	if(map->get_now_use_d() == 1 && result == 2) {
		blood->fail();
		qDebug()<<"fail";
		//return false;
	} else if(map->get_now_use_d() == 1 && result == 3) {
		bag->put(9);
		map->remove_pick_item(x_axis, y_axis, direction);
	} else if(map->get_now_use_d() == 2 && result == 1) {
		bag->put(9);
		map->remove_pick_item(x_axis, y_axis, direction);
	} else if(map->get_now_use_d() == 2 && result == 3) {
		blood->fail();
		qDebug()<<"fail";
		//return false;
	} else if(map->get_now_use_d() == 3 && result == 1) {
		blood->fail();
		qDebug()<<"fail";
		//return false;
	} else if(map->get_now_use_d() == 3 && result == 2) {
		bag->put(9);
		map->remove_pick_item(x_axis, y_axis, direction);
	}
	return true;
}

bool Action::furnace(int result)
{
	if(result == 1) {
		if(bag->get_item_num(4) >= WEAPON_SCISSOR_WOOD && bag->get_item_num(5) >= WEAPON_SCISSOR_STONE) {
			for(int i=0; i<WEAPON_SCISSOR_WOOD; i++) {
				bag->take(4);
			}
			for(int i=0; i<WEAPON_SCISSOR_STONE; i++) {
				bag->take(5);
			}
			if(bag->put(6)) {
				map->open_furnace(1, 0);
				return true;
			} else {
				return false;
			}
		}
	} else if(result == 2) {
		if(bag->get_item_num(4) >= WEAPON_STONE_WOOD && bag->get_item_num(5) >= WEAPON_STONE_STONE) {
			for(int i=0; i<WEAPON_STONE_WOOD; i++) {
				bag->take(4);
			}
			for(int i=0; i<WEAPON_STONE_STONE; i++) {
				bag->take(5);
			}
			if(bag->put(7)) {
				map->open_furnace(2, 0);
				return true;
			} else {
				return false;
			}
		}
	} else if(result == 3) {
		if(bag->get_item_num(4) >= WEAPON_PAPER_WOOD && bag->get_item_num(5) >= WEAPON_PAPER_STONE) {
			for(int i=0; i<WEAPON_PAPER_WOOD; i++) {
				bag->take(4);
			}
			for(int i=0; i<WEAPON_PAPER_STONE; i++) {
				bag->take(5);
			}
			if(bag->put(8)) {
				map->open_furnace(3, 0);
				return true;
			} else {
				return false;
			}
		}
	}
}

bool Action::bbq()
{
	if(bag->get_item_num(9)) {
		bag->take(9);
		bag->put(10);
		map->open_bbq();
		return true;
	} else {
		return false;
	}
}


bool Action::stove()
{
	if(bag->get_item_num(1) && bag->get_item_num(2)) {
		bag->take(1);
		bag->take(2);
		bag->put(3);
		map->open_stove();
		return true;
	} else {
		return false;
	}
}

bool Action::use_item()
{
	qDebug()<<bag->get_order_item(map->get_bag_select());
	switch (bag->get_order_item(map->get_bag_select())) {
		case 1:
			// grass blue
			blood->grass(1);
			bag->take(1);
			map->open_bag(map->get_bag_select(), !bag->get_item_num(1));
			break;
		case 2:
			// grass red
			blood->grass(2);
			bag->take(2);
			map->open_bag(map->get_bag_select(), !bag->get_item_num(2));
			break;
		case 3:
			// grass purple
			qDebug()<<"efudo";
			gamewindow->set_invincible_time(30);
			bag->take(3);
			map->open_bag(map->get_bag_select(), !bag->get_item_num(3));
			reverse = true;
			break;
		case 4:
			// wood
			break;
		case 5:
			// stone
			break;
		case 6:
			// weapon scissor
			break;
		case 7:
			// weapon stone
			break;
		case 8:
			// weapon paper
			break;
		case 9:
			// flesh
			energy->eat(9);
			bag->take(9);
			map->open_bag(map->get_bag_select(), !bag->get_item_num(9));
			break;
		case 10:
			// meat
			energy->eat(10);
			bag->take(10);
			map->open_bag(map->get_bag_select(), !bag->get_item_num(10));
			break;
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
	qDebug()<<"dyiscuhxjk"<<y_axis<<x_axis;
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

void Action::set_blood(Blood *b)
{
	blood = b;
}

void Action::set_gamewindow(GameWindow * g)
{
	gamewindow = g;
}

void Action::set_bag(Bag *b)
{
	bag = b;
}

void Action::set_player(Player *p)
{
	player = p;
}

bool Action::set_x_axis(int x)
{
	x_axis = x;
}

bool Action::set_y_axis(int y)
{
	y_axis = y;
}

bool Action::set_direction(int d)
{
	direction = d;
}

int &Action::get_x_axis()
{
	return x_axis;
}

int &Action::get_y_axis()
{
	return y_axis;
}

int &Action::get_direction()
{
	return direction;
}

bool Action::energy_update()
{
	return energy->sub_time();
}

bool Action::change_status(int s)
{
	int last_status = status;
	switch (s) {
		case 0:
			status = 0;
			pause = 0;
			return true;
		case 1:
			// pause
			status = 1;
			pause = 1;
			return true;
		case 2:
			// invincible mode
			status = 2;
			pause = 1;
			return true;
		case 3:
			// save file
			system->save(player, map, last_status);
			status = 3;
			pause = 1;
			return true;
		case 4:
			// game over
			status = 4;
			pause = 1;
			return true;
		case 5:
			// furnace
			status = 5;
			pause = 1;
			return true;
		case 6:
			// bbq
			status = 6;
			pause = 1;
			return true;
		case 7:
			// stove
			status = 7;
			pause = 1;
			return true;
		case 8:
			// fight
			status = 8;
			pause = 1;
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

bool Action::get_reverse()
{
	return reverse;
}

void Action::change_reverse(bool r)
{
	reverse = r;
}
