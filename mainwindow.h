#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private slots:
		void on_btn_new_game_clicked();

		void on_btn_old_memory_clicked();

		void on_btn_rule_intro_clicked();

		void on_action_game_intro_triggered();

		void on_action_old_memory_triggered();

		void on_action_new_game_triggered();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
