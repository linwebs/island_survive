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

class Player: public QObject, public QGraphicsPixmapItem
{
		Q_OBJECT
	public:
		Player(QGraphicsItem *parent = 0);
		void setMap(Map *m);

		Blood * blood;
		Energy * energy;
		Action * action;
		Bag * bag;
		Map *map;

};

#endif // PLAYER_H
