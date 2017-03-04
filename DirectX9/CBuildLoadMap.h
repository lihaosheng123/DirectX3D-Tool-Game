/********************************************************************************
* タイトル　CBuildLoadMap.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップの数値読み込みの管理
********************************************************************************/
#ifndef _CBUILDLOADMAP_H_
#define _CBUILDLOADMAP_H_
/*******************************************************************************
マクロ定義
*******************************************************************************/
#define MAX_BUFFER		(4000)				// バッファの総数
#define MAX_WALL		(300)			//壁の設定最大値(これを超えると、bugが出る)
#define MAX_ENEMY		(50)			//敵の設定最大値(これを超えると、bugが出る)
//前方宣言
class CGameEnemy_001;
class CGameEnemy_002;
class CGameEnemy_001_data;
class CGameEnemy_002_data;
class CGameWall_001;
class CGameWall_002;
class CGameWall_001_data;
class CGameWall_002_data;
class CGameCeiling_data;
class CGameCeiling;
class CGameDoor_data;
class CGameDoor;
class CGamePoint;
class CStart;
class CEnd;
class CRobot;
/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildLoadMap
{
	//フレンドクラス
	friend class CDebugProc;
	friend class CBullet;
	friend class CGameWall_001;
	friend class CGameWall_002;
	friend class CGameEnemy_001;
	friend class CGameEnemy_002;
	friend class CGameDoor;
	friend class CEnemy_Bullet;
	friend class CGameCeiling;
	friend class CGamePoint;
	friend class BuildSetMap;
	friend class CDoor_Effect;
	friend class CStart;
	friend class CEnd;
	friend class CRobot;
public:
	// コンストラクタ・デストラクタ
	CBuildLoadMap();
	~CBuildLoadMap();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理

public:
	int i;
	FILE *pFile;						// ファイルポインタ
	char aStr[MAX_BUFFER];		// ファイルの行データ
	char aData[MAX_BUFFER];		// 格納する配列

	//位置と向きの配列
	int fPosX[MAX_WALL];
	int fPosY[MAX_WALL];
	int fPosZ[MAX_WALL];
	float fRotX[MAX_WALL];
	float fRotY[MAX_WALL];
	float fRotZ[MAX_WALL];
	//敵の軌跡配列
	D3DXVECTOR3 fPos_To[MAX_ENEMY];
	//読込
	//テスト用読み込み
	void LoadTest(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//壁001の読み込み
	void LoadWall_001(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//壁002の読み込み
	void LoadWall_002(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//敵001の読み込み
	void LoadEnemy_001(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//敵002の読み込み
	void LoadEnemy_002(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//天井板の読み込み
	void LoadCeiling(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//ドアモデルの読み込み
	void LoadDoor(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//条件モデルの読み込み
	void LoadPoint(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//プレイヤー最初位置の読み込み
	void LoadStart(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//ゲーム終了位置の読み込み
	void LoadEnd(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	//ルールを説明するのモデルの読み込み
	void LoadRobot(const char *fileName, HINSTANCE hInstance, HWND hWnd);
	HINSTANCE hInstance;
	HWND hWnd;
	//テスト用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Test[MAX_WALL];
	D3DXVECTOR3 m_Rot_Test[MAX_WALL];

	//壁001用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Wall_001[MAX_WALL];
	D3DXVECTOR3 m_Rot_Wall_001[MAX_WALL];

	//壁002用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Wall_002[MAX_WALL];
	D3DXVECTOR3 m_Rot_Wall_002[MAX_WALL];

	//敵001用座標位置、向きと軌跡の配列
	D3DXVECTOR3 m_Pos_Enemy_001[MAX_ENEMY];
	D3DXVECTOR3 m_Rot_Enemy_001[MAX_ENEMY];
	D3DXVECTOR3 m_Pos_To_Enemy_001[MAX_ENEMY];

	//敵002用座標位置、向きと軌跡の配列
	D3DXVECTOR3 m_Pos_Enemy_002[MAX_ENEMY];
	D3DXVECTOR3 m_Rot_Enemy_002[MAX_ENEMY];
	D3DXVECTOR3 m_Pos_To_Enemy_002[MAX_ENEMY];

	//天井板用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Ceiling[MAX_WALL];

	//ドアモデル用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Door[MAX_ENEMY];
	D3DXVECTOR3 m_Rot_Door[MAX_ENEMY];

	//条件モデル用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Point[MAX_ENEMY];

	//ルールを説明するのモデル用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Robot[1];
	D3DXVECTOR3 m_Rot_Robot[1];

	//プレイヤー最初位置用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_Start[1];

	//ゲーム終了用座標位置と向きの配列
	D3DXVECTOR3 m_Pos_End[1];

	//読み込みの壁001数
	int m_Wall001_num;
	//読み込みの壁002数
	int m_Wall002_num;
	//読み込みの敵001数
	int m_Enemy001_num;
	//読み込みの敵002数
	int m_Enemy002_num;
	//読み込みの天井板数
	int m_Ceiling_num;
	//読み込みのドアモデル数
	int m_Door_num;
	//読み込みの条件モデル数
	int m_Point_num;
};
#endif