///********************************************************************************
//* タイトル　01
//* ファイル名　CEnemy_001.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Enemy_001描画
//********************************************************************************/
#ifndef	_CENEMY_001_H_
#define	_CENEMY_001_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MAX_ENEMY_001 (10)
#define MODEL_ENEMY_001 "data\\MODEL\\ENEMY\\enemy_001.x"
#define ENEMY_MOVE 2.0f;
#define ENEMY_001_INERTIA_MOVE (0.025f)		//慣性調整係数
class CEnemy_001:public CScene
{
friend class CBuildMenu;
friend class CBuildMap;
friend class CBuildLight;
friend class CTrail;
public:
enum ENEMY_001_TYPE
{
	ENEMY_001_NORMAL = 0,			// 通常
	ENEMY_001_BUILDING_FRONT,
	ENEMY_001_BUILDING_BACK,
	ENEMY_001_BUILDING_LEFT,
	ENEMY_001_BUILDING_RIGHT,
	ENEMY_001_BUILDING_FALSE,
	ENEMY_001_MAX
};
public:
	CEnemy_001();
	~CEnemy_001();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CEnemy_001* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	ENEMY_001_TYPE m_type;
};
#endif