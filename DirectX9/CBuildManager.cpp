/********************************************************************************
* タイトル　CBUILDMANAGER
* ファイル名　CBuildManager.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/19
*Buildのマネジャー
********************************************************************************/
#include "CBuildManager.h"
//------------------------------------------------------------------------------
//	関数名:	CBuildManager::CBuildManager
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBuildManager::CBuildManager()
{
	CManager *manager = GetManager();
	//Buildモードオン
	manager->m_Build = true;
	//マウス描画オン
	manager->m_MouseDraw = true;
}

//------------------------------------------------------------------------------
//	関数名:	CBuildManager::~CBuildManager
//	引数:	なし
//	戻り値:	CBuildManager
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBuildManager::~CBuildManager()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CBuildManager::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CBuildManager::Init(void)
{
	//ライトクラスのインスタンスと初期化
	m_Light = new CBuildLight;
	m_Light->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//カメラクラスのインスタンスと初期化
	m_BuildCamera = new CBuildCamera;
	m_BuildCamera->Init();

	//マップの読み込みクラスのインスタンスと初期化
	m_BuildLoadMap = new CBuildLoadMap;
	m_BuildLoadMap->Init();
	/*リスト構造描画開始*/
	//天井板描画用
	m_GameCeiling = CGameCeiling::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_CEILING_FILE);
	//壁001描画用
	m_GameWall_001 = CGameWall_001::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, GAME_TEXTURE_WALL_001_FILE);
	//壁002描画用
	m_GameWall_002 = CGameWall_002::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, GAME_TEXTURE_WALL_002_FILE);
	//敵001描画用
	m_GameEnemy_001 = CGameEnemy_001::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_001);
	//敵002描画用
	m_GameEnemy_002 = CGameEnemy_002::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
	//ドアモデル描画用
	m_GameDoor = CGameDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
	//条件モデル描画用
	m_GamePoint = CGamePoint::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_POINT);
	//フィールド描画用
	m_Field = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, MESHFIELD_TEXTURE_FILE00);
	//座標系描画用
	m_axis = Caxis::Create(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7000.0f, 7000.0f, TEXTURE_AXIS_FILE);
	//2DMEnu(main)描画用
	m_BuildMenu = CBuildMenu::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 90.0f, "NULL");
	//2DMEnu(wall)描画用
	m_BuildMenu_Wall = CBuildMenu_Wall::Create(D3DXVECTOR3(130.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, "NULL");
	//2DMEnu(enemy)描画用
	m_BuildMenu_Enemy = CBuildMenu_Enemy::Create(D3DXVECTOR3(130.0f, 130.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 60.0f, "NULL");
	//2DMEnu(prop)描画用
	m_BuildMenu_Prop  = CBuildMenu_Prop::Create(D3DXVECTOR3(150.0f, 370.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 100.0f, "NULL");
	//2DMEnu(another)描画用
	m_BuildMenu_Another = CBuildMenu_Another::Create(D3DXVECTOR3(150.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 100.0f, "NULL");
	//Build用(wall001)描画用
	m_Wall_001[0] = CWall_001::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_001_FILE);
	//Build用(wall002)描画用
	m_Wall_002[0] = CWall_002::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_002_FILE);
	//Build用(enemy001)描画用
	m_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_001);
	//Build用(enemy002)描画用
	m_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
	//Build用(ceiling(天井板))描画用
	m_Ceiling[0] = CCeiling::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_CEILING_FILE);
	//Build用(Trail(敵の軌跡))描画用
	m_Trail = CTrail::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 30.0f, TEXTURE_TRAIL_FILE);
	//Build用(door)描画用
	m_Door = CDoor::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
	//Build用(point)描画用
	m_Point = CPoint::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_POINT);
	//Build用(start)描画用
	m_Start = CStart::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_START);
	//Build用(end)描画用
	m_End = CEnd::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, "NULL");
	//Build用(robot)描画用
	m_Robot = CRobot::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ROBOT);
	//Build用(BuildImage)描画用
	m_BuildImage = CBuildImage::Create(D3DXVECTOR3(1120.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 300.0f, TEXTURE_BUILDIMAGE_FILE);
	/*リスト構造描画終了*/
	//存在するのデータ入力のインスタンスと初期化
	m_BuildSetMap = new BuildSetMap;
	m_BuildSetMap->Init();

	//マックの作成と入力インスタンスと初期化
	m_BuildMap = new CBuildMap;
	m_BuildMap->Init();


}

