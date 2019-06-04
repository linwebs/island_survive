#include "ruleintrowindow.h"
#include "ui_ruleintrowindow.h"

RuleIntroWindow::RuleIntroWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RuleIntroWindow)
{
	ui->setupUi(this);
}

RuleIntroWindow::~RuleIntroWindow()
{
	delete ui;
}

void RuleIntroWindow::on_pushButton_clicked()
{
	this->hide();
}
