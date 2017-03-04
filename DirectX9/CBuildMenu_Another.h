#///********************************************************************************
//* ファイル名　CBuildMenu_Another.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*anotherのmenu
//********************************************************************************/
#ifndef	_CBUILDMENU_ANOTHER_H_
#define	_CBUILDMENU_ANOTHER_H_

#define MENU_ANOTHER_NUM 3		//anotherのmenu数
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildMenu_Another :public CScene
{
	//フレンドクラス
	friend class CBuildMenu;
	friend class CAnother;
	friend class CBuildMap;
public:
	typedef enum
	{
		BUILD_MENU_ANOTHER_00 = 0,
		BUILD_MENU_ANOTHER_START,
		BUILD_MENU_ANOTHER_END,
		BUILD_MENU_ANOTHER_PRESENT,
		BUILD_MENU_ANOTHER_MAX
	}BUILD_MENU＿ANOTHER;

	CBuildMenu_Another();
	~CBuildMenu_Another();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildMenu_Another* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Build_Another[MENU_ANOTHER_NUM];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Build_Another[MENU_ANOTHER_NUM];//テクスチャのポインタ
	bool m_bUse;
	BUILD_MENU＿ANOTHER m_type;
};
#endif
