#pragma once

#include <list>

class Tiger;

//�Ր�����B
class TigerCreater
{
public:
	TigerCreater();
	~TigerCreater();
	void Update();
	void Draw();
private:
	SkinModelData m_skinModelData;
	std::list<Tiger*> m_tigers;		//!<�Ղ̃��X�g�B
	int m_timer = 0;
};

