#include "gamewindowview.h"

GameWindowView::GameWindowView()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1280, 720);

	show();
}

void GameWindowView::sceneSet(QGraphicsScene *scene) {
	setScene(scene);
}
