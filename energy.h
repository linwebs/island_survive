#ifndef ENERGY_H
#define ENERGY_H

/* 體力 */
class Energy
{
	public:
		Energy();
		Energy(int);		// 帶入存檔(energy)
		void sub_time();	// 定時扣飢餓度(QTimer主動呼叫)
		bool attack();		// 攻擊動物
		bool pick();		// 採草藥
		bool eat();			// 進食
		bool die();			// 死亡判定
		int get_energy();	// 取得體力

	private:
		bool add(int);		// 增加體力(數值)
		bool sub(int);		// 減少體力(數值)
		int energy;			// 體力
};

#endif // ENERGY_H
