		///********************************************************************************
//* タイトル　01
//* ファイル名　portal.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Portal描画
//********************************************************************************/
#ifndef	_CPORTAL_H_
#define	_CPORTAL_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_PORTAL_TEXTURE "data\\MODEL\\portal.x"

class CPortal : public CSceneX
{
friend class CBall;
friend class CGun;
friend class CBullet;
friend class CGame;
public:
	CPortal();
	~CPortal();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CPortal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数
	float Length( D3DXVECTOR3 *Vector );
	void Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 );
private:
	bool m_Buse;
	bool m_OneCheck;
};
#endif