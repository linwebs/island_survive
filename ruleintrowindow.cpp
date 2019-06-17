#include "ruleintrowindow.h"
#include "ui_ruleintrowindow.h"
#include <QTextCursor>
#include <QScrollBar>

RuleIntroWindow::RuleIntroWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RuleIntroWindow)
{
	ui->setupUi(this);
	QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">					  <html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">					  p, li { white-space: pre-wrap; }					  </style></head><body style=\" font-family:'PMingLiU'; font-size:14pt; font-weight:400; font-style:normal;\">					  <p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/res/img/intro/game_intro.png\" /></p></body></html>";
	ui->textBrowser->setHtml(content);
	ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->minimum());
}

RuleIntroWindow::~RuleIntroWindow()
{
	delete ui;
}
