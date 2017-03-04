///********************************************************************************
//* タイトル　01
//* ファイル名　CGameDoor.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameDoor描画
//********************************************************************************/
#ifndef	_CGAMDOOR_H_
#define	_CGAMDOOR_H_
#include "CGameDoor_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
class CGameDoor_data;
class CGameDoor :public CScene
{
	friend class CLoadMap;
	friend class CEnemy_Bullet;
	friend class CEnemy_Effect;
	CGameDoor_data m_data[MAX_ENEMY];

public:

	CGameDoor();
	~CGameDoor();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void SetGameDoor(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CGameDoor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	CGameDoor_data* Get(int Index);
	float Length(D3DXVECTOR3 *Vector);
	int m_warp;
};
#endif