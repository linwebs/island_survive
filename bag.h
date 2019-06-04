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
		vector<bags> *get_items();	// 取得背包中的物品
		bool full(int);				// 判斷背包物品是否已滿

	private:
		int checkbag(int);			// 檢查物品是否在背包中(item_id)
		vector<bags> bag;			// 背包列表
};

#endif // BAG_H
