///********************************************************************************
//* タイトル　01
//* ファイル名　bullet.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*bullet描画
//********************************************************************************/
#ifndef	_BULLET_H_
#define	_BULLET_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define	TEXTURE_BULLET_FILE		"data\\TEXTURE\\bullet.png"	// 読み込むテクスチャファイル名
#define BULLET_MAX (256)
#define BULLET_SPEED (40.0f);
typedef struct
{
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	//D3DXVECTOR3 m_OldPosition;
	bool m_bUse;
	int m_Life;
	bool m_OneCheck;

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数
	D3DXVECTOR3 m_Vektor;
}BULLET;
class CBullet :public CScene
{
friend class CPlayer;
friend class CDebugProc;
friend class CExplosion;

public:
	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);
	float Length( D3DXVECTOR3 *Vector );
	void Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 );
	void SetBullet( D3DXVECTOR3 pos);
	BULLET* GetBullet(void);
private:
	BULLET m_Bullet[BULLET_MAX];
	int m_Num;
	int frame;

};
#endif