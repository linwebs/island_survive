#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "oldmemorywindow.h"
#include "ruleintrowindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QPixmap bkgnd("://res/img/logo/splashlogo.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btn_new_game_clicked()
{
	GameWindow *gamewindow = new GameWindow;
	gamewindow->show();
	this->hide();
}

void MainWindow::on_action_new_game_triggered()
{
	GameWindow *gamewindow = new GameWindow;
	gamewindow->show();
	this->hide();
}

void MainWindow::on_btn_old_memory_clicked()
{
	OldMemoryWindow *oldmemorywindow = new OldMemoryWindow;
	oldmemorywindow->show();
	this->hide();
}

void MainWindow::on_action_old_memory_triggered()
{
	OldMemoryWindow *oldmemorywindow = new OldMemoryWindow;
	oldmemorywindow->show();
	this->hide();
}

void MainWindow::on_btn_rule_intro_clicked()
{
	RuleIntroWindow *ruleintrowindow = new RuleIntroWindow;
	ruleintrowindow->show();
}

void MainWindow::on_action_game_intro_triggered()
{
	RuleIntroWindow *ruleintrowindow = new RuleIntroWindow;
	ruleintrowindow->show();
}
