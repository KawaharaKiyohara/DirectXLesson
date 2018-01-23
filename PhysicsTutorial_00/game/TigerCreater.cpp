#include "stdafx.h"
#include "TigerCreater.h"
#include "Tiger.h"

TigerCreater::TigerCreater()
{
	m_skinModelData.LoadModelData("Assets/modelData/tiger.x", NULL);
}


TigerCreater::~TigerCreater()
{
	for (auto tiger : m_tigers) {
		delete tiger;
	}
}

void TigerCreater::Update()
{
	m_timer++;
	if (m_timer == 60) {
		//60�t���[���o�߂�����A�m���ŌՂ𐶐�����B
		int t = rand() % 100;
		if (t < 80) {
			//�Ղ����B
			Tiger* newTiger = new Tiger(&m_skinModelData);
			m_tigers.push_back(newTiger);
		}
		m_timer = 0.0f;
	}

	auto it = m_tigers.begin();
	while (it != m_tigers.end()) {
		if ((*it)->Update()) {
			it++;
		}
		else {
			//�Ղ���񎀖S�B
			delete *it;
			it = m_tigers.erase(it);
		}
	}
}

void TigerCreater::Draw()
{
	for (auto tiger : m_tigers) {
		tiger->Draw();
	}
}