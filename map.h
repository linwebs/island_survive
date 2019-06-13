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
		Map(GameWindowScene *GWscene, int *);
		Map(vector<maps>);	// 帶入存檔(map)
		bool update_map(int&, int&, int&);
		bool set_player(Player*);
		bool create_items(QJsonObject);	// 從 map.json 取得地圖上物品
		int get_size_height();
		int get_size_width();
		int show_energy_blood(int, int, QString avatar_v = "://res/img/character/people_avatar_130.png");
        void show_bags();
        bool exit_pause();
		void pause_game();
		int get_local_item();
		bool remove_pick_item(int, int, int);
		void open_bag();		// 背包
		void close_bag();
		void open_bbq();		// 篝火
		void close_bbq();

	private:
		bool create_land();		// 生成土地
		bool barrier(int);	// 障礙物
		bool prey(int);		// 獵物
		bool stone(int);	// 礦物
		bool wood(int);		// 木頭
		bool grass(int);	// 草
		bool stove(int);	// 煉丹爐
		bool furnace(int);	// 熔爐
		bool home(int);		// 房子
		bool land(int);		// 土地
		bool initialize_items();
		bool items_event();
		bool generate_player(bool);
		bool save_file();

		vector<maps> map;	// 地圖組成項目列表
		GameWindowScene *scene;
		Player *player;

        // save
		QGraphicsRectItem *save_bgm;
		QGraphicsPixmapItem *pause_text;

        // bags
		QGraphicsPixmapItem *bags_bgm;
		QGraphicsTextItem *bags_items_text[10];
		QGraphicsPixmapItem *bags_items[10];

        // bag
        QGraphicsPixmapItem *bag_bgm;
		QGraphicsTextItem *bag_items_text[10];
		QGraphicsPixmapItem *bag_items[10];

		// bbq
		QGraphicsPixmapItem *bbq_bgm;
		QGraphicsPixmapItem *bbq_exit;
		QGraphicsTextItem *bbq_flesh_text;
		QGraphicsTextItem *bbq_meat_text;

		// hint
		QGraphicsPixmapItem *hint_text;

        QGraphicsPixmapItem *player_show;
		QGraphicsPixmapItem *background[16][9];
		QGraphicsPixmapItem *map_now[16][9];
		QGraphicsTextItem *pause_time;
		vector<vector<map_item>> map_items;
		int size_height;
		int size_width;
		int *play_time;
		int local_item;
		int last_local_item;

};


#endif // MAP_H
