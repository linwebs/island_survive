#include "oldmemorywindow.h"
#include "ui_oldmemorywindow.h"
#include "mainwindow.h"
#include "gamewindow.h"
#include "system.h"
#include <QDebug>
#include <QString>
#include <QCloseEvent>

OldMemoryWindow::OldMemoryWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::OldMemoryWindow)
{
	ui->setupUi(this);
	this->statusBar()->setSizeGripEnabled(false);
	System s;
	QString ss[1000], name;
	int l = s.get_save_file(ss);
	for(int i=0; i<l; i++) {
		name = ss[i].mid(0,4) + "/" + ss[i].mid(4,2) + "/" + ss[i].mid(6,2) + " " +
			   ss[i].mid(8,2) + ":" + ss[i].mid(10,2) + " " + ss[i].mid(12, ss[i].size()-17);
		ui->listWidget->addItem(name);
	}


	qDebug()<<System::get_default_map();


	/*
	ui->listWidget->addItem("data001");
	ui->listWidget->addItem("data002");
	ui->listWidget->addItem("data003");*/
}

OldMemoryWindow::~OldMemoryWindow()
{
	delete ui;
}

void OldMemoryWindow::on_select_memory_clicked()
{
	QString selected = ui->listWidget->currentItem()->text();
	QString name;
	name += selected.mid(0,4);
	name += selected.mid(5,2);
	name += selected.mid(8,2);
	name += selected.mid(11,2);
	name += selected.mid(14,2);
	name += selected.mid(17,selected.size()-16);
	GameWindow *gamewindow = new GameWindow(name);
	gamewindow->show();
	this->hide();
	qDebug()<<name;
}

void OldMemoryWindow::on_back_to_home_clicked()
{
	MainWindow *mainwindow = new MainWindow;
	mainwindow->show();
	this->hide();
}

void OldMemoryWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
	MainWindow *mainwindow = new MainWindow;
	mainwindow->show();
	this->hide();
}
