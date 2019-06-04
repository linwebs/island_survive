#include "energy.h"
#include <QDebug>

Energy::Energy()
{
	energy=100;
}

Energy::Energy(int e)
{
	energy=e;
}

void Energy::sub_time()
{
	energy=energy-1;
	qDebug()<<energy;
}

bool Energy::attack()
{
	return sub(3);
}

bool Energy::pick()
{
	return sub(4);
}

bool Energy::eat()
{
	return add(10);
}

bool Energy::die()
{
	if(energy<=0) {
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
	if(energy+e>100)
		return false;
	else
	{
		energy=energy+e;
		return true;
	}
}

bool Energy::sub(int e) {
	if(energy-e<=0) {
		return false;
		// return die();
	} else {
		energy=energy-e;
		return true;
	}
}
