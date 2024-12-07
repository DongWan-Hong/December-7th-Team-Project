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
	m_tInfo  = { 100.f, WINCY / 2.f, 42.f, 48.f };//초기위치
	m_fSpeed = 10.f;//이동속도
	m_fDistance = 100.f;//이동거리
	m_fJumpPower = 3.f; //기본 점프 파워
}

int CPlayer::Update()
{
	Key_Input(); // 키 입력
	CustomJumping(); // 커스텀 점프 로직
	
	// 충돌 박스 설정
	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}
void CPlayer::Late_Update()
{
	m_CollisionRect = { m_tRect.left, m_tRect.bottom, m_tRect.right, m_tRect.bottom + 5 }; 
	Offset();// 화면 스크롤 처리
}


void CPlayer::Render(HDC hDC)
{
	//스크롤 위치 계산
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
		m_tInfo.fX -= m_fSpeed; // 왼쪽으로 이동
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed; // 오른쪽으로 이동
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_bisGround) { m_bJump = true; } // 지면에 있을 때만 점프 시작
		m_fJumpPower = 6.f; // 초기 점프 파워 설정
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (!m_bisGround && m_bJump)
		{
			m_fJumpPower += 0.5f; // 점프 파워 증가

			if (m_fJumpPower >= 16.f)
				m_fJumpPower = 16.f; // 최대 점프 파워 제한
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		if (m_bisGround)
		{
			m_fTime = 0.1f; // 시간 초기화
			m_bJump = false; // 점프 종료
		}
	}

}

void CPlayer::Jumping()
{
	float	fY(0.f);

	//라인충돌감지
	//무결코드는  m_tInfo.fY 추가
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY, m_tInfo.fY);
	if (m_bJump)
	{
		// 포물선 계산에 따라 y 위치 변경
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			// 충돌 시 점프 종료
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		// 지면 충돌 시 위치 설정
		m_tInfo.fY = fY;
	}
	else
	{
		// 공중에서 중력 적용
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
        CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed); // 화면 왼쪽 이동

    if (iOffSetmaxX < m_tInfo.fX + iScrollX)
        CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed); // 화면 오른쪽 이동
}

void CPlayer::CustomJumping()
{
	float Ground_Y(0.f);

	if (m_bJump)
	{
		m_bisGround = false;// 점프 중에는 지면에서 떨어짐
		float temp = (m_fJumpPower * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_tInfo.fY -= temp;
		m_fTime += 0.1f; // 무결코드는 파워 0.2에서 0.1f 로 수정됨

	}
	else
	{
		if (!m_bisGround) // 지면에 떨어져있을때
		{
			//공중에 있을 때의 중력적용
			m_tInfo.fY += 9.8f * m_fTime * m_fTime * 0.5f; // 중력
			m_fTime += 0.1f;
		}
		else
		{
			m_fTime = 0; // 지면 도달 시 초기화
		}
	}
}



