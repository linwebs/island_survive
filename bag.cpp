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
	bag = ibag;
}

bool Bag::put(int name)
{
	if(get_item_num(name) == 0) {		// 檢查要新增的物品是否已在背包中
		// 要新增的物品不在背包中
		if(item_full() == false) {	// 檢查背包格數是否已滿
			bags blanck;
			blanck.item = name;
			blanck.quantity = 1;
			bag.push_back(blanck);
			return true;
		} else {
			// 背包格數已滿，無法新增
			return false;
		}
	} else {
		if(quantity_full(name) == false) {	// 檢查背包此物品空間是否已滿
			bag[get_item_order(name)].quantity++;
			return true;
		} else {
			// 背包此物品空間已滿，無法新增
			return false;
		}
	}
}

bool Bag::take(int name)
{
	if(get_item_num(name) == 0) {		// 檢查要取出的物品是否有在背包中
		// 背包中無此物品，無法取出
		return false;
	} else if(get_item_num(name) == 1) {
		bag.erase(bag.begin() + get_item_order(name));
		return true;
	} else {
		bag[get_item_order(name)].quantity--;
		return true;
	}
}

int Bag::bag_size()
{
	return bag.size();
}

vector<bags> *Bag::get_items()
{
	return &bag;
}

bool Bag::item_full()
{
	if(bag.size() >= 10) {
		return true;
	} else {
		return false;
	}
}

bool Bag::quantity_full(int name)
{
	if(bag[get_item_order(name)].quantity >= 10) {
		return true;
	} else {
		return false;
	}
}

int Bag::get_item_num(int name)
{
	for(int i=0; i<bag.size(); i++)
	{
		if(bag[i].item == name)
		{
			return bag[i].quantity;
		}
	}
	return 0;
}

int Bag::get_order_item(int order)
{
	if(order >= bag.size()) {
		return 0;
	} else {
		return bag[order].item;
	}
}

int Bag::get_item_order(int name)
{
	for(int i=0; i<bag.size(); i++)
	{
		if(bag[i].item == name)
		{
			return i;
		}
	}
	return -1;
}

