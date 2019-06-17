#include <string>
#include <QString>
#include <QJsonObject>
using namespace std;
#ifndef SYSTEM_H
#define SYSTEM_H

class Map;
class Player;
/* 系統 */
class System
{
	public:
		System();
		static bool save(Player *, Map *, int);		// 儲存檔案
		bool exit();			// 離開遊戲[返回主畫面]
		int get_save_file(QString []);	// 讀取檔案(name)[開啟遊戲]
		QJsonObject static read_save_file(QString);	// 讀取檔案(name)[開啟遊戲]
		QJsonObject static get_default_map();	// 讀取地圖
		static QString get_bag_item_file_path(int);	// 將背包中物品 ID 轉為檔案路徑 (full)
		static QString get_bags_item_file_path(int);	// 將背包中物品 ID 轉為檔案路徑 (small)

	private:
		string *get_data();	// 取得所有存檔
		string name;			// 檔案名稱
		Player *player;
		Map *map;
};

#endif // SYSTEM_H
