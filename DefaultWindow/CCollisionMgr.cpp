#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"  

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT rc{};// �浹�Ѱ� ������ RECT ����ü

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			// �� ��ü�� RECT �浹 ���� Ȯ��
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				// �浹 �߻� �� �Ѵ� ����������
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

// �� �浹 ó��
//_Dst�� _Src ����Ʈ ���� ��� ��ü�� ���� ���� �浹 ���θ� Ȯ��
// - �浹 �߻� �� ���ó� �Ѵ� ������
void CCollisionMgr::Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			// �� �浹 ���� Ȯ��
			if (Check_Circle(Dst, Src))
			{
				// �浹 �߻� �� Ÿ�뽺
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

// �� �浹 ���� Ȯ�� �Լ�
//�� ��ü�� �߽� ��ǥ ���� �Ÿ��� ������ ���� ���Ͽ� �浹 ���� �Ǵ�
bool CCollisionMgr::Check_Circle(CObj* _Dst, CObj* _Src)
{
	float fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;//������ ��

	float fWidth  = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);// x�� �Ÿ�
	float fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);// y�� �Ÿ�

	float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);//�߽� ���� �Ÿ�

	return fRadius >= fDiagonal; // �������� ���� �߽� �Ÿ����� ũ�ų� ������ Ÿ�뽺
}

//�簢�� �浹ó��
// - �浹 �߻� �� ��ü�� ��ġ�� �о�� ������� ó��
//void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
//{
//	float	fX(0.f), fY(0.f);// ?
//
//	for (auto& Dst : _Dst)
//	{
//		for (auto& Src : _Src)
//		{
//			if (Check_Rect(Dst, Src, &fX, &fY)) 
//			{
//				// �� �� �浹
//				if (fX > fY)
//				{
//					// �� �浹
//					if (Dst->Get_Info().fY < Src->Get_Info().fY)
//					{
//						Dst->Set_PosY(-fY);
//					}
//					// �� �浹
//					else
//					{
//						Dst->Set_PosY(+fY);
//					}
//				}
//				
//				// �� �� �浹
//				else
//				{
//					// �� �浹
//					if (Dst->Get_Info().fX < Src->Get_Info().fX)
//					{
//						Dst->Set_PosX(-fX);
//					}
//					// �� �浹
//					else
//					{
//						Dst->Set_PosX(fX);
//					}
//				}
//			}
//		}
//	}
//}
// 
// - �浹 �߻� �� ��ü�� ��ġ�� �о�� ������� ó��? ( �����ڵ� ) �� �ּ� �ڵ�� ��
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float fX(0.f), fY(0.f); // �浹�� ���� �и� �Ÿ�

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY)) // �浹 ���� Ȯ��
			{
				// ���� �浹
				if (Dst->Get_Info().fX < Src->Get_Info().fX)
				{
					Dst->Set_PosX(-fX); // x�� ��ġ ����
				}
				// ���� �浹
				else
				{
					Dst->Set_PosX(fX); // x�� ��ġ ����
				}

				Dst->Update_Rect(); 
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* pX, float* pY)
{
    float fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX); // x�� �Ÿ�
    float fY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY); // y�� �Ÿ�

    float fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f; // x�� ������ ��
    float fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f; // y�� ������ ��

    if ((fRadiusX >= fX) && (fRadiusY >= fY)) // �浹 ���� Ȯ��
    {
        *pX = fRadiusX - fX; // x�� �и� �Ÿ� ���
        *pY = fRadiusY - fY; // y�� �и� �Ÿ� ���
        return true; // �浹 �߻�
    }

    return false; // �浹 ����
}



//(�����ڵ�) 
// �ڽ� �浹 ó��
// - �÷��̾�� �ڽ��� �浹 ���θ� Ȯ���ϰ�, �浹 �� ���� ���¿� ��ġ�� ����?
void CCollisionMgr::Collision_Box(CObj* _Player, list<CObj*> _Src)
{
    RECT rc{}; // �浹 ����
	int iColCount(0); // �뵵 �𸣰���...
    float Y(0); // y�� ��ġ ���� ��

    for (auto& Src : _Src)
    {
        if (IntersectRect(&rc, _Player->Get_Rect(), Src->Get_Rect()))
        {
            // �浹�� ��ü�� ���ʿ� �÷��̾ ��ġ��Ŵ
            Y = (rc.top) - _Player->Get_Info().fCY * 0.5f;
            _Player->Set_Pos(_Player->Get_Info().fX, Y);

            // �÷��̾� ���� ����? �ΰ� ����
            dynamic_cast<CPlayer*>(_Player)->m_bisGround = true;
            dynamic_cast<CPlayer*>(_Player)->SetJump(false);

            _Player->Update_Rect(); 
        }
    }
}

//(�����ڵ�)
// ���� �浹 ó��
// - �÷��̾ ���� �� ��ü�� �浹�Ͽ� ���鿡 �ִ� ���¸� �Ǵ�
void CCollisionMgr::Collision_Jump(CObj* _Player, list<CObj*> _Src)
{
	CPlayer* _Dst = dynamic_cast<CPlayer*>(_Player); // �÷��̾� ��ü�� �ٿ�ĳ����

	for (auto& Src : _Src)
	{
		float fY = abs(_Dst->GetColBox()->fY - Src->Get_Info().fY); // y�� �Ÿ�
		float fRadiusY = (_Dst->GetColBox()->fCY + Src->Get_Info().fCY) * 0.5f; // y�� ������ ��

		if (fRadiusY >= fY && _Dst->GetJump() == false) // �浹 �߻� �� ���� ���°� �ƴ� ���
		{
			_Dst->m_bisGround = true; // ���鿡 ����
			break; // �浹 Ȯ�� �� ����
		}

		_Dst->m_bisGround = false; // ���鿡�� ������
	}
}