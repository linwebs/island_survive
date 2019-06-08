#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

class GameWindowScene;
class Map;
class Player;

class GameWindow : public QMainWindow
{
		Q_OBJECT

	public:
		GameWindow();
		void closeEvent (QCloseEvent*);
	private:
		void createActions();
		void createMenus();
	private slots:
		void showAbout();

	private:
		Map *map;				// view
		GameWindowScene *scene;	// scene
		Player *player;			// item
		QAction *MenuActions[4][6];
		QMenu *Menus[4];
};

#endif // GAMEWINDOW_H
