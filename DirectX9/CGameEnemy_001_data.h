///********************************************************************************
//* タイトル　01
//* ファイル名　CGameEnemy_001_data.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/10
//* GameEnemy_001data
//********************************************************************************/
#ifndef	_CGAMEENEMY_001_DATA_H_
#define	_CGAMEENEMY_001_DATA_H_
#include "scene.h"
#include "CLoadMap.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

class CGameEnemy_001_data
{
friend class CLoadMap;
friend class CGameEnemy_001;
friend class CEnemy_Bullet;
public:

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;	// スケール値
	CMatrix Matrix;
	bool m_bUse;
	bool m_bMove_Muki;
	bool m_bMove_Use;
	float m_speed;
	D3DXVECTOR3 m_LoadPos;
	int m_Life;
	int m_Control_Bullet;
	bool m_Bullet_Use;
	CGameEnemy_001_data() {
		m_Position = D3DXVECTOR3(0.0f, 5000.0f, 0.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f,1.0f, 1.0f);
		m_LoadPos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		m_bUse = false;
		m_bMove_Muki = false;
		m_bMove_Use = true;
		m_Bullet_Use = true;
		m_speed = 1.0f;
		m_Life = 5;
		m_Control_Bullet = 0;
	}
};
#endif