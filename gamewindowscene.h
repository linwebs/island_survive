#ifndef GAMEWINDOWSCENE_H
#define GAMEWINDOWSCENE_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class Player;
class Map;

class GameWindowScene : public QGraphicsScene
{
		Q_OBJECT
	public:
		GameWindowScene(Player *, QObject *parent = 0);
		void set_map(Map *);
	protected:
		void keyPressEvent(QKeyEvent *);
		void mousePressEvent(QGraphicsSceneMouseEvent *);
		// void keyReleaseEvent(QKeyEvent *event);
	private:
		void space_event();
		void f_event();
		Player *player;
		Map *map;
};

#endif // GAMEWINDOWSCENE_H
