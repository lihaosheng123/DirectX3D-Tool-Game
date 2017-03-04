///********************************************************************************
//* ファイル名　CBuildMenu.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*Build画面のmenu
//********************************************************************************/
#ifndef	_CBUILDMENU_H_
#define	_CBUILDMENU_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define MENU_NUM 8		//menu数

/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildMenu :public CScene
{
	//フレンドクラス
	friend class CBuildMap;
	friend class CBuildMenu_Wall;
	friend class CBuildMenu_Enemy;
	friend class CBuildMenu_Prop;
	friend class CBuildMenu_Another;
public:
	//Menuの種類
	typedef enum
	{
		BUILD_MENU_WALL = 0,//壁
		BUILD_MENU_ENEMY,//敵
		BUILD_MENU_LIGHT,//ライト
		BUILD_MENU_CEILING,//天井板
		BUILD_MENU_PROP,//道具
		BUILD_MENU_ANOTHER,//他
		BUILD_MENU_GAMESTART,	//ゲーム開始(画面遷移)
		BUILD_MENU_BACKTITLE,	//タイトル画面遷移
		BUILD_MENU_MAX
	}BUILD_MENU;

	// コンストラクタ・デストラクタ
	CBuildMenu();
	~CBuildMenu();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildMenu* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Build[MENU_NUM];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Build[MENU_NUM];//テクスチャのポインタ
	BUILD_MENU m_type;	//状態
};
#endif