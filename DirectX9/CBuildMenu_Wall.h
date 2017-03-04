#///********************************************************************************
//* ファイル名　CBuildMenu_Wall.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*タイトル画面のmenu
//********************************************************************************/
#ifndef	_CBUILDMENU_WALL_H_
#define	_CBUILDMENU_WALL_H_

#define MENU_WALL_NUM 2
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

class CBuildMenu_Wall :public CScene
{
friend class CBuildMenu;
friend class CWall;
friend class CBuildMap;
public:


	typedef enum
	{
		BUILD_MENU_WALL_00 = 0,
		BUILD_MENU_WALL_01,
		BUILD_MENU_WALL_02,
		BUILD_MENU_WALL_MAX
	}BUILD_MENU＿WALL;

	CBuildMenu_Wall();
	~CBuildMenu_Wall();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildMenu_Wall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Build_Wall[MENU_WALL_NUM];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Build_Wall[MENU_WALL_NUM];
	bool m_bUse;
	BUILD_MENU＿WALL m_type;
};
#endif