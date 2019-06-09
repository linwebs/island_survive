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

	scene = new GameWindowScene(player);	// scene

	map = new Map(scene);	// view
	player->setMap(map);


	player->action->setMap(map);
	scene->setSceneRect(0, 0, 1280, 720);	// 設定場景大小
	map->setScene(scene);
	setCentralWidget(map);	// 將場景添加到 QMain Window

	/* 560: 1280-80*7=560
	 * 453: 720-80*2-107=453
	 */

	// make the player focusable and set it to be the current focus
	//player->setFlag(QGraphicsItem::ItemIsFocusable);
	//player->setFocus();
	scene->addItem(player);	// 將玩家加入場景中

	createActions();	// 建立標題列按鈕活動(小分支)
	createMenus();		// 建立標題列按鈕
}

void GameWindow::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "是否返回主畫面", "是否要存檔並返回主畫面", QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes) {
		event->accept();
		MainWindow *mainwindow = new MainWindow;
		mainwindow->show();
		this->hide();
	} else {
		event->ignore();
	}
}

void GameWindow::createActions()
{
	menu_actions[0][0] = new QAction(tr("&存檔"), this);		// 次選單文字
	menu_actions[0][0] -> setShortcut(tr("Ctrl+S"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[0][0], SIGNAL(triggered()), this, SLOT(showAbout()));

	menu_actions[0][1] = new QAction(tr("&返回主畫面"), this);// 次選單文字
	menu_actions[0][1] -> setShortcut(tr("Ctrl+R"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[0][1], SIGNAL(triggered()), this, SLOT(showAbout()));

	menu_actions[0][2] = new QAction(tr("&離開遊戲"), this);	// 次選單文字
	menu_actions[0][2] -> setShortcut(tr("Ctrl+Q"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[0][2], SIGNAL(triggered()), this, SLOT(back_to_main_window()));

	menu_actions[1][0] = new QAction(tr("&暫停"), this);		// 次選單文字
	menu_actions[1][0] -> setShortcut(tr("Ctrl+P"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[1][0], SIGNAL(triggered()), this, SLOT(showAbout()));

	menu_actions[1][1] = new QAction(tr("&繼續"), this);		// 次選單文字
	menu_actions[1][1] -> setShortcut(tr("Ctrl+C"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[1][1], SIGNAL(triggered()), this, SLOT(showAbout()));

	menu_actions[2][0] = new QAction(tr("&遊戲說明"), this);	// 次選單文字
	menu_actions[2][0] -> setShortcut(tr("Ctrl+I"));		// 呼叫次選單功能的快捷鍵
	connect(menu_actions[2][0], SIGNAL(triggered()), this, SLOT(showAbout()));
}

void GameWindow::createMenus()
{

	menus[0] = menuBar()->addMenu(tr("&遊戲"));	// 主選單文字
	menus[0]->addAction(menu_actions[0][0]);
	menus[0]->addAction(menu_actions[0][1]);
	menus[0]->addSeparator();
	menus[0]->addAction(menu_actions[0][2]);

	menus[1] = menuBar()->addMenu(tr("&選項"));	// 主選單文字
	menus[1]->addAction(menu_actions[1][0]);
	menus[1]->addAction(menu_actions[1][1]);

	menus[2] = menuBar()->addMenu(tr("&說明"));	// 主選單文字
	menus[2]->addAction(menu_actions[2][0]);
	menus[2]->setToolTip("遊戲說明");				// 主選單內的次選單提示文字
}

void GameWindow::showAbout(){

	RuleIntroWindow *ruleintrowindow = new RuleIntroWindow;
	ruleintrowindow->show();
}

void GameWindow::back_to_main_window()
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "是否返回主畫面", "是否要存檔並返回主畫面", QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes) {
		MainWindow *mainwindow = new MainWindow;
		mainwindow->show();
		this->hide();
	}
}
