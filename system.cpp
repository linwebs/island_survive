#include <string>
#include <QDir>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QDateTime>
#include "player.h"
#include "action.h"
#include "bag.h"
#include "energy.h"
#include "blood.h"
#include "map.h"

using namespace std;
#include "system.h"

System::System() {
	// constructor
}

// Save File Test
bool System::save(Map *m, Player *p) {
	if(!QDir("data").exists()) {
		QDir().mkdir("data");
	}
	string name = QDateTime::currentDateTime().toString("yyyyMMddhhmm").toStdString();
	string file_name="data/" + name + ".dat";
	QFile file(file_name.c_str());
	file.open(QIODevice::WriteOnly);

	QJsonObject obj;
	obj.insert("project", "island_survive");
	obj.insert("type", "save");
	obj.insert("note", "");
	obj.insert("date_time", "");
	QJsonObject player;
	player.insert("x_axis", p->action->get_x_axis());
	player.insert("y_axis", p->action->get_y_axis());
	player.insert("direction", p->action->get_direction());
	player.insert("blood", p->blood->get_blood());
	player.insert("energy", p->energy->get_energy());
	player.insert("status", p->action->get_status());
	obj.insert("player", player);

	QJsonObject size;
	size.insert("height", m->get_size_height()-8);
	size.insert("width", m->get_size_width()-15);
	obj.insert("size", size);

	QJsonObject home;
	home.insert("height", m->get_home_size_height());
	home.insert("width", m->get_home_size_width());
	obj.insert("home", home);

	QJsonArray bag;
	const vector<bags> bb = *p->bag->get_items();
	for(int i=0; i<bb.size(); i++) {
		QJsonObject bags;
		bags.insert("item", bb[i].item);
		bags.insert("quantity", bb[i].quantity);
		bag.append(bags);
	}
	obj.insert("bag", bag);

	const vector<vector<map_item>> mm = *m->get_map_items();
	QJsonArray item;
	qDebug()<<mm.size()<<mm[0].size();
	for(int i=7; i<mm.size()-8; i++) {		// 65
		for(int j=2; j<mm[i].size()-6; j++) {	// 48
			QJsonObject items;
			items.insert("item", mm[i][j].item);
			items.insert("size", mm[i][j].size);
			items.insert("walk", mm[i][j].walk);
			items.insert("x_axis", i-7);
			items.insert("y_axis", j-2);
			items.insert("img", mm[i][j].img);
			item.append(items);
		}
	}

	for(int i=0; i<5; i++) {
		QJsonObject items;
		items.insert("item", 6);
		items.insert("size", 9);
		items.insert("walk", 0);
		items.insert("x_axis", 2);
		items.insert("y_axis", 10);
		items.insert("img", "://res/img/building/bbq_1_80.png");
		item.append(items);
	}
	obj.insert("item", item);

	QJsonDocument doc(obj);
	QString str(doc.toJson(QJsonDocument::Compact));
	QByteArray ba = str.toLocal8Bit();
	const char* data = ba.data();
	file.write(data);
	file.close();
	return true;
}

// Read File Test
int System::read(QString files[]) {
	int n=0;
	QDir directory("data");
	QStringList file = directory.entryList(QStringList() << "*.dat", QDir::Files);
	//qDebug()<<file;

	foreach(QString filename, file) {
		//qDebug()<<filename;
		files[n++]=filename;
	}
	return n;
}

QJsonObject System::get_default_map()
{
	//qDebug()<<"========================";

	QString settings;
	QFile file;
	file.setFileName("map.json");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	settings = file.readAll();
	file.close();

	QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
	//qWarning() << sd.isNull(); // <- print false :)
	QJsonObject sett = sd.object();
	if(!sd.isNull()) {
		if((sett["project"].toString().toStdString().data() == QString("island_survive"))) {
			if((sett["type"].toString().toStdString().data() == QString("map"))) {
				return sett;
			} else {
				qDebug()<<"System:: [map.json] type error!";
			}
		} else {
			qDebug()<<"System:: [map.json] project error!";
		}
	} else {
		qDebug()<<"System:: [map.json] empty!";
	}
	//qWarning() << sett.value(QString("project"));  // <- print my title

	//qDebug()<<"========================";
}

QString System::get_bag_item_file_path(int name)
{
//	return "://res/img/bag/bbb_180.png";
	switch (name) {
		case 1:
			return "://res/img/bag/grass_blue_180.png";
		case 2:
			return "://res/img/bag/grass_red_180.png";
		case 3:
			return "://res/img/bag/grass_purple_180.png";
		case 4:
			return "://res/img/bag/wood_180.png";
		case 5:
			return "://res/img/bag/stone_180.png";
		case 6:
			return "://res/img/bag/weapon_scissor_180.png";
		case 7:
			return "://res/img/bag/weapon_stone_180.png";
		case 8:
			return "://res/img/bag/weapon_paper_180.png";
		case 9:
			return "://res/img/bag/flesh_180.png";
		case 10:
			return "://res/img/bag/meat_180.png";
		default:
			return "";
	}
}

QString System::get_bags_item_file_path(int name)
{
	switch (name) {
		case 1:
			return "://res/img/bag/grass_blue_54.png";
		case 2:
			return "://res/img/bag/grass_red_54.png";
		case 3:
			return "://res/img/bag/grass_purple_54.png";
		case 4:
			return "://res/img/bag/wood_54.png";
		case 5:
			return "://res/img/bag/stone_54.png";
		case 6:
			return "://res/img/bag/weapon_scissor_54.png";
		case 7:
			return "://res/img/bag/weapon_stone_54.png";
		case 8:
			return "://res/img/bag/weapon_paper_54.png";
		case 9:
			return "://res/img/bag/flesh_54.png";
		case 10:
			return "://res/img/bag/meat_54.png";
		default:
			return "";
	}
}

/*
 * Write Data
if(!QDir("data").exists()) {
	QDir().mkdir("data");
}
QFile file("data/save1.dat");
file.open(QIODevice::WriteOnly);
const char* data = "welcome QT!\nHello World!";
file.write(data);
file.close();
 *
 * Get All Save Data
QDir directory("data");
QStringList file = directory.entryList(QStringList() << "*.dat", QDir::Files);
qDebug()<<file;

foreach(QString filename, file) {
	qDebug()<<filename;
}
*/
