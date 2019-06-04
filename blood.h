#ifndef BLOOD_H
#define BLOOD_H

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

	private:
		bool add(int);		// 增加血量(數值)
		bool sub(int);		// 減少血量(數值)
		int bloods;			// 血量
};

#endif // BLOOD_H
