#ifndef GAMEWINDOWSCENE_H
#define GAMEWINDOWSCENE_H
#include <QGraphicsScene>
#include <QKeyEvent>

class Player;
class Map;

class GameWindowScene : public QGraphicsScene
{
		Q_OBJECT
	public:
		GameWindowScene(Player *p, QObject *parent = 0);
		void set_map(Map *);
	protected:
		void keyPressEvent(QKeyEvent *event);
		// void keyReleaseEvent(QKeyEvent *event);
	private:
		void space_event();
		Player *player;
		Map *map;
};

#endif // GAMEWINDOWSCENE_H
