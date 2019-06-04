#include "oldmemorywindow.h"
#include "ui_oldmemorywindow.h"
#include "mainwindow.h"
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
	int l = s.read(ss);
	for(int i=0; i<l; i++) {
		name = ss[i].mid(0,4) + "/" + ss[i].mid(4,2) + "/" + ss[i].mid(6,2) + " " +
			   ss[i].mid(8,2) + ":" + ss[i].mid(10,2) + " " + ss[i].mid(12, ss[i].size()-16);
		ui->listWidget->addItem(name);
	}
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
	qDebug()<< ui->listWidget->currentItem()->text();
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
