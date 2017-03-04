/********************************************************************************
* タイトル　FADE
* ファイル名　fade.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/13
*
********************************************************************************/
#ifndef _FADE_H_
#define _FADE_H_
#define	TEXTURE_FADEBG_FILE		"data\\TEXTURE\\fade.png"	// 読み込むテクスチャファイル名
//マクロ定義
class CFade 
{
public:
	CFade();
	~CFade();
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
};

#endif