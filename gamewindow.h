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
class System;

class GameWindow : public QMainWindow
{
		Q_OBJECT

	public:
		GameWindow();
		GameWindow(QString);
		virtual ~GameWindow();
		void closeEvent (QCloseEvent*);
		void back_to_main_window();
		void set_play_time(int);
		void set_invincible_time(int);
		void set_bag_full_show_time(int);
		void set_use_item_time(int);
		void set_use_item_img(QString);
		int get_play_time();
		int get_invincible_time();
		int get_bag_full_show_time();
		int get_use_item_time();
		QString get_use_item_img();

	private:
        void create_actions();
        void create_menus();
		void destructor();
	private slots:
		void show_about();
		void show_use();
        void show_bag();
        void save_file();
		void pause_game();
		void exit_pause_game();
		void back_to_main_window_slot();
		void sub_time();
		void add_play_time();

	private:
		Map *map;				// view
		GameWindowScene *scene;	// scene
		Player *player;			// item
		QAction *menu_actions[4][6];
		QMenu *menus[4];
		QTimer *timer, *energy_timer;
		System *system;
		int play_time;
		int invincible_time;
		int bag_full_show_time;
		int use_item_show_time;
		QString use_item_img;
};

#endif // GAMEWINDOW_H
