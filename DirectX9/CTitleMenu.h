///********************************************************************************
//* ファイル名　CTitleMenu.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*タイトル画面のmenu
//********************************************************************************/
#ifndef	_CTITLEMENU_H_
#define	_CTITLEMENU_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

class CTitleMenu :public CScene
{
	friend class CTitleMark;
	friend class CTitle;
public:
	CTitleMenu();
	~CTitleMenu();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitleMenu* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Title[3];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Title[3];
	int alpha;
	bool m_bUse;
};
#endif