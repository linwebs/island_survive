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
		void back_to_main_window();

	private:
		Map *map;				// view
		GameWindowScene *scene;	// scene
		Player *player;			// item
		QAction *menu_actions[4][6];
		QMenu *menus[4];
};

#endif // GAMEWINDOW_H
