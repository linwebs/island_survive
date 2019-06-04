#include "blood.h"

Blood::Blood()
{
	bloods = 100;
}

Blood::Blood(int b)
{
	bloods = b;
}

bool Blood::grass(int m)
{
	if(m==2)
		return add(5);
	else if(m==3)
		return sub(2);
}

bool Blood::fail()
{
	return sub(10);
}

bool Blood::die()
{
	if(bloods<=0) {
		return true;
	} else {
		return false;
	}
}

int Blood::get_blood()
{
	return bloods;
}

bool Blood::add(int b)
{
	if(bloods+b>100)
		return false;
	else
	{
		bloods+=b;
		return true;
	}
}

bool Blood::sub(int b) {
	 if(bloods-b<=0)
		return false;
	 else
	 {
		bloods-=b;
		return true;
	 }
}
