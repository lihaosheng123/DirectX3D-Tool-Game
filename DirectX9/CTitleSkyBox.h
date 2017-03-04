///********************************************************************************
//* タイトル　01
//* ファイル名　CTitleSkyBox.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/04/28
//* CTitleSkyBox
//********************************************************************************/
#ifndef	_CTITLESKYBOX_H_
#define	_CTITLESKYBOX_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

class CTitleSkyBox :public CScene
{
public:
	CTitleSkyBox();
	~CTitleSkyBox();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitleSkyBox* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture[6];
};
#endif