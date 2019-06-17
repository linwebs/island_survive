#include "blood.h"
#include "map.h"

Blood::Blood()
{
	bloods = 100;
}

Blood::Blood(int b)
{
	bloods = b;
}

bool Blood::grass(int n)
{
	if(n==1) {
		return add(5);
	} else if(n==2) {
		return sub(2);
	}
}

bool Blood::fail()
{
	return sub(10);
}

bool Blood::die()
{
	if(bloods<=0) {
		map->show_die();
		return true;
	} else {
		return false;
	}
}

int Blood::get_blood()
{
	return bloods;
}

void Blood::set_blood(int b)
{
	bloods = b;
}

bool Blood::add(int b)
{
	if(bloods == 100) {
		return false;
	} else {
		bloods += b;
		if(bloods > 100) {
			bloods = 100;
		}
		return true;
	}
}

bool Blood::sub(int b) {
	bloods -= b;
	if(bloods <= 0) {
		bloods = 0;
		return !die();
	} else {
		return true;
	}
}

void Blood::set_map(Map *m)
{
	map = m;
}
