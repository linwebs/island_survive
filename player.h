#ifndef PLAYER_H
#define PLAYER_H
#include "blood.h"
#include "energy.h"
#include "action.h"
#include "bag.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Map;
class GameWindow;

class Player: public QObject, public QGraphicsPixmapItem
{
		Q_OBJECT
	public:
		Player(GameWindow *, QGraphicsItem *parent = 0);
		virtual ~Player();
		void set_map(Map *m);
		int get_play_time();
		bool add_play_time(int);

		Blood * blood;
		Energy * energy;
		Action * action;
		GameWindow *gamewindow;
		Bag * bag;
		Map *map;
		int play_time;
};

#endif // PLAYER_H
