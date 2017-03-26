/********************************************************************************
* ファイル名　SetMap.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップ管理
********************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include "main.h"
#include "scene3D.h"
#include "manager.h"
#include "scene.h"
#include "SetMap.h"
/*******************************************************************************
マクロ定義
*******************************************************************************/

//------------------------------------------------------------------------------
//	関数名:	SetMap::SetMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
SetMap::SetMap()
{
	m_GameWall_001 = NULL;
	m_GameWall_002 = NULL;
	m_GameEnemy_001 = NULL;
	m_GameEnemy_002;
	m_GameCeiling = NULL;
	m_GameDoor = NULL;
	m_GamePoint = NULL;
}

//------------------------------------------------------------------------------
//	関数名:	SetMap::~SetMap
//	引数:	なし
//	戻り値:	
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
SetMap::~SetMap()
{

}

/*******************************************************************************
関数名：	HRESULT SetMap::Init
戻り値：	HRESULT
引数：		void
説明：		SetMapの初期化処理
**********	*********************************************************************/
void SetMap::Init(void)
{
	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CGameWall_001 *m_GameWall_001 = game->GetGameWall_001();
	CGameWall_002 *m_GameWall_002 = game->GetGameWall_002();
	CGameEnemy_001 *m_GameEnemy_001 = game->GetGameEnemy_001();
	CGameEnemy_002 *m_GameEnemy_002 = game->GetGameEnemy_002();
	CGameCeiling *m_GameCeiling = game->GetGameCeiling();
	CGameDoor *m_GameDoor = game->GetGameDoor();
	CGamePoint *m_GamePoint = game->GetGamePoint();
	for (int i = 0; i < m_LoadMap->m_Wall001_num; i++)
	{
		m_GameWall_001->SetGameWall_001(m_LoadMap->m_Pos_Wall_001[i], m_LoadMap->m_Rot_Wall_001[i]);
	}
	for (int i = 0; i < m_LoadMap->m_Wall002_num; i++)
	{
		m_GameWall_002->SetGameWall_002(m_LoadMap->m_Pos_Wall_002[i], m_LoadMap->m_Rot_Wall_002[i]);
	}
	for (int i = 0; i < m_LoadMap->m_Ceiling_num; i++)
	{
		m_GameCeiling->SetGameCeiling(m_LoadMap->m_Pos_Ceiling[i]);
	}
	for (int i = 0; i < m_LoadMap->m_Enemy001_num; i++)
	{
		m_GameEnemy_001->SetGameEnemy_001(m_LoadMap->m_Pos_Enemy_001[i], m_LoadMap->m_Rot_Enemy_001[i]);
	}

	for (int i = 0; i < m_LoadMap->m_Enemy002_num; i++)
	{
		m_GameEnemy_002->SetGameEnemy_002(m_LoadMap->m_Pos_Enemy_002[i], m_LoadMap->m_Rot_Enemy_002[i]);
	}
	for (int i = 0; i < m_LoadMap->m_Door_num; i++)
	{
		m_GameDoor->SetGameDoor(m_LoadMap->m_Pos_Door[i], m_LoadMap->m_Rot_Door[i]);
	}
	for (int i = 0; i < m_LoadMap->m_Point_num; i++)
	{
		m_GamePoint->SetGamePoint(m_LoadMap->m_Pos_Point[i]);
	}
}

/*******************************************************************************
関数名：	void SetMap::Uninit
戻り値：	void
引数：		void
説明：		SetMapの終了処理
*******************************************************************************/
void SetMap::Uninit(void)
{
	m_GameWall_001 = NULL;
	m_GameWall_002 = NULL;
	m_GameEnemy_001 = NULL;
	m_GameEnemy_002;
	m_GameCeiling = NULL;
	m_GameDoor = NULL;
	m_GamePoint = NULL;
}

/*******************************************************************************
関数名：	void SetMap::Update
戻り値：	void
引数：		void
説明：		SetMapの更新処理
*******************************************************************************/
void SetMap::Update()
{


}

/*******************************************************************************
関数名：	void SetMap::Draw
戻り値：	void
引数：		void
説明：		SetMapの描画処理
*******************************************************************************/
void SetMap::Draw(void)
{

}

