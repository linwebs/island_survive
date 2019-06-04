#ifndef RULEINTROWINDOW_H
#define RULEINTROWINDOW_H

#include <QDialog>

namespace Ui {
class RuleIntroWindow;
}

class RuleIntroWindow : public QDialog
{
		Q_OBJECT

	public:
		explicit RuleIntroWindow(QWidget *parent = nullptr);
		~RuleIntroWindow();

	private slots:
		void on_pushButton_clicked();

	private:
		Ui::RuleIntroWindow *ui;
};

#endif // RULEINTROWINDOW_H
