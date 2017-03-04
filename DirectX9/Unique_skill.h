/********************************************************************************
* タイトル　01
* ファイル名　Unique_skill.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/17
* `Unique_skill描画
********************************************************************************/
#ifndef _UNIQUE_SKILL_H_
#define _UNIQUE_SKILL_H_

//マクロ定義
#define	TEXTURE_UNIQUE_SKILL "data\\TEXTURE\\skull.png"

#define	NUM_PATTERN_UNIQUE_SKILL			(9)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X_UNIQUE_SKILL		(20.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y_UNIQUE_SKILL		(11.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X_UNIQUE_SKILL		(1.0f / TEXTURE_PATTERN_X_UNIQUE_SKILL)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_UNIQUE_SKILL		(1.0f / TEXTURE_PATTERN_Y_UNIQUE_SKILL)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_UNIQUE_SKILL	(10)						// アニメーションの切り替え間隔

#define UNIQUE_SKILL_MAX (1)
typedef struct
{
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス。

	bool m_Buse;

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数
}UNIQUE_SKILL;
class CUnique_skill : public CScene
{
	friend class CPlayer;
	friend class CBall;
	friend class CBullet;
	friend class CFox;
	friend class CDebugProc;
	friend class Cskillbg;
public:
	CUnique_skill();
	~CUnique_skill();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CUnique_skill* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	void SetUnique_skill(D3DXVECTOR3 pos);
private:
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
	UNIQUE_SKILL m_Unique_skill[UNIQUE_SKILL_MAX];
	bool m_bgUse;
	int m_frame;
	bool m_CheckUse;
	Cskillbg *m_skillbg;
};

#endif