#pragma once

#include"CObj.h"

class CBoss_FireMan : public CObj
{
public:
    CBoss_FireMan();
	~CBoss_FireMan();

private:
// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

    void     Key_Input();


public:
    void Set_HP(float _type) { Hp_Count = _type; }
    void Set_Player(CObj* pPlayer) { m_Boss_pPlayer = pPlayer; } // 플레이어 객체 설정

    void Set_Boss_Ground(bool _bisGround)
    {
        m_Boss_Ground = _bisGround;

    }
    bool Get_Boss_Ground()
    {

        return m_Boss_Ground;

    }
    void Set_Boss_Jump(bool _isjump) { m_bJump = _isjump; }//동완,점프상태설정
    bool GetJump() { return m_bJump; }//동완, 점프상태반환



    float Get_Hp() { return MAX_Hp - Hp_Count; }


    CObj* Create_Bullet(int _type);
    void Jumping();
private:
    ////////////////////////////////////////////
    
    /// <summary>
    /// //////////////////////////////////////////
    /// </summary>
    list<CObj*>* m_p_Boss_Bullet;
    unsigned long long m_ullLast_Fire;
    INFO HP_INFO;
    CObj* m_Boss_pPlayer; // 플레이어 객체를 저장할 멤버 변수

private:
    int Bullet_X;
    float MAX_Hp; // 기본 체력
    float Hp_Count; // 보스에 충돌할때마다 체크

    bool                m_bJump; // 점프체크
    float               m_fJumpPower;//점프속도
    float               m_fTime; // 시간
    bool                m_Boss_Ground;
    ////////////////////////
       bool m_bMovingLeft;
       int m_fJumpCooldown;
       


};

