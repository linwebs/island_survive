#include "useintro.h"
#include "ui_useintro.h"

UseIntro::UseIntro(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UseIntro)
{
	ui->setupUi(this);
}

UseIntro::~UseIntro()
{
	delete ui;
}