//------------------------------------------------------------------------------
//	関数名:	void CBuildManager::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CBuildManager::Uninit(void)
{
	//カメラクラスの削除
	m_BuildCamera->Uninit();
	delete m_BuildCamera;

	//ライトクラスの削除
	delete m_Light;

	//マックの作成と入力クラスの削除
	m_BuildMap->Uninit();
	delete m_BuildMap;

	//マップの読み込みクラスの削除
	m_BuildLoadMap->Uninit();
	delete m_BuildLoadMap;

	//存在するのデータ入力クラスの削除
	delete m_BuildSetMap;

	/*リスト構造の削除*/
	CScene::UninitAll();



}

//------------------------------------------------------------------------------
//	関数名:	void CBuildManager::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理

//------------------------------------------------------------------------------
void CBuildManager::Update(void)
{
	CManager *manager = GetManager();
	CSceneInput *m_Input = manager->GetInput();

	//ライトクラスの更新
	m_Light->Update();

	//カメラクラスの更新
	m_BuildCamera->Update();

	//マップの読み込みクラスの更新
	m_BuildLoadMap->Update();

	/*リスト構造の更新*/
	CScene::UpdateAll();

	//マックの作成と入力クラスの更新
	m_BuildMap->Update(hInstance,hWnd);
}

//------------------------------------------------------------------------------
//	関数名:	void CBuildManager::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CBuildManager::Draw(void)
{
	/*リスト構造の描画*/
	CScene::DrawAll();
	
}
CBuildLoadMap* CBuildManager::GetBuildLoadMap(void)
{
	return m_BuildLoadMap;
}
CBuildCamera* CBuildManager::GetBuildCamera(void)
{
	return m_BuildCamera;
}
CBuildMap* CBuildManager::GetBuildMap(void)
{
	return m_BuildMap;
}
CBuildLight* CBuildManager::GetBuildLight(void)
{
	return m_Light;
}
CBuildMenu_Wall* CBuildManager::GetBuildMenu_Wall(void)
{
	return m_BuildMenu_Wall;
}
CBuildMenu_Enemy* CBuildManager::GetBuildMenu_Enemy(void)
{
	return m_BuildMenu_Enemy;
}
CBuildMenu* CBuildManager::GetBuildMenu(void)
{
	return m_BuildMenu;
}
CEnemy_001* CBuildManager::GetEnemy_001(int Index)
{
	return m_Enemy_001[Index];
}
CEnemy_002* CBuildManager::GetEnemy_002(int Index)
{
	return m_Enemy_002[Index];
}
CWall_001* CBuildManager::GetBuildWall_001(int Index)
{
	return m_Wall_001[Index];
}
CWall_002* CBuildManager::GetBuildWall_002(int Index)
{
	return m_Wall_002[Index];
}
CTrail* CBuildManager::GetBuildTrail(void)
{
	return m_Trail;
}
CGameWall_001* CBuildManager::GetGameWall_001(void)
{
	return m_GameWall_001;
}
CGameWall_002* CBuildManager::GetGameWall_002(void)
{
	return m_GameWall_002;
}
CGameEnemy_001* CBuildManager::GetGameEnemy_001(void)
{
	return m_GameEnemy_001;
}
CGameEnemy_002* CBuildManager::GetGameEnemy_002(void)
{
	return m_GameEnemy_002;
}
CCeiling* CBuildManager::GetCeiling(int Index)
{
	return m_Ceiling[Index];
}
CGameCeiling* CBuildManager::GetGameCeiling(void)
{
	return m_GameCeiling;
}
CGameDoor* CBuildManager::GetGameDoor(void)
{
	return m_GameDoor;
}
CDoor* CBuildManager::GetDoor(void)
{
	return m_Door;
}
CBuildMenu_Prop* CBuildManager::GetBuildMenu_Prop(void)
{
	return m_BuildMenu_Prop;
}
CPoint* CBuildManager::GetPoint(void)
{
	return m_Point;
}
CStart* CBuildManager::GetStart(void)
{
	return m_Start;
}
CEnd* CBuildManager::GetEnd(void)
{
	return m_End;
}
CGamePoint* CBuildManager::GetGamePoint(void)
{
	return m_GamePoint;
}
CBuildMenu_Another* CBuildManager::GetBuildMenu_Another(void)
{
	return m_BuildMenu_Another;
}
CRobot* CBuildManager::GetRobot(void)
{
	return m_Robot;
}