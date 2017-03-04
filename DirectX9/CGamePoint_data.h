///********************************************************************************
//* タイトル　01
//* ファイル名　CGamePoint_data.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/10
//* GamePointdata
//********************************************************************************/
#ifndef	_CGAMPOINT_DATA_H_
#define	_CGAMPOINT_DATA_H_
#include "scene.h"
#include "CLoadMap.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

class CGamePoint_data
{
	friend class CLoadMap;
	friend class CGamePoint;
	friend class CEnemy_Bullet;
public:

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;	// スケール値
	CMatrix Matrix;
	bool m_bUse;
	CGamePoint_data() {
		m_Position = D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_bUse = false;
	}
};
#endif