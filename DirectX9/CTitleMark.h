///********************************************************************************
//* ファイル名　CTitleMark.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*タイトル画面のmenuのmark
//********************************************************************************/
#ifndef	_CTITLEMARK_H_
#define	_CTITLEMARK_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define	TEXTURE_TITLEMARK "data\\TEXTURE\\titlemark.png"

class CTitleMark :public CScene
{
friend class CTitle;
friend class CTitleMenu;
public:

	typedef enum
	{
		TITLE_MENU_START = 0,
		TITLE_MENU_BUILD,
		TITLE_MENU_END,
		TITLE_MENU_MAX
	}TITLE_MENU;

	CTitleMark();
	~CTitleMark();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitleMark* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	TITLE_MENU m_type;
	bool m_bUse;
	D3DXCOLOR col;
	float num;
	bool m_colMove;
};
#endif