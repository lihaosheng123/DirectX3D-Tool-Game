#///********************************************************************************
//* ファイル名　CBuildMenu_Prop.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*prop
//********************************************************************************/
#ifndef	_CBUILDMENU_PROP_H_
#define	_CBUILDMENU_PROP_H_

#define MENU_PROP_NUM 2
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

class CBuildMenu_Prop :public CScene
{
	friend class CBuildMenu;
	friend class CProp;
	friend class CBuildMap;
public:


	typedef enum
	{
		BUILD_MENU_PROP_00 = 0,
		BUILD_MENU_PROP_DOOR,
		BUILD_MENU_PROP_POINT,
		BUILD_MENU_PROP_MAX
	}BUILD_MENU＿PROP;

	CBuildMenu_Prop();
	~CBuildMenu_Prop();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildMenu_Prop* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Build_Prop[MENU_PROP_NUM];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Build_Prop[MENU_PROP_NUM];
	bool m_bUse;
	BUILD_MENU＿PROP m_type;
};
#endif
