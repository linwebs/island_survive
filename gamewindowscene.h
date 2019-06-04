#ifndef GAMEWINDOWSCENE_H
#define GAMEWINDOWSCENE_H
#include <QGraphicsScene>
#include <QKeyEvent>

class Player;

class GameWindowScene : public QGraphicsScene
{
		Q_OBJECT
	public:
		GameWindowScene(Player *p, QObject *parent = 0);
	protected:
		void keyPressEvent(QKeyEvent *event);
		// void keyReleaseEvent(QKeyEvent *event);
	private:
		Player *player;
};

#endif // GAMEWINDOWSCENE_H
