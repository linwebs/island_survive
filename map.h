#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QLabel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QJsonObject>
#include "struct.cpp"
#include "gamewindow.h"
#include "gamewindowscene.h"
#include <vector>
using namespace std;

class Player;
/* 地圖 */
class Map : public QGraphicsView
{
	public:
		Map(GameWindowScene *GWscene);
		Map(vector<maps>);	// 帶入存檔(map)
		bool update_map(int&, int&, int&);
		bool set_player(Player*);
		bool create_items(QJsonObject);	// 從 map.json 取得地圖上物品
		int get_size_height();
		int get_size_width();
		int show_energy_blood();

	private:
		bool create_land();		// 生成土地
		bool barrier(int);	// 障礙物
		bool prey(int);		// 獵物
		bool stone(int);	// 礦物
		bool wood(int);		// 木頭
		bool grass(int);	// 草
		bool stove(int);	// 煉丹爐
		bool furnace(int);	// 熔爐
		bool bbq(int);		// 篝火
		bool home(int);		// 房子
		bool land(int);		// 土地
		bool initialize_items();
		bool put_items(int, int, int);
		bool generate_player(bool);

		vector<maps> map;	// 地圖組成項目列表
		GameWindowScene *scene;
		QGraphicsPixmapItem *player_show;
		QGraphicsPixmapItem *background[16][9];
		QGraphicsPixmapItem *map_now[16][9];
		vector<vector<map_item>> map_items;
		int size_height;
		int size_width;
};


#endif // MAP_H
