#ifndef USEINTRO_H
#define USEINTRO_H

#include <QDialog>

namespace Ui {
class UseIntro;
}

class UseIntro : public QDialog
{
		Q_OBJECT

	public:
		explicit UseIntro(QWidget *parent = nullptr);
		~UseIntro();

	private:
		Ui::UseIntro *ui;
};

#endif // USEINTRO_H
