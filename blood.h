#ifndef BLOOD_H
#define BLOOD_H

class Map;
/* 血量 */
class Blood
{
	public:
		Blood();
		Blood(int);			// 帶入存檔(blood)
		bool grass(int);	// 使用草藥(item_id)
		bool fail();		// 戰鬥失敗
		bool die();			// 死亡判定
		int get_blood();	// 取得血量
		void set_blood(int);	// 設定血量
		void set_map(Map*);		// 設定Map以顯示死亡畫面

	private:
		bool add(int);		// 增加血量(數值)
		bool sub(int);		// 減少血量(數值)
		int bloods;			// 血量
		Map *map;
};

#endif // BLOOD_H
