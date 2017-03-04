///********************************************************************************
//* タイトル　01
//* ファイル名　CCeiling.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*Ceiling描画
//********************************************************************************/
#ifndef	_CCEILING_H_
#define	_CCEILING_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_CEILING_FILE		"data\\TEXTURE\\ceiling.jpg"	// 読み込むテクスチャファイル名
class CCeiling :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu_Ceiling;
	friend class CBuildMenu;
public:
	enum CEILING_TYPE
	{
		CEILING_NORMAL = 0,			// 通常
		CEILING_BUILDING_TRUE,
		CEILING_BUILDING_FALSE,
		CEILING_MAX
	};
public:
	CCeiling();
	~CCeiling();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CCeiling* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);

private:

	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	bool m_use;
	CEILING_TYPE m_type;

};
#endif