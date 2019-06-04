#include <iostream>
#include <algorithm>
#include "struct.cpp"
#include "bag.h"

Bag::Bag()
{
	bag.clear();
}

Bag::Bag(vector<bags> ibag)
{
	bag=ibag;
}

bool Bag::put(int name)
{
	if(checkbag(name)==-1)
	{
		bags blanck;
		blanck.item=name;
		blanck.quantity=1;
		bag.push_back(blanck);
	}
}

bool Bag::take(int name)
{
	int ch=0;
	for(int i=0; i<bag.size(); i++)
	{
		if(name==bag[i].item)
		{
			bag[i].quantity--;
			ch=1;
			if(bag[i].quantity==0)
			{
				bag.erase(bag.begin()+i);
			}
		}
	}
	if(ch==1)
	{
		return true;
	}
	else if(ch==0)
	{
		return false;
	}
}

vector<bags> *Bag::get_items()
{
	return &bag;
}

bool Bag::full(int)
{
	if(bag.size()==10)
	{
		return false;
	}
	else if(bag.size()<=10)
	{
		return true;
	}
}

int Bag::checkbag(int name)
{
	int c=1;
	for(int i=0; i<bag.size(); i++)
	{
		if(bag[i].item==name)
		{
			bag[i].quantity++;
			c=0;
		}
	}
	if(c==1)
	{
		return -1;
	}
	else if(c==0)
	{
		return 1;
	}
}
