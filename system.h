#include <string>
#include <QString>
using namespace std;
#ifndef SYSTEM_H
#define SYSTEM_H

/* 系統 */
class System
{
	public:
		System();
		bool save(string);		// 儲存檔案
		int read(QString []);	// 讀取檔案(name)[開啟遊戲]
		bool exit();			// 離開遊戲[返回主畫面]

	private:
		string *get_data();	// 取得所有存檔
		string name;			// 檔案名稱
};

#endif // SYSTEM_H
