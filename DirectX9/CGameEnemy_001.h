///********************************************************************************
//* タイトル　01
//* ファイル名　CGameEnemy_001.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameEnemy_001描画
//********************************************************************************/
#ifndef	_CGAMEENEMY_001_H_
#define	_CGAMEENEMY_001_H_
#include "CGameEnemy_001_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

#define MODEL_ENEMY_001 "data\\MODEL\\ENEMY\\enemy_001.x"

class CGameEnemy_001_data;
class CGameEnemy_001 :public CScene
{ 
	friend class CLoadMap;
	friend class CEnemy_Bullet;
	friend class CEnemy_Effect;
	CGameEnemy_001_data m_data[MAX_ENEMY];

public:

	CGameEnemy_001();
	~CGameEnemy_001();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void SetGameEnemy_001(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CGameEnemy_001* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	CGameEnemy_001_data* Get(int Index);
	float Length(D3DXVECTOR3 *Vector);
};
#endif