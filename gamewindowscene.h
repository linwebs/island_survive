#ifndef GAMEWINDOWSCENE_H
#define GAMEWINDOWSCENE_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class Player;
class Map;
class GameWindow;

class GameWindowScene : public QGraphicsScene
{
		Q_OBJECT
	public:
		GameWindowScene(Player *, GameWindow *, QObject *parent = 0);
		void set_map(Map *);
	protected:
		void keyPressEvent(QKeyEvent *);
		void mousePressEvent(QGraphicsSceneMouseEvent *);
		// void keyReleaseEvent(QKeyEvent *event);
	private:
		void space_event();
		void f_event();
		void q_event();
		void up_event();
		void down_event();
		void left_event();
		void right_event();
		GameWindow *gamewindow;
		Player *player;
		Map *map;
};

#endif // GAMEWINDOWSCENE_H
