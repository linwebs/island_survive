#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "oldmemorywindow.h"
#include "ruleintrowindow.h"
#include "teamintro.h"
#include "useintro.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QPixmap bkgnd("://res/img/main/main_bgm.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);

	ui->btn_new_game->setStyleSheet("border-image: url(://res/img/main/new_game_btn.png);");
	ui->btn_old_memory->setStyleSheet("border-image: url(://res/img/main/old_game_btn.png);");
	ui->btn_rule_intro->setStyleSheet("border-image: url(://res/img/main/rule_intro_btn.png);");

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

void MainWindow::on_action_about_us_triggered()
{
	TeamIntro *teamintrowindow = new TeamIntro;
	teamintrowindow->show();
}

void MainWindow::on_action_game_control_triggered()
{
	UseIntro *useintrowindow = new UseIntro;
	useintrowindow->show();
}
