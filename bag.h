#ifndef BAG_H
#define BAG_H
#include <vector>
#include "struct.cpp"
using namespace std;

/* 背包 */
class Bag
{
	public:
		Bag();
		Bag(vector<bags>);			// 帶入存檔(背包列表)
		bool put(int);				// 放入物品(item_id)
		bool take(int);				// 拿出物品(item_id)
		int bag_size();				// 取得當前背包使用格數
		vector<bags> *get_items();	// 取得背包中的物品

	private:
		int checkbag(int);			// 檢查物品是否在背包中(item_id)
		bool item_full();			// 判斷背包格數是否已滿
		bool quantity_full(int);	// 判斷背包單一物品數量是否已滿
		int get_item_order(int);	// 取得物品在背包中的順序
		vector<bags> bag;			// 背包列表
};

#endif // BAG_H
