#pragma once

#include <list>

class Tiger;

//虎生成器。
class TigerCreater
{
public:
	TigerCreater();
	~TigerCreater();
	void Update();
	void Draw();
private:
	SkinModelData m_skinModelData;
	std::list<Tiger*> m_tigers;		//!<虎のリスト。
	int m_timer = 0;
};

