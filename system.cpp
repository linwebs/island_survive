#include <string>
#include <QDir>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

using namespace std;
#include "system.h"

System::System() {
	// constructor
}

// Save File Test
bool System::save(string name) {
	if(!QDir("data").exists()) {
		QDir().mkdir("data");
	}
	string file_name="data/"+name;
	QFile file(file_name.c_str());
	file.open(QIODevice::WriteOnly);

	const char* data = "Save File!\nsaving data!\n";
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
	qDebug()<<"========================";

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

	qDebug()<<"========================";
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
