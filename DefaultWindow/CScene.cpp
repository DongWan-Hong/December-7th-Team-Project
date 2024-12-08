#include "pch.h"
#include "CScene.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CWall.h"
#include "CScrollMgr.h"

CScene::CScene()
{
	ZeroMemory(&m_arrObj, sizeof(m_arrObj));
}

CScene::~CScene() 
{
	
}




