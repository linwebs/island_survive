#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QLabel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "struct.cpp"
#include "gamewindow.h"
#include "gamewindowscene.h"
using namespace std;

/* 地圖 */
class Map : public QGraphicsView
{
	public:
		Map(GameWindowScene *GWscene);
		Map(vector<maps>);	// 帶入存檔(map)
		bool create();		// 生成地圖
		bool update_map();

	private:
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
		vector<maps> map;	// 地圖組成項目列表
		GameWindowScene *scene;
		QGraphicsPixmapItem *background[16][9];
		QGraphicsPixmapItem *grasses[16][9];
};


#endif // MAP_H
