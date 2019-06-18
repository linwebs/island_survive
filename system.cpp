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
#include "map.h"
#include "player.h"
#include "bag.h"

using namespace std;
#include "system.h"

System::System() {
	// constructor
}

// Save File Test
bool System::save(Player *p, Map *m, int status) {
	if(!QDir("data").exists()) {
		QDir().mkdir("data");
	}
	string name = QDateTime::currentDateTime().toString("yyyyMMddhhmm").toStdString();
	string file_name="data/" + name + ".data";
	QFile file(file_name.c_str());
	file.open(QIODevice::WriteOnly);

	QJsonObject json;

	json.insert("project", "island_survive");
	json.insert("type", "save");
	json.insert("note", "");
	json.insert("date_time", QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss"));

	QJsonObject player;
	player.insert("x_axis", p->action->get_x_axis());
	player.insert("y_axis", p->action->get_y_axis());
	player.insert("direction", p->action->get_direction());
	player.insert("status", status);
	player.insert("reverse", p->action->get_reverse());
//	player.insert("pause", p->action->get_pause());
	player.insert("energy", p->energy->get_energy());
	player.insert("blood", p->blood->get_blood());
	player.insert("time", p->action->get_play_time());
	player.insert("invincible", p->action->get_invincible_time());
	json.insert("player", player);

	QJsonObject size;
	size.insert("height", m->get_size_height()-8);
	size.insert("width", m->get_size_width()-15);
	json.insert("size", size);

	QJsonObject home;
	home.insert("height", m->get_home_size_height());
	home.insert("width", m->get_home_size_width());
	json.insert("home", home);

	QJsonArray bag;
	const vector<bags> bb = *p->bag->get_items();
	for(int i=0; i<bb.size(); i++) {
		QJsonObject bag_item;
		bag_item.insert("item", bb[i].item);
		bag_item.insert("quantity", bb[i].quantity);
		bag.append(bag_item);
	}
	json.insert("bag", bag);

	QJsonArray items;
	const vector<vector<map_item>> mm = *m->get_map_items();
	for(int i=7; i<mm.size()-8; i++) {
		for(int j=2; j<mm[0].size()-6; j++) {
			QJsonObject map_item;
			map_item.insert("item", mm[i][j].item);
			map_item.insert("size", mm[i][j].size);
			map_item.insert("walk", mm[i][j].walk);
			map_item.insert("img", mm[i][j].img);
			map_item.insert("x_axis", i-7);
			map_item.insert("y_axis", j-2);
			items.append(map_item);
		}
	}
	json.insert("items", items);

	QJsonDocument doc(json);
	QString str(doc.toJson((QJsonDocument::Compact)));
	QByteArray ba = str.toLocal8Bit();
	const char* data = ba.data();
	file.write(data);
	file.close();
	return true;
}

int System::get_save_file(QString files[] )
{
	int n=0;
	QDir directory("data");
	QStringList file = directory.entryList(QStringList() << "*.data", QDir::Files);
	//qDebug()<<file;

	foreach(QString filename, file) {
		//qDebug()<<filename;
		files[n++]=filename;
	}
	return n;
}

// Read File Test
QJsonObject System::read_save_file(QString save) {
	QString settings, name;
	name = "data/" + save + ".data";
	QFile file;
	file.setFileName(name);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	settings = file.readAll();
	file.close();

	QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
	//qWarning() << sd.isNull(); // <- print false :)
	QJsonObject sett = sd.object();
	if(!sd.isNull()) {
		if((sett["project"].toString().toStdString().data() == QString("island_survive"))) {
			if((sett["type"].toString().toStdString().data() == QString("save"))) {
				return sett;
			} else {
				qDebug()<<"System:: [savefile.data] type error!";
			}
		} else {
			qDebug()<<"System:: [savefile.data] project error!";
		}
	} else {
		qDebug()<<"System:: [savefile.data] empty!";
	}
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
