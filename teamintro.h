#ifndef TEAMINTRO_H
#define TEAMINTRO_H

#include <QDialog>

namespace Ui {
class TeamIntro;
}

class TeamIntro : public QDialog
{
		Q_OBJECT

	public:
		explicit TeamIntro(QWidget *parent = nullptr);
		~TeamIntro();

	private:
		Ui::TeamIntro *ui;
};

#endif // TEAMINTRO_H
