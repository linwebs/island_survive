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
		Map(GameWindowScene *GWscene, int *, Player *);
		Map(GameWindowScene *GWscene, int *, Player *, QString);						// 帶入存檔(map)
		bool update_map(int&, int&, int&);
		bool set_player(Player*);
		bool create_items(QJsonObject);		// 從 map.json 取得地圖上物品
		int get_size_height();
		int get_size_width();
		int get_home_size_height();
		int get_home_size_width();
		int show_energy_blood(int, int, QString avatar_v = "://res/img/character/people_avatar_130.png");
		void show_bags();						// 顯示小背包
		bool exit_pause();						// 離開暫停遊戲畫面
		void pause_game();						// 遊戲暫停畫面
		int get_local_item();					// 取得當前位置的物品
		bool remove_pick_item(int, int, int);	// 移除當前位置的物品
		void open_bag(int, int);						// 背包
		void close_bag();
		int get_bag_select();
		void open_bbq();						// 篝火
		void close_bbq();
		void open_stove();						// 煉丹爐
		void close_stove();
		void open_furnace(int, int);			// 熔爐
		void close_furnace();
		int get_now_use_d();					// 取得熔爐目前配方
		void show_die();						// 死亡畫面
		void open_fight(int, int, int);		// 戰鬥
		void close_fight();
		int get_fight_result();
		bool generate_grass();					// 生成草
		bool generate_animal();				// 生成獵物
		bool generate_stone();					// 生成礦物
		bool generate_wood();					// 生成木頭
		vector<vector<map_item> > *get_map_items();	// 取得背包中的物品

	private:
		bool create_land();					// 生成土地
		bool initialize_items(int, int);
		bool items_event();
		bool generate_player(bool);
		bool save_file();

		vector<maps> map;						// 地圖組成項目列表
		GameWindowScene *scene;
		Player *player;

		// save
		QGraphicsRectItem *save_bgm;
		QGraphicsPixmapItem *pause_text;

		// bags
		QGraphicsPixmapItem *bags_bgm;
		QGraphicsTextItem *bags_items_text[10];
		QGraphicsPixmapItem *bags_items[10];

		// bag big
		QGraphicsPixmapItem *bag_bgm;
		QGraphicsPixmapItem *bag_exit;
		QGraphicsPixmapItem *bag_selected;
		QGraphicsTextItem *bag_items_text[10];
		QGraphicsPixmapItem *bag_items[10];
		int bag_select;

		// bbq
		QGraphicsPixmapItem *bbq_bgm;
		QGraphicsPixmapItem *bbq_exit;
		QGraphicsTextItem *bbq_flesh_text;
		QGraphicsTextItem *bbq_meat_text;

		// stove
		QGraphicsPixmapItem *stove_bgm;
		QGraphicsPixmapItem *stove_exit;
		QGraphicsTextItem *red_grass_text;
		QGraphicsTextItem *blue_grass_text;
		QGraphicsTextItem *purple_grass_text;

		// furnace
		QGraphicsPixmapItem *furnace_bgm;
		QGraphicsPixmapItem *furnace_exit;
		QGraphicsPixmapItem *result_item;
		QGraphicsPixmapItem *now_use;
		QGraphicsTextItem *wood_text;
		QGraphicsTextItem *stone_text;
		QGraphicsTextItem *result_text;
		QGraphicsTextItem *paper_card_text;
		QGraphicsTextItem *scissor_card_text;
		QGraphicsTextItem *stone_card_text;
		int now_use_d;

		// hint
		QGraphicsPixmapItem *hint_text;

		// die
		QGraphicsPixmapItem *die_bgm;
		QGraphicsPixmapItem *die_exit;
		QGraphicsTextItem *survive_time;

		// fight
		QGraphicsPixmapItem *fight_bgm;
		QGraphicsPixmapItem *fight_exit;
		QGraphicsPixmapItem *fight_people;
		QGraphicsPixmapItem *fight_animal;
		QGraphicsPixmapItem *fight_card_people_bgm;
		QGraphicsPixmapItem *fight_card_animal_bgm;
		QGraphicsPixmapItem *fight_card_people;
		QGraphicsPixmapItem *fight_card_animal;
		QGraphicsPixmapItem *fight_text;
		QGraphicsPixmapItem *fight_now_use_card;
		QGraphicsPixmapItem *fight_sword;
		QGraphicsTextItem *fight_paper_card_text;
		QGraphicsTextItem *fight_scissor_card_text;
		QGraphicsTextItem *fight_stone_card_text;
		int fight_result;

		QGraphicsPixmapItem *player_show;
		QGraphicsPixmapItem *background[16][9];
		QGraphicsPixmapItem *map_now[16][9];
		QGraphicsTextItem *pause_time;
		vector<vector<map_item>> map_items;
		int size_height;
		int size_width;
		int home_size_height;
		int home_size_width;
		int *play_time;
		int local_item;
		int last_local_item;

};


#endif // MAP_H
