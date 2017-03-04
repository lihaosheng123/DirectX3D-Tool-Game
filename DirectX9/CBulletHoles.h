///********************************************************************************
//* タイトル　01
//* ファイル名　bullet.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*bullet描画
//********************************************************************************/
#ifndef	_BULLETHOLES_H_
#define	_BULLETHOLES_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define	TEXTURE_BULLETHOLES_FILE		"data\\TEXTURE\\bulletholes.png"	// 読み込むテクスチャファイル名
#define BULLETHOLES_MAX (256)

#define	NUM_PATTERN_BULLETHOLES			(1)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X_BULLETHOLES		(1.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y_BULLETHOLES		(1.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X_BULLETHOLES		(1.0f / TEXTURE_PATTERN_X_BULLETHOLES)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_BULLETHOLES		(1.0f / TEXTURE_PATTERN_Y_BULLETHOLES)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_BULLETHOLES	(5)						// アニメーションの切り替え間隔
typedef struct
{
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_OldPosition;
	bool m_bUse;
	int m_Life;
	bool m_OneCheck;

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.

}BULLETHOLES;
class CBulletHoles :public CScene
{
friend class CPlayer;
friend class CDebugProc;
friend class CExplosion;
public:
	CBulletHoles();
	~CBulletHoles();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBulletHoles* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);
	float Length( D3DXVECTOR3 *Vector );
	void Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 );
	void SetBulletHoles( D3DXVECTOR3 pos,D3DXVECTOR3 rot);

private:
	BULLETHOLES m_BulletHoles[BULLETHOLES_MAX];


};
#endif