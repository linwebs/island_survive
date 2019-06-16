#include "energy.h"
#include "map.h"
#include <QDebug>

Energy::Energy()
{
	energy = 100;
}

Energy::Energy(int e)
{
	energy = e;
}

bool Energy::sub_time()
{
	return sub(1);
	//	qDebug()<<energy;
}

bool Energy::attack()
{
	return sub(3);
}

bool Energy::pick()
{
	return sub(2);
}

bool Energy::eat(int n)
{
	if(n==9) {
		return sub(5);
	} else if(n==10) {
		return add(20);
	}
}

bool Energy::die()
{
	if(energy<=0) {
		map->show_die();
		return true;
	} else {
		return false;
	}
}

int Energy::get_energy()
{
	return energy;
}

bool Energy::add(int e)
{
	if(energy == 100) {
		return false;
	} else {
		energy+=e;
		if(energy > 100) {
			energy = 100;
		}
		return true;
	}
}

bool Energy::sub(int e) {
	energy -= e;
	if(energy <= 0) {
		energy = 0;
		return !die();
	} else {
		return true;
	}
}

void Energy::set_map(Map *m)
{
	map = m;
}
