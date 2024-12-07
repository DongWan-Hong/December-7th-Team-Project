#include "pch.h"
#include "Boss_FireMan.h"
#include "CBullet.h"
#include "CScrollMgr.h"
#include "CLineMgr.h"
#include "BlockMgr.h"

CBoss_FireMan::CBoss_FireMan()
{

	ZeroMemory(&m_p_Boss_Bullet, sizeof(m_p_Boss_Bullet));
	ZeroMemory(&HP_INFO, sizeof(HP_INFO));
	m_Boss_pPlayer = NULL;
	m_ullLast_Fire = 0;

	Bullet_X = 40;

	Hp_Count = 0;
	MAX_Hp = 10;

	m_bJump = false;
	m_fJumpPower=  0.f;
	m_fTime = 0.f;


}

CBoss_FireMan::~CBoss_FireMan()
{
}

void CBoss_FireMan::Initialize()
{
	m_tInfo = { 300, 400, 42.f, 48.f };
	HP_INFO = { 200,200,200.f,200.f };
	m_fSpeed = 3.f;
	
	
	 
}

int CBoss_FireMan::Update()
{
	
	Update_Rect();
	return OBJ_NOEVENT;
}


void CBoss_FireMan::Late_Update()
{
}


void CBoss_FireMan::Render(HDC hDC)
{
	// ��ũ�� ��ġ ���
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// ���� ��ü �簢�� ������
	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY);

	// ���� �̸� ���
	TCHAR box[32] = L"";
	swprintf_s(box, L"����");
	TextOut(hDC, m_tInfo.fX + iScrollX - 17, m_tInfo.fY + iScrollY - 10, box, lstrlen(box));

	// ü�� �� ��� (m_fSpeed ���� Ȯ��)
	if (m_fSpeed == 0)
	{
		// ��ü ü�� �� , ����Ʈ,ž,����Ʈ,����
		Rectangle(hDC, 90, 80, 110, 200);  // �ϴ� �ִ�ä�� 580

		// ü�� �� ���� ����
		HBRUSH MyBrush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);

		// ���� ü�¿� ���� �� ���� ���
		Rectangle(hDC, 90, 80, 110 , (200 - Hp_Count));

		// �귯�� ����
		SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);
	}
}




void CBoss_FireMan::Release()
{
}

void CBoss_FireMan::Key_Input()
{
	if (GetAsyncKeyState('2')) // ������ �� ���� ����
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Bullet(2));
	}
	if (GetAsyncKeyState('3')) // ���� �� ���� ����
	{
		if (m_ullLast_Fire + 300 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Bullet(3));

	}
	if (GetAsyncKeyState('4'))  // 5�� ����ź
	{
		if (m_ullLast_Fire + 100 > GetTickCount64())
		{
			return;
		}
		m_ullLast_Fire = GetTickCount64();
		m_p_Boss_Bullet->push_back(Create_Bullet(4));
	}

	if (m_ullLast_Fire + 800 > GetTickCount64())
	{
		return;
	}


}

CObj* CBoss_FireMan::Create_Bullet(int _type)
{
	CObj* pBullet = nullptr;

	

	return pBullet;
}

void CBoss_FireMan::Jumping()
{
	//float	fY(0.f);

	////�����浹����
	////�����ڵ��  m_tInfo.fY �߰�
	//bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m
	//if (m_bJump)
	//{
	//	// ������ ��꿡 ���� y ��ġ ����
	//	m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
	//	m_fTime += 0.2f;

	//	if (bLineCol && (fY < m_tInfo.fY))
	//	{
	//		// �浹 �� ���� ����
	//		m_bJump = false;
	//		m_fTime = 0.f;
	//		m_tInfo.fY = fY;
	//	}
	//}
	//else if (bLineCol)
	//{
	//	// ���� �浹 �� ��ġ ����
	//	m_tInfo.fY = fY;
	//}
	//else
	//{
	//	// ���߿��� �߷� ����
	//	m_tInfo.fY += 9.8f * m_fTime * m_fTime * 0.5f;
	//	m_fTime += 0.2f;
	//}
}

//





