#ifndef ACTION_H
#define ACTION_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Map;
/* 行動 */
class Action: public QGraphicsPixmapItem
{
	public:
		Action();
		Action(int);		// 帶入存檔(direction, x-axis, y-axis)
		bool move(int);		// 行走(direction_id)
		bool pick(int);		// 採集資源(item id)
		bool attack();		// 獵殺動物
		bool furmace(int);	// 使用熔爐(item_id)
		bool bbq();			// 使用篝火
		bool stove();		// 使用煉丹爐
		void setMap(Map *m);
		//void keyPressEvent(QKeyEvent *event); // 偵測鍵盤事件

	private:
		bool judge();		// 判斷是否面對物資(QT)
		bool wall();		// 障礙物判定
		//以下四個皆為走路判定
		bool go_up(int);		// 向上走
		bool go_down(int);		// 向下走
		bool go_left(int);		// 向左走
		bool go_right(int);	// 向右走
		Map *map;

		int direction;		// 方向
		int x_axis;			// X 軸座標
		int y_axis;			// Y 軸座標
};

#endif // ACTION_H
