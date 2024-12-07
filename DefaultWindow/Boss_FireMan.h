#pragma once

#include"CObj.h"

class CBoss_FireMan : public CObj
{
public:
    CBoss_FireMan();
	~CBoss_FireMan();

private:
// CObj��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

    void     Key_Input();


public:
    void Set_HP(float _type) { Hp_Count = _type; }
    void Set_Player(CObj* pPlayer) { m_Boss_pPlayer = pPlayer; } // �÷��̾� ��ü ����

    void Set_Boss_Ground(bool _bisGround)
    {
        m_Boss_Ground = _bisGround;

    }
    bool Get_Boss_Ground()
    {

        return m_Boss_Ground;

    }
    void Set_Boss_Jump(bool _isjump) { m_bJump = _isjump; }//����,�������¼���
    bool GetJump() { return m_bJump; }//����, �������¹�ȯ



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
    CObj* m_Boss_pPlayer; // �÷��̾� ��ü�� ������ ��� ����

private:
    int Bullet_X;
    float MAX_Hp; // �⺻ ü��
    float Hp_Count; // ������ �浹�Ҷ����� üũ

    bool                m_bJump; // ����üũ
    float               m_fJumpPower;//�����ӵ�
    float               m_fTime; // �ð�
    bool                m_Boss_Ground;
    ////////////////////////
       bool m_bMovingLeft;
       int m_fJumpCooldown;
       


};

