///********************************************************************************
//* タイトル　01
//* ファイル名　CGameDoor_data.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/10
//* GameDoordata
//********************************************************************************/
#ifndef	_CGAMDOOR_DATA_H_
#define	_CGAMDOOR_DATA_H_
#include "scene.h"
#include "CLoadMap.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

class CGameDoor_data
{
	friend class CLoadMap;
	friend class CGameDoor;
	friend class CEnemy_Bullet;
public:

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;	// スケール値
	CMatrix Matrix;
	bool m_bUse;
	bool m_bEffectUse;
	CGameDoor_data() {
		m_Position = D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_bUse = false;
		m_bEffectUse = true;
	}
};
#endif