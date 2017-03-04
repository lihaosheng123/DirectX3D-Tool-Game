/********************************************************************************
* タイトル　01
* ファイル名　CSpark.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/17
* `CSpark描画
********************************************************************************/
#ifndef _CSPARK_H_
#define _CSPARK_H_

//マクロ定義
#define	TEXTURE_SPARK "data\\TEXTURE\\spark.png"

#define	NUM_PATTERN_SPARK			(4)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X_SPARK		(4.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y_SPARK		(1.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X_SPARK		(1.0f / TEXTURE_PATTERN_X_SPARK)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_SPARK		(1.0f / TEXTURE_PATTERN_Y_SPARK)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_SPARK	(2)						// アニメーションの切り替え間隔

#define SPARK_MAX (256)
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
}SPARK;
class CSpark : public CScene
{
	friend class CPlayer;
	friend class CBall;
	friend class CBullet;
	friend class CFox;
	friend class CDebugProc;
	friend class Cskillbg;
public:
	CSpark();
	~CSpark();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CSpark* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	void SetSpark(D3DXVECTOR3 pos);
private:

	SPARK m_Spark[SPARK_MAX];
};

#endif