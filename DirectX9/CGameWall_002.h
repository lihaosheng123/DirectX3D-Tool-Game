///********************************************************************************
//* タイトル　01
//* ファイル名　CGameWall_002.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/12
//*CGameWall_002描画
//********************************************************************************/
#ifndef	_CGAMEWALL_002_H_
#define	_CGAMEWALL_002_H_
#include "CGameWall_002_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	GAME_TEXTURE_WALL_002_FILE		"data\\TEXTURE\\wall_002.jpg"	// 読み込むテクスチャファイル名
#include "CLoadMap.h"
class CLoadMap;
class CBuildLoad;
class CGameWall_002_data;
class CGameWall_002 :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
private:
	CGameWall_002_data m_data[5000];
public:
	CGameWall_002();
	~CGameWall_002();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void SetGameWall_002(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CGameWall_002* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
	int m_warp;

};
#endif