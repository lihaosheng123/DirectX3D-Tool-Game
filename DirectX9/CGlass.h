/********************************************************************************
* タイトル　01
* ファイル名　CGlass.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/17
* `CGlass描画
********************************************************************************/
#ifndef _CGLASS_H_
#define _CGLASS_H_

//マクロ定義
#define	TEXTURE_GLASS "data\\TEXTURE\\glass.png"

#define	NUM_PATTERN_GLASS			(8)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X_GLASS		(8.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y_GLASS		(1.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X_GLASS		(1.0f / TEXTURE_PATTERN_X_GLASS)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_GLASS		(1.0f / TEXTURE_PATTERN_Y_GLASS)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_GLASS	(2)						// アニメーションの切り替え間隔

#define GLASS_MAX (256)
typedef struct
{
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス。
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
	bool m_Buse;

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数
}GLASS;
class CGlass : public CScene
{
	friend class CPlayer;
	friend class CBall;
	friend class CBullet;
	friend class CFox;
	friend class CDebugProc;
	friend class Cskillbg;
public:
	CGlass();
	~CGlass();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CGlass* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	void SetGlass(D3DXVECTOR3 pos);
private:

	GLASS m_Glass[GLASS_MAX];
};

#endif