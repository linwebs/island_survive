#include "teamintro.h"
#include "ui_teamintro.h"

TeamIntro::TeamIntro(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TeamIntro)
{
	ui->setupUi(this);
}

TeamIntro::~TeamIntro()
{
	delete ui;
}
