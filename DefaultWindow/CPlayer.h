#pragma once
#include "CObj.h"
#include "CShield.h"
#include "CScrewBullet.h"
#include "CGuideBullet.h"

class CPlayer :    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void SetHeight(float _height) { m_pGroundHeight = _height; }//��

private:
    void        Key_Input();
    void        Jumping();
    void        Offset();

    void        CustomJumping(); // ����

public:
    RECT* GetColRect() // ����,�浹�簢�� ��ȯ
    {
        return &m_CollisionRect;
    }
    INFO* GetColBox() // ����,�浹 �ڽ� ��ȯ
    {
        return &m_CollisionBox;
    }

    void SetJump(bool _isjump) { m_bJump = _isjump; }//����,�������¼���
    bool GetJump() { return m_bJump; }//����, �������¹�ȯ

private:
    POINT               m_tPosin;
    bool                m_bJump;
    float               m_fJumpPower;
    float               m_fTime;

public: // ���Შ �״�� �ϱ� �ߴµ� ���߿� �����̺����� �ٲٰ� ���ؾ��ҵ�

    INFO                m_CollisionBox; // ����,�浹 �ڽ� ����
    RECT                m_CollisionRect; // ����,�浹 �簢�� ����
    float               m_fJumpTime; //����,���� �ð�
    bool                m_bisGround; //����,���鿡 �ִ��� ����
    float              m_pGroundHeight;//����,���� ����
};

