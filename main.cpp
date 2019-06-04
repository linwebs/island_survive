#include "mainwindow.h"
#include <QSplashScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon("://res/img/logo/logo.ico"));

	//Add Splash Screen
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap("://res/img/logo/splashlogo.png"));
	splash->show();

	MainWindow w;
	w.show();

	QTimer::singleShot(40,splash,SLOT(close()));
	QTimer::singleShot(40,&w,SLOT(show()));

	return a.exec();
}
