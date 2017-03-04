///********************************************************************************
//* タイトル　01
//* ファイル名　CWall_002.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*Wall_002描画
//********************************************************************************/
#ifndef	_CWALL_002_H_
#define	_CWALL_002_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_WALL_002_FILE		"data\\TEXTURE\\wall_002.jpg"	// 読み込むテクスチャファイル名
class CWall_002 :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu_Wall_002;
	friend class CBuildMenu;
	//*************************************
	// 壁状態の種類
	//*************************************
public:
	enum WALL_002_TYPE
	{
		WALL_002_NORMAL = 0,			// 通常
		WALL_002_BUILDING_FRONT,
		WALL_002_BUILDING_BACK,
		WALL_002_BUILDING_LEFT,
		WALL_002_BUILDING_RIGHT,
		WALL_002_BUILDING_FALSE,
		WALL_002_MAX
	};
public:
	CWall_002();
	~CWall_002();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CWall_002* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);

private:

	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	WALL_002_TYPE m_type;
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	bool m_use;

};
#endif