#ifndef OLDMEMORYWINDOW_H
#define OLDMEMORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class OldMemoryWindow;
}

class OldMemoryWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit OldMemoryWindow(QWidget *parent = nullptr);
		~OldMemoryWindow();
		void closeEvent (QCloseEvent*);

	private slots:
		void on_select_memory_clicked();

		void on_back_to_home_clicked();

	private:
		Ui::OldMemoryWindow *ui;
};

#endif // OLDMEMORYWINDOW_H
