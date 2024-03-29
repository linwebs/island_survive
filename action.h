#ifndef ACTION_H
#define ACTION_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Map;
class Energy;
class Blood;
class Bag;
class GameWindow;
class Player;
class System;
/* 行動 */
class Action: public QGraphicsPixmapItem
{
	public:
		Action();
		bool move(int);				// 行走(direction_id)
		bool pick(int);				// 採集資源(item id)
		bool attack();				// 獵殺動物
		bool exit_attack(int);		// 獵殺動物
		bool furnace(int);			// 使用熔爐(item_id)
		bool bbq();					// 使用篝火
		bool stove();				// 使用煉丹爐
		bool use_item();			// 使用物品
		void set_map(Map *);
		void set_energy(Energy *);
		void set_blood(Blood *);
		void set_gamewindow(GameWindow *);
		void set_bag(Bag *);
		void set_player(Player *);
		bool set_x_axis(int);
		bool set_y_axis(int);
		bool set_direction(int);
		void set_play_time(int);
		void set_invincible_time(int);
		int &get_x_axis();
		int &get_y_axis();
		int &get_direction();
		bool energy_update();
		bool change_status(int);
		int get_status();
		int get_pause();
		bool get_reverse();
		int get_play_time();
		int get_invincible_time();
		void change_reverse(bool);

	private:
		bool judge();				// 判斷是否面對物資(QT)
		bool wall();				// 障礙物判定
		//以下四個皆為走路判定
		bool go_up(int);			// 向上走
		bool go_down(int);			// 向下走
		bool go_left(int);			// 向左走
		bool go_right(int);			// 向右走
		Map *map;
		Energy *energy;
		Blood *blood;
		Bag *bag;
		GameWindow *gamewindow;
		Player *player;
		System *system;

		int direction;				// 方向
		bool reverse;				// 反向
		int x_axis;					// X 軸座標
		int y_axis;					// Y 軸座標
		int pause;					// 暫停狀態
		int status;					// 遊戲狀態
};

#endif // ACTION_H
