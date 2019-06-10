#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>

class GameWindowScene;
class Map;
class Player;

class GameWindow : public QMainWindow
{
		Q_OBJECT

	public:
		GameWindow();
		virtual ~GameWindow();
		void closeEvent (QCloseEvent*);
	private:
		void createActions();
		void createMenus();
		void destructor();
	private slots:
		void showAbout();
		void pause_game();
		void exit_pause_game();
		void back_to_main_window();
		void sub_time();
		void add_play_time();

	private:
		Map *map;				// view
		GameWindowScene *scene;	// scene
		Player *player;			// item
		QAction *menu_actions[4][6];
		QMenu *menus[4];
		QTimer *timer, *energy_timer;
		int play_time;
};

#endif // GAMEWINDOW_H
