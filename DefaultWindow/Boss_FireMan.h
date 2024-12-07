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

    float Get_Hp() { return MAX_Hp - Hp_Count; }
    void Set_HP(float _type) { Hp_Count = _type; }
    void Set_Player(CObj* pPlayer) { m_Boss_pPlayer = pPlayer; } // �÷��̾� ��ü ����

    void Set_Ground(bool _bisGround)
    {

        m_bisGround = _bisGround;

    }
    bool Get_Ground()
    {

        return m_bisGround;

    }
    void SetJump(bool _isjump) { m_bJump = _isjump; }//����,�������¼���
    bool GetJump() { return m_bJump; }//����, �������¹�ȯ


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
    bool                m_bisGround;\

        ////////////////////////


};

