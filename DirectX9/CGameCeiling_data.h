///********************************************************************************
//* タイトル　01
//* ファイル名　CGameCeiling_data.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/10
//* GameCeilingdata
//********************************************************************************/
#ifndef	_CGAMECEILING_DATA_H_
#define	_CGAMECEILING_DATA_H_
#include "scene.h"
//**************
//***********************************************************************************
//* マクロ定義*************************************************************/
//マクロ定義

class CGameCeiling_data
{
	friend class CLoadMap;
public:

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;	// スケール値
	CMatrix Matrix;
	bool m_bUse;

	CGameCeiling_data() {
		m_Position = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_bUse = false;
	}
};
#endif