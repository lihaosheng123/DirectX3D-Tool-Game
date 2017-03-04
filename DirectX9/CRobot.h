///********************************************************************************
//* タイトル　01
//* ファイル名　CRobot.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Robot描画
//********************************************************************************/
#ifndef	_CROBOT_H_
#define	_CROBOT_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MAX_ROBOT (10)
#define MODEL_ROBOT "data\\MODEL\\robot.x"
#define ENEMY_MOVE 2.0f;
#define ROBOT_INERTIA_MOVE (0.025f)		//慣性調整係数
class CRobot :public CScene
{
	friend class CBuildMenu;
	friend class CBuildMap;
	friend class CBuildLight;
	friend class CTrail;
public:
	enum ROBOT_TYPE
	{
		ROBOT_NORMAL = 0,			// 通常
		ROBOT_BUILDING_FRONT,
		ROBOT_BUILDING_BACK,
		ROBOT_BUILDING_LEFT,
		ROBOT_BUILDING_RIGHT,
		ROBOT_BUILDING_FALSE,
		ROBOT_MAX
	};
public:
	CRobot();
	~CRobot();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CRobot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	ROBOT_TYPE m_type;
};
#endif
