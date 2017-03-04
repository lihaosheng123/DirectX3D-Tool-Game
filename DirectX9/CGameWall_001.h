///********************************************************************************
//* タイトル　01
//* ファイル名　CGameWall_001.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/12
//*CGameWall_001描画
//********************************************************************************/
#ifndef	_CGAMEWALL_001_H_
#define	_CGAMEWALL_001_H_
#include "CGameWall_001_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	GAME_TEXTURE_WALL_001_FILE		"data\\TEXTURE\\wall_001.jpg"	// 読み込むテクスチャファイル名
#include "CLoadMap.h"
class CLoadMap;
class CBuildLoad;
class CGameWall_001_data;
class CGameWall_001 :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
private:
	CGameWall_001_data m_data[5000];
public:
	CGameWall_001();
	~CGameWall_001();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理 
	void SetGameWall_001(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CGameWall_001* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
	int m_warp;

};
#endif