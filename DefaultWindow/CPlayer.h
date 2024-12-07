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
    void SetHeight(float _height) { m_pGroundHeight = _height; }//무

private:
    void        Key_Input();
    void        Jumping();
    void        Offset();

    void        CustomJumping(); // 무결

public:
    RECT* GetColRect() // 무결,충돌사각형 반환
    {
        return &m_CollisionRect;
    }
    INFO* GetColBox() // 무결,충돌 박스 반환
    {
        return &m_CollisionBox;
    }

    void SetJump(bool _isjump) { m_bJump = _isjump; }//무결,점프상태설정
    bool GetJump() { return m_bJump; }//무결, 점프상태반환

private:
    POINT               m_tPosin;
    bool                m_bJump;
    float               m_fJumpPower;
    float               m_fTime;

public: // 무결꺼 그대로 하긴 했는데 나중에 프라이빗으로 바꾸고 겟해야할듯

    INFO                m_CollisionBox; // 무결,충돌 박스 정보
    RECT                m_CollisionRect; // 무결,충돌 사각형 정보
    float               m_fJumpTime; //무결,점프 시간
    bool                m_bisGround; //무결,지면에 있는지 여부
    float              m_pGroundHeight;//무결,지면 높이
};

