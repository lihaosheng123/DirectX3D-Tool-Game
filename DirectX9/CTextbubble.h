///********************************************************************************
//* タイトル　01
//* ファイル名　CTextbubble.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*Textbubble描画
//********************************************************************************/
#ifndef	_CTEXTBUBBLE_H_
#define	_CTEXTBUBBLE_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_TEXTBUBBLE_FILE		"data\\TEXTURE\\textbubble.png"	// 読み込むテクスチャファイル名
class CTextbubble :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu;

public:
	CTextbubble();
	~CTextbubble();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTextbubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);

private:

	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	bool m_use;
};
#endif