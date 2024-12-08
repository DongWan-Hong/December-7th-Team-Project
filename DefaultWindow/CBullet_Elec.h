#pragma once
#include "CBullet.h"
class CBullet_Elec: public CBullet
{
public:
	CBullet_Elec(){ }
	~CBullet_Elec() {}

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	BULLET_ID m_eBulletId;
};

