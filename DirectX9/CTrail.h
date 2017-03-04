//********************************************************************************
//* タイトル　01
//* ファイル名　CTrail.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/12
//*Trail描画
//********************************************************************************/
#ifndef	_CTRAIL_H_
#define	_CTRAIL_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_TRAIL_FILE		"data\\TEXTURE\\trail.png"	// 読み込むテクスチャファイル名

class CTrail :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu_Trail;
	friend class CBuildMenu;
public:
	enum TRAIL_TYPE
	{
		TRAIL_NORMAL = 0,			// 通常
		TRAIL_BUILDING_FRONT,
		TRAIL_BUILDING_BACK,
		TRAIL_BUILDING_LEFT,
		TRAIL_BUILDING_RIGHT,
		TRAIL_BUILDING_FALSE,
		TRAIL_MAX
	};
public:
	CTrail();
	~CTrail();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTrail* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
private:
	int m_Changge;
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数
	D3DXVECTOR3 m_NumCheck;
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	int Check;
	TRAIL_TYPE m_type;
};
#endif