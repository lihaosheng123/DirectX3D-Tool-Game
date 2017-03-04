///********************************************************************************
//* タイトル　01
//* ファイル名　CEnemy_002.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Enemy_002描画
//********************************************************************************/
#ifndef	_CENEMY_002_H_
#define	_CENEMY_002_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MAX_ENEMY_002 (10)
#define MODEL_ENEMY_002 "data\\MODEL\\ENEMY\\enemy_002.x"
#define ENEMY_MOVE 2.0f;
#define ENEMY_002_INERTIA_MOVE (0.025f)		//慣性調整係数
class CEnemy_002 :public CScene
{
	friend class CBuildMenu;
	friend class CBuildMap;
	friend class CTrail;
public:
	enum ENEMY_002_TYPE
	{
		ENEMY_002_NORMAL = 0,			// 通常
		ENEMY_002_BUILDING_FRONT,
		ENEMY_002_BUILDING_BACK,
		ENEMY_002_BUILDING_LEFT,
		ENEMY_002_BUILDING_RIGHT,
		ENEMY_002_BUILDING_FALSE,
		ENEMY_002_MAX
	};
public:
	CEnemy_002();
	~CEnemy_002();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CEnemy_002* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	ENEMY_002_TYPE m_type;
};
#endif