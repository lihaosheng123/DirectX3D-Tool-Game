///********************************************************************************
//* タイトル　01
//* ファイル名　CGameCeiling.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/12
//*CGameCeiling描画
//********************************************************************************/
#ifndef	_CGAMECEILING_H_
#define	_CGAMECEILING_H_
#include "CGameCeiling_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	GAME_TEXTURE_CEILING_FILE		"data\\TEXTURE\\ceiling.jpg"	// 読み込むテクスチャファイル名
#include "CLoadMap.h"
class CLoadMap;
class CBuildLoad;
class CGameCeiling_data;
class CGameCeiling :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CPlayer;
public:
	CGameCeiling();
	~CGameCeiling();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void SetGameCeiling(D3DXVECTOR3 pos);
	static CGameCeiling* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
	CGameCeiling_data m_data[MAX_WALL];
	int m_warp;

};
#endif