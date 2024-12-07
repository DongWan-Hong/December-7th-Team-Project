#include "pch.h"
//#include "pch.h"
//#include "CBoss.h"
//#include "CBullet.h"
//
//CBoss::CBoss()
//{
//
//	ZeroMemory(&m_p_Boss_Bullet, sizeof(m_p_Boss_Bullet));
//	ZeroMemory(&turretEnd, sizeof(turretEnd));
//	ZeroMemory(&HP_INFO, sizeof(HP_INFO));
//	m_Boss_pPlayer = NULL;
//	m_ullLast_Fire = 0;
//	m_fTurretAngle = 0.f; // 포신 각도 초기화
//	m_fTurretSpeed = 2.f; // 포신 회전 속도
//	Bullet_X = 40;
//	Hp_Count = 0;
//	MAX_Hp = 10;
//
//}
//
//CBoss::~CBoss()
//{
//}
//
//void CBoss::Initialize()
//{
//	m_tInfo = { 300, -200, 200.f, 200.f };
//	HP_INFO = { 200,200,200.f,200.f };
//	m_fSpeed = 3.f;
//}
//
//int CBoss::Update()
//{
//	m_tInfo.fY += m_fSpeed;
//
//	if (m_tInfo.fY > 150) // 멈추는 조건
//	{
//		m_fSpeed = 0;
//	}
//
//	if (m_fSpeed == 0)
//	{
//		static int Boss_direction = 2.f;
//		m_tInfo.fX += Boss_direction;
//		if (m_tInfo.fX > WINCX - 300)  //오른쪽 벽충돌
//		{
//			m_tInfo.fX = WINCX - 300;
//			Boss_direction = -2.f;
//		}
//
//		if (m_tInfo.fX < 120) // 왼쪽
//		{
//			m_tInfo.fX = 120;
//			Boss_direction = +2.f;
//		}
//
//		Key_Input();
//	}
//
//	// 포신 회전 각도 갱신
//	m_fTurretAngle += m_fTurretSpeed;
//
//
//	if (bDead == true)
//	{
//		return OBJ_DEAD;
//	}
//
//
//
//	Update_Rect();
//	return OBJ_NOEVENT;
//
//
//}
//
//void CBoss::LateUpdate()
//{
//
//}
//
//void CBoss::Render(HDC hDC)
//{
//
//	Ellipse(hDC,
//		m_tRect.left,
//		m_tRect.top,
//		m_tRect.right,
//		m_tRect.bottom);
//
//	TCHAR box[32] = L""; // 총알
//	swprintf_s(box, L"보스");
//	TextOut(hDC, m_tInfo.fX - 17, m_tInfo.fY - 10, box, lstrlen(box)); // x축 y축
//
//
//	turretEnd.x = long(m_tInfo.fX + 100 * cosf(m_fTurretAngle * (PI / 180.f))); // 100은 선 길이
//	turretEnd.y = long(m_tInfo.fY - 100 * sinf(m_fTurretAngle * (PI / 180.f)));
//
//	// 포신 그리기
//	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
//	LineTo(hDC, turretEnd.x, turretEnd.y);
//	if (m_fSpeed == 0)
//	{
//		//레프트 탑 라이트 바텀
//		Rectangle(hDC, 40, 20, 580, 40); // 전체 체력
//		HBRUSH MyBrush = CreateSolidBrush(RGB(255, 0, 0));
//		HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
//		Rectangle(hDC, 40, 20, 40 + MAX_Hp - Hp_Count, 40); //  체력
//		SelectObject(hDC, OldBrush);
//		DeleteObject(MyBrush);
//
//	}
//
//	//Hp_Count
//}
//
//
//
//void CBoss::Release()
//{
//}
//
//void CBoss::Key_Input()
//{
//	if (GetAsyncKeyState('2')) // 오른쪽 벽 몰기 패턴
//	{
//		if (m_ullLast_Fire + 300 > GetTickCount64())
//		{
//			return;
//		}
//		m_ullLast_Fire = GetTickCount64();
//		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(2));
//	}
//	if (GetAsyncKeyState('3')) // 왼쪽 벽 몰기 패턴
//	{
//		if (m_ullLast_Fire + 300 > GetTickCount64())
//		{
//			return;
//		}
//		m_ullLast_Fire = GetTickCount64();
//		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(3));
//
//	}
//	if (GetAsyncKeyState('4'))  // 5개 유도탄
//	{
//		if (m_ullLast_Fire + 100 > GetTickCount64())
//		{
//			return;
//		}
//		m_ullLast_Fire = GetTickCount64();
//		m_p_Boss_Bullet->push_back(Create_Boss_Bullet(4));
//	}
//
//	if (m_ullLast_Fire + 800 > GetTickCount64())
//	{
//		return;
//	}
//	m_ullLast_Fire = GetTickCount64();
//	m_p_Boss_Bullet->push_back(Create_Boss_Bullet(1)); // 기본 총알
//
//
//}
//
//CObj* CBoss::Create_Boss_Bullet(int _type)
//{
//	CObj* pBullet = new Boss_Bullet;
//
//	if (_type == 1) // 기본 총알
//	{
//		static_cast<Boss_Bullet*>(pBullet)->Default_Bullet();
//
//		// 1번 총알 
//		CObj* bullet_1 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_1)->Default_Bullet();
//		bullet_1->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_1->Set_Ang(0.f);
//		// 2번 총알
//		CObj* bullet_2 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_2)->Default_Bullet();
//		bullet_2->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_2->Set_Ang(30.f);
//
//		// 3번 총알 ( 중앙 )
//		CObj* bullet_3 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_3)->Default_Bullet();
//		bullet_3->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_3->Set_Ang(60.f);
//		// 4번 총알 
//		CObj* bullet_4 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_4)->Default_Bullet();
//		bullet_4->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_4->Set_Ang(90.f);
//		// 5번 총알
//		CObj* bullet_5 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_5)->Default_Bullet();
//		bullet_5->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_5->Set_Ang(120.f);
//		// 6번 총알
//		CObj* bullet_6 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_6)->Default_Bullet();
//		bullet_6->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_6->Set_Ang(150.f);
//		// 7번 총알
//		CObj* bullet_7 = new Boss_Bullet;
//		static_cast<Boss_Bullet*>(bullet_7)->Default_Bullet();
//		bullet_7->Set_Pos(m_tInfo.fX, m_tInfo.fY);
//		bullet_7->Set_Ang(180.f);
//
//		// 리스트에 추가
//		m_p_Boss_Bullet->push_back(bullet_1);
//		m_p_Boss_Bullet->push_back(bullet_2);
//		m_p_Boss_Bullet->push_back(bullet_3);
//		m_p_Boss_Bullet->push_back(bullet_4);
//		m_p_Boss_Bullet->push_back(bullet_5);
//		m_p_Boss_Bullet->push_back(bullet_6);
//		m_p_Boss_Bullet->push_back(bullet_7);
//
//	}
//	else if (_type == 2) // 레이저 총알 오른벽 몰기
//	{
//		static int direction_Left = 1; // 
//
//		if (Bullet_X >= 490) // 오른쪽 끝에 닿았을 때
//		{
//			direction_Left = -1;
//		}
//		else if (Bullet_X <= 80) // 왼쪽 끝에 닿았을 때
//		{
//			direction_Left = 1;
//		}
//		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_1();
//		pBullet->Set_Pos(Bullet_X, -200); // 총알의 초기 위치를 포신 끝으로 설정
//		Bullet_X += 50 * direction_Left; // 방향에 따라 이동
//	}
//	else if (_type == 3) //3번  레이저 총알 왼벽 몰기
//	{
//		static int direction_Right = 1; // 
//		static float _Bullet_X = 550;
//
//		if (_Bullet_X >= 550) // 오른쪽 끝에 닿았을 때
//		{
//			direction_Right = -1;
//		}
//		else if (_Bullet_X <= 130) // 왼쪽 끝에 닿았을 때
//		{
//			direction_Right = +1;
//		}
//		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_2();
//		pBullet->Set_Pos(_Bullet_X, -200); // 총알의 초기 위치를 포신 끝으로 설정
//		_Bullet_X += 50 * direction_Right; // 방향에 따라 이동   
//	}
//	else if (_type == 4) // 유도총알
//	{
//		static_cast<Boss_Bullet*>(pBullet)->Boss_Bullet_3();
//		pBullet->Set_Pos(turretEnd.x, turretEnd.y);
//		pBullet->Set_Ang(m_fTurretAngle);
//
//		static_cast<Boss_Bullet*>(pBullet)->Set_Player(m_Boss_pPlayer);
//	}
//
//
//	return pBullet;
//}
//
//
