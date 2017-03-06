#///********************************************************************************
//* ファイル名　CBuildMenu_Enemy.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/12/17
//*anotherのenemy
//********************************************************************************/
#ifndef	_CBUILDMENU_ENEMY_H_
#define	_CBUILDMENU_ENEMY_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define MENU_ENEMY_NUM 2//敵の種類


/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildMenu_Enemy :public CScene
{
	friend class CBuildMenu;
	friend class CEnemy;
	friend class CBuildMap;
	friend class CTrail;
public:


	typedef enum
	{
		BUILD_MENU_ENEMY_00 = 0,
		BUILD_MENU_ENEMY_01,
		BUILD_MENU_ENEMY_02,
		BUILD_MENU_ENEMY_MAX
	}BUILD_MENU＿ENEMY;

	CBuildMenu_Enemy();
	~CBuildMenu_Enemy();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildMenu_Enemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer_Build_Enemy[MENU_ENEMY_NUM];	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture_Build_Enemy[MENU_ENEMY_NUM];
	bool m_bUse;
	BUILD_MENU＿ENEMY m_type;
};
#endif#pragma once
