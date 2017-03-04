///********************************************************************************
//* タイトル　01
//* ファイル名　CEnemy_Effect.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/20
//*敵のeffect描画
//********************************************************************************/
#ifndef	_CENEMY_EFFECT_H_
#define	_CENEMY_EFFECT_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define	NUM_PATTERN_EFFECT_ENEMY			(8)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X_EFFECT_ENEMY		(8.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y_EFFECT_ENEMY		(1.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X_EFFECT_ENEMY		(1.0f / TEXTURE_PATTERN_X_EFFECT_ENEMY)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_EFFECT_ENEMY		(1.0f / TEXTURE_PATTERN_Y_EFFECT_ENEMY)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_EFFECT_ENEMY	(4)						// アニメーションの切り替え間隔
#define	TEXTURE_ENEMY_EFFECT_FILE		"data\\TEXTURE\\enemy_effect.png"	// 読み込むテクスチャファイル名
#define ENEMY_EFFECT_MAX (100)
#include "scene.h"
typedef struct
{
	D3DXVECTOR3 m_scl;		//スケール値
	bool m_bUse;
	int m_Life;

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
	CMatrix m_Matrix;
}ENEMY_EFFECT;
class CEnemy_Effect :public CScene
{
	friend class CPlayer;
	friend class CDebugProc;
	friend class CExplosion;
	friend class CGameEnemy_001;
public:
	CEnemy_Effect();
	~CEnemy_Effect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CEnemy_Effect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
	void SetEffect(D3DXVECTOR3 pos);
	ENEMY_EFFECT* GetEnemy_Effect(void);
private:
	ENEMY_EFFECT m_Enemy_Effect[ENEMY_EFFECT_MAX];
	int cnt;
};
#endif