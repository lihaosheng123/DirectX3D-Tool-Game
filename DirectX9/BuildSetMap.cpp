/********************************************************************************
* ファイル名　BuildSetMap.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップの描画管理
********************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "scene3D.h"
#include "manager.h"
#include "scene.h"
#include "BuildSetMap.h"
/*******************************************************************************
マクロ定義
*******************************************************************************/

//------------------------------------------------------------------------------
//	関数名:	BuildSetMap::BuildSetMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
BuildSetMap::BuildSetMap()
{



}

//------------------------------------------------------------------------------
//	関数名:	BuildSetMap::~BuildSetMap
//	引数:	なし
//	戻り値:	
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
BuildSetMap::~BuildSetMap()
{

}

/*******************************************************************************
関数名：	void BuildSetMap::Init
戻り値：	なし
引数：		void
説明：		BuildSetMapの初期化処理
**********	*********************************************************************/
void BuildSetMap::Init(void)
{
	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();

	CGameWall_001 *m_GameWall_001 = BuildManager->GetGameWall_001();
	CGameWall_002 *m_GameWall_002 = BuildManager->GetGameWall_002();
	CGameEnemy_001 *m_GameEnemy_001 = BuildManager->GetGameEnemy_001();
	CGameEnemy_002 *m_GameEnemy_002 = BuildManager->GetGameEnemy_002();
	CGameCeiling *m_GameCeiling = BuildManager->GetGameCeiling();
	CGameDoor *m_GameDoor = BuildManager->GetGameDoor();
	CGamePoint *m_GamePoint = BuildManager->GetGamePoint();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	//壁001の描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Wall001_num; i++)
	{
		m_GameWall_001->SetGameWall_001(m_BuildLoadMap->m_Pos_Wall_001[i], m_BuildLoadMap->m_Rot_Wall_001[i]);
	}
	//壁002の描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Wall002_num; i++)
	{
		m_GameWall_002->SetGameWall_002(m_BuildLoadMap->m_Pos_Wall_002[i], m_BuildLoadMap->m_Rot_Wall_002[i]);
	}
	//天井板の描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Ceiling_num; i++)
	{
		m_GameCeiling->SetGameCeiling(m_BuildLoadMap->m_Pos_Ceiling[i]);
	}
	//敵001の描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Enemy001_num; i++)
	{
		m_GameEnemy_001->SetGameEnemy_001(m_BuildLoadMap->m_Pos_Enemy_001[i], m_BuildLoadMap->m_Rot_Enemy_001[i]);
	}
	//敵002の描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Enemy002_num; i++)
	{
		m_GameEnemy_002->SetGameEnemy_002(m_BuildLoadMap->m_Pos_Enemy_002[i], m_BuildLoadMap->m_Rot_Enemy_002[i]);
	}
	//ドアモデルの描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Door_num; i++)
	{
		m_GameDoor->SetGameDoor(m_BuildLoadMap->m_Pos_Door[i], m_BuildLoadMap->m_Rot_Door[i]);
	}
	//条件モデルの描画配置
	for (int i = 0; i < m_BuildLoadMap->m_Point_num; i++)
	{
		m_GamePoint->SetGamePoint(m_BuildLoadMap->m_Pos_Point[i]);
	}
}

/*******************************************************************************
関数名：	void BuildSetMap::Uninit
戻り値：	void
引数：		void
説明：		BuildSetMapの終了処理
*******************************************************************************/
void BuildSetMap::Uninit(void)
{

}

/*******************************************************************************
関数名：	void BuildSetMap::Update
戻り値：	void
引数：		void
説明：		BuildSetMapの更新処理
*******************************************************************************/
void BuildSetMap::Update()
{


}

/*******************************************************************************
関数名：	void BuildSetMap::Draw
戻り値：	void
引数：		void
説明：		BuildSetMapの描画処理
*******************************************************************************/
void BuildSetMap::Draw(void)
{

}

