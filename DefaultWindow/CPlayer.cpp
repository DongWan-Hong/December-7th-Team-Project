#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"

CPlayer::CPlayer() 
: m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f)

{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo  = { 100.f, WINCY / 2.f, 42.f, 48.f };//�ʱ���ġ
	m_fSpeed = 10.f;//�̵��ӵ�
	m_fDistance = 100.f;//�̵��Ÿ�
	m_fJumpPower = 3.f; //�⺻ ���� �Ŀ�
}

int CPlayer::Update()
{
	Key_Input(); // Ű �Է�
	CustomJumping(); // Ŀ���� ���� ����
	
	// �浹 �ڽ� ����
	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}
void CPlayer::Late_Update()
{
	m_CollisionRect = { m_tRect.left, m_tRect.bottom, m_tRect.right, m_tRect.bottom + 5 }; 
	Offset();// ȭ�� ��ũ�� ó��
}


void CPlayer::Render(HDC hDC)
{
	//��ũ�� ��ġ ���
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, 
		m_tRect.left + iScrollX,
		m_tRect.top, 
		m_tRect.right + iScrollX,
		m_tRect.bottom);	
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	float	fY(0.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed; // �������� �̵�
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed; // ���������� �̵�
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_bisGround) { m_bJump = true; } // ���鿡 ���� ���� ���� ����
		m_fJumpPower = 6.f; // �ʱ� ���� �Ŀ� ����
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (!m_bisGround && m_bJump)
		{
			m_fJumpPower += 0.5f; // ���� �Ŀ� ����

			if (m_fJumpPower >= 16.f)
				m_fJumpPower = 16.f; // �ִ� ���� �Ŀ� ����
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		if (m_bisGround)
		{
			m_fTime = 0.1f; // �ð� �ʱ�ȭ
			m_bJump = false; // ���� ����
		}
	}

}

void CPlayer::Jumping()
{
	float	fY(0.f);

	//�����浹����
	//�����ڵ��  m_tInfo.fY �߰�
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);
	if (m_bJump)
	{
		// ������ ��꿡 ���� y ��ġ ����
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			// �浹 �� ���� ����
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		// ���� �浹 �� ��ġ ����
		m_tInfo.fY = fY;
	}
	else
	{
		// ���߿��� �߷� ����
		m_tInfo.fY += 9.8f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;
	}
}

void CPlayer::Offset()
{
	/*int		iOffSetX = WINCX >> 1;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);*/

	int iOffSetminX = 100;
    int iOffSetmaxX = 700;

    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

    if (iOffSetminX > m_tInfo.fX + iScrollX)
        CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed); // ȭ�� ���� �̵�

    if (iOffSetmaxX < m_tInfo.fX + iScrollX)
        CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed); // ȭ�� ������ �̵�
}

void CPlayer::CustomJumping()
{
	float Ground_Y(0.f);

	if (m_bJump)
	{
		m_bisGround = false;// ���� �߿��� ���鿡�� ������
		float temp = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_tInfo.fY -= temp;
		m_fTime += 0.1f; // �����ڵ�� �Ŀ� 0.2���� 0.1f �� ������

	}
	else
	{
		if (!m_bisGround) // ���鿡 ������������
		{
			//���߿� ���� ���� �߷�����
			m_tInfo.fY += 9.8f * m_fTime * m_fTime * 0.5f; // �߷�
			m_fTime += 0.1f;
		}
		else
		{
			m_fTime = 0; // ���� ���� �� �ʱ�ȭ
		}
	}
}



