///********************************************************************************
//* タイトル　01
//* ファイル名　CWall_001.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*Wall_001描画
//********************************************************************************/
#ifndef	_CWALL_001_H_
#define	_CWALL_001_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_WALL_001_FILE		"data\\TEXTURE\\wall_001.jpg"	// 読み込むテクスチャファイル名
class CWall_001 :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu_Wall_001;
	friend class CBuildMenu;
	//*************************************
	// 壁状態の種類
	//*************************************
public:
	enum WALL_001_TYPE
	{
		WALL_001_NORMAL = 0,			// 通常
		WALL_001_BUILDING_FRONT,
		WALL_001_BUILDING_BACK,
		WALL_001_BUILDING_LEFT,
		WALL_001_BUILDING_RIGHT,
		WALL_001_BUILDING_FALSE,
		WALL_001_MAX
	};
public:
	CWall_001();
	~CWall_001();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CWall_001* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);

private:

	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	WALL_001_TYPE m_type;
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	bool m_use;
};
#endif