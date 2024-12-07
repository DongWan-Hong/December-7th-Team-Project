#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}
void CBullet::Late_Update()
{

}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::Default_Bullet()
{
	m_tInfo.fCX = 20.f; // ÃÑ¾Ë Å©±â
	m_tInfo.fCY = 20.f;
	m_fSpeed = 10.f;

	Check_Bul = Default;
}

void CBullet::Skill_F1_Bullet()
{

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 15.f;

	Check_Bul = Skill_1;

}

void CBullet::Skill_F2_Bullet()
{

	m_tInfo.fCX = 20.f; // Å©±â
	m_tInfo.fCY = 20.f;
	m_tRect.right = 50;
	m_tRect.left = 50;


	m_fSpeed = 20.f; //ÃÑ¾Ë¼Óµµ

	Check_Bul = Skill_2;

}

