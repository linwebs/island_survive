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
		int object_id;	// 物件 id
		int x_axis;		// 物件 X 軸
		int y_axis;		// 物件 Y 軸
};

struct map_item {
		int item;
		int size;
		int walk;
		QString img;
};

#endif
