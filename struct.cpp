#ifndef STRUCT
#define STRUCT

#include <iostream>
#include <QString>
using namespace std;

/* 角色位置結構 */
struct location {
		int x;			// 角色 x 軸
		int y;			// 角色 y 軸
		int direction;	// 角色面相方向
		/* direction:
	 *  1=>up,
	 *  2=>down,
	 *  3=>left,
	 *  4=>right
	 */
};

/* 背包結構 */
struct bags {
		int item;		// 物品 id
		int quantity;	// 物品數量
};

/* 地圖結構 */
struct maps {
		int object_id;
		// 物件 id
		int x_axis;		// 物件 X 軸
		int y_axis;		// 物件 Y 軸
};

struct map_item {
		int item;
		int size;
		int walk;
		QString img;
};

#define WEAPON_SCISSOR_WOOD 2
#define WEAPON_SCISSOR_STONE 0
#define WEAPON_STONE_WOOD 0
#define WEAPON_STONE_STONE 2
#define WEAPON_PAPER_WOOD 1
#define WEAPON_PAPER_STONE 1
#define MAP_GRASS_PATH "://res/img/land/grass_80.png"
#define MAP_WOOD_PATH "://res/img/land/wood_80.png"
#define MAP_STONE_PATH "://res/img/land/stone_80.png"
#define MAP_ANIMAL_PATH "://res/img/land/animal_80.png"
#endif
