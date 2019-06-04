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
	aboutAction = new QAction(tr("&關於此遊戲"), this);  // 小標題文字
	aboutAction->setShortcut(tr("Ctrl+I")); // 小標題快捷鍵
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void GameWindow::createMenus()
{
	helpMenu = menuBar()->addMenu(tr("&說明"));   // 大標題文字
	helpMenu->setToolTip("遊戲簡介"); // 大標題提示文字
	helpMenu->addAction(aboutAction);
}

void GameWindow::showAbout(){

	RuleIntroWindow *ruleintrowindow = new RuleIntroWindow;
	ruleintrowindow->show();
}
