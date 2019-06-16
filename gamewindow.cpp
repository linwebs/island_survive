#include "gamewindow.h"
#include "mainwindow.h"
#include "map.h"
#include "ruleintrowindow.h"
#include "gamewindowscene.h"
#include "player.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

GameWindow::GameWindow()
{
	setWindowTitle("小島生存");  // 設定遊戲視窗標題
	setFixedSize(1280, 740);   // 設定遊戲視窗大小

	player = new Player();	// 建立玩家 object
	player->setPos(560, 453);

	play_time = 0;

	scene = new GameWindowScene(player, this);	// scene

	map = new Map(scene, &play_time);	// view
	player->set_map(map);

	player->action->set_map(map);
	scene->setSceneRect(0, 0, 1280, 720);	// 設定場景大小
	map->setScene(scene);
	map->set_player(player);
	scene->set_map(map);
	setCentralWidget(map);	// 將場景添加到 QMain Window

	/* 560: 1280-80*7=560
	 * 453: 720-80*2-107=453
	 */

	// make the player focusable and set it to be the current focus
	//player->setFlag(QGraphicsItem::ItemIsFocusable);
	//player->setFocus();
	scene->addItem(player);	// 將玩家加入場景中

    create_actions();	// 建立標題列按鈕活動(小分支)
    create_menus();		// 建立標題列按鈕

	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(add_play_time()));
//	connect("要connect的東西", SIGNAL("得到訊號"), this, SLOT("要執行的東西"));

	energy_timer = new QTimer(this);
	energy_timer->start(3000);
	connect(energy_timer, SIGNAL(timeout()), this, SLOT(sub_time()));
}

GameWindow::~GameWindow()
{
	timer->stop();
	energy_timer->stop();
	delete timer;
	delete energy_timer;
	delete player;
	delete map;
}

void GameWindow::destructor()
{
	timer->stop();
	energy_timer->stop();
	delete timer;
	delete energy_timer;
	delete player;
	delete map;
}

void GameWindow::sub_time()
{
	if(player->action->get_pause() == 0) {
		if(player->action->energy_update()) {
			map->show_energy_blood(player->energy->get_energy(), player->blood->get_blood());
		}
	}
}

void GameWindow::add_play_time()
{

	if(player->action->get_status() == 0) {
		play_time++;
	}
	//qDebug()<<"play time: "<<play_time;
}

void GameWindow::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "是否返回主畫面", "是否要存檔並返回主畫面", QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes) {
		event->accept();
		MainWindow *mainwindow = new MainWindow;
		mainwindow->show();
		// save file
		/* desctructor */
		destructor();

		this->hide();
	} else {
		event->ignore();
	}
}

void GameWindow::create_actions()
{
	menu_actions[0][0] = new QAction(tr("&存檔"), this);		// 次選單文字
	menu_actions[0][0] -> setShortcut(tr("Ctrl+S"));		// 呼叫次選單功能的快捷鍵
    connect(menu_actions[0][0], SIGNAL(triggered()), this, SLOT(save_file()));

	menu_actions[0][1] = new QAction(tr("&返回主畫面"), this);// 次選單文字
	menu_actions[0][1] -> setShortcut(tr("Ctrl+R"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[0][1], SIGNAL(triggered()), this, SLOT(back_to_main_window_slot()));

	//	menu_actions[0][2] = new QAction(tr("&離開遊戲"), this);	// 次選單文字
	//	menu_actions[0][2] -> setShortcut(tr("Ctrl+Q"));		// 呼叫次選單功能的快捷鍵
	//	connect(menu_actions[0][2], SIGNAL(triggered()), this, SLOT());

	menu_actions[1][0] = new QAction(tr("&暫停"), this);		// 次選單文字
    menu_actions[1][0] -> setShortcut(Qt::Key_P);		// 呼叫次選單功能的快捷鍵
    connect(menu_actions[1][0], SIGNAL(triggered()), this, SLOT(pause_game()));

    menu_actions[1][1] = new QAction(tr("&繼續"), this);		// 次選單文字
    menu_actions[1][1] -> setShortcut(Qt::Key_C);		// 呼叫次選單功能的快捷鍵
    connect(menu_actions[1][1], SIGNAL(triggered()), this, SLOT(exit_pause_game()));

    menu_actions[1][2] = new QAction(tr("&展開背包"), this);		// 次選單文字
    menu_actions[1][2] -> setShortcut(Qt::Key_B);		// 呼叫次選單功能的快捷鍵
    connect(menu_actions[1][2], SIGNAL(triggered()), this, SLOT(show_bag()));

	menu_actions[2][0] = new QAction(tr("&遊戲說明"), this);	// 次選單文字
	menu_actions[2][0] -> setShortcut(tr("Ctrl+I"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[2][0], SIGNAL(triggered()), this, SLOT(show_about()));
}

void GameWindow::create_menus()
{

	menus[0] = menuBar()->addMenu(tr("&遊戲"));	// 主選單文字
	menus[0]->addAction(menu_actions[0][0]);
	menus[0]->addAction(menu_actions[0][1]);
	//	menus[0]->addSeparator();
	//	menus[0]->addAction(menu_actions[0][2]);

	menus[1] = menuBar()->addMenu(tr("&選項"));	// 主選單文字
    menus[1]->addAction(menu_actions[1][0]);
    menus[1]->addAction(menu_actions[1][1]);
    menus[1]->addAction(menu_actions[1][2]);

	menus[2] = menuBar()->addMenu(tr("&說明"));	// 主選單文字
	menus[2]->addAction(menu_actions[2][0]);
	menus[2]->setToolTip("遊戲說明");				// 主選單內的次選單提示文字
}

void GameWindow::show_about(){

	RuleIntroWindow *ruleintrowindow = new RuleIntroWindow;
    ruleintrowindow->show();
}

void GameWindow::show_bag()
{
	if(player->action->get_status() == 0) {
        map->open_bag();
	} else if(player->action->get_status() == 9) {
		map->close_bag();
	}
}

void GameWindow::save_file()
{
    qDebug()<<"save file";
}

void GameWindow::pause_game()
{
	if(player->action->get_status() == 0)
		map->pause_game();
}

void GameWindow::exit_pause_game()
{
	map->exit_pause();
}

void GameWindow::back_to_main_window_slot() {
	back_to_main_window();
}

void GameWindow::back_to_main_window()
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "是否返回主畫面", "是否要存檔並返回主畫面", QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes) {
		MainWindow *mainwindow = new MainWindow;
		mainwindow->show();
		destructor();
		this->hide();
	}
}
