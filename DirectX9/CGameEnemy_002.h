///********************************************************************************
//* タイトル　01
//* ファイル名　CGameEnemy_002.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameEnemy_002描画
//********************************************************************************/
#ifndef	_CGAMEENEMY_002_H_
#define	_CGAMEENEMY_002_H_
#include "CGameEnemy_002_data.h"
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

#define MODEL_ENEMY_002 "data\\MODEL\\ENEMY\\enemy_002.x"

class CGameEnemy_002_data;
class CGameEnemy_002 : public CScene
{
	friend class CLoadMap;

private:
	CGameEnemy_002_data m_data[5000];
public:
	CGameEnemy_002();
	~CGameEnemy_002();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void SetGameEnemy_002(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CGameEnemy_002* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	CGameEnemy_002_data* Get(int Index);
	float  Length(D3DXVECTOR3 *Vector);

};
#endif