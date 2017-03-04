/********************************************************************************
* ファイル名　CBuildMap.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップ管理、読み込み、ファイル作成
********************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "scene3D.h"
#include "manager.h"
#include "scene.h"
#include "CBuildMap.h"
/*******************************************************************************
マクロ定義
*******************************************************************************/

//------------------------------------------------------------------------------
//	関数名:	CBuildMap::CBuildMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBuildMap::CBuildMap()
{
	//データの読み込み初期化
	PosX = 0;
	PosY = 0;
	PosZ = 0;
	RotX = 0;
	RotY = 0;
	RotZ = 0;
	m_Trail_PosX = 0;
	m_Trail_PosY = 0;
	m_Trail_PosZ = 0;

	/*リスト構造のモデル描画(確保用)*/
	//敵001描画用
	p_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_001);
	//敵002描画用
	p_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
	//ドアモデル描画用
	p_Door[0] = CDoor::Create(D3DXVECTOR3(0.f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
	//条件モデル描画用
	p_Point[0] = CPoint::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_POINT);
	//Build用(start)描画用
	p_Start[0] = CStart::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_START);
	//Build用(end)描画用
	p_End[0] = CEnd::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, "NULL");
	//Build用(robot)描画用
	p_Robot[0] = CRobot::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ROBOT);
}

//------------------------------------------------------------------------------
//	関数名:	CBuildMap::~CBuildMap
//	引数:	なし
//	戻り値:	
//	説明:	コンストラクタ
//------------------------------------	------------------------------------------
CBuildMap::~CBuildMap()
{

}

/*******************************************************************************
関数名：	HRESULT CBuildMap::Init
戻り値：	HRESULT
引数：		void
説明：		CBuildMapの初期化処理
**********	*********************************************************************/
void CBuildMap::Init(void)
{
	CManager *manager = GetManager();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildMap *m_BuildMap = BuildManager->GetBuildMap();
	CSceneInput *m_Input = manager->GetInput();
	CSceneMouse *m_Mouse = manager->GetMouse();
	CRenderer *renderer = manager->GetRenderer();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CBuildMenu_Enemy *m_BuildMenu_Enemy = BuildManager->GetBuildMenu_Enemy();
	CWall_001 *m_Wall_001 = BuildManager->GetBuildWall_001(0);
	CWall_002 *m_Wall_002 = BuildManager->GetBuildWall_002(0);
	CEnemy_001 *m_Enemy_001 = BuildManager->GetEnemy_001(0);
	CEnemy_002 *m_Enemy_002 = BuildManager->GetEnemy_002(0);
	CBuildMenu *m_BuildMenu = BuildManager->GetBuildMenu();
	CBuildLight *m_BuildLight = BuildManager->GetBuildLight();
	CCeiling *m_Ceiling = BuildManager->GetCeiling(0);
	CDoor *m_Door = BuildManager->GetDoor();
	CPoint *m_Point = BuildManager->GetPoint();
	CStart *m_Start = BuildManager->GetStart();
	CEnd *m_End = BuildManager->GetEnd();
	CRobot *m_Robot = BuildManager->GetRobot();

	//使用しないの場合、初期化FALSE
	m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
	m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
	m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
	m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
	m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
	m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
	m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
	m_Start->m_type = m_Start->START_BUILDING_FALSE;
	m_End->m_type = m_End->END_BUILDING_FALSE;
	m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;
}

/*******************************************************************************
関数名：	void CBuildMap::Uninit
戻り値：	void
引数：		void
説明：		CBuildMapの終了処理
*******************************************************************************/
void CBuildMap::Uninit(void)
{

}

/*******************************************************************************
関数名：	void CBuildMap::Update
戻り値：	void
引数：		void
説明：		CBuildMapの更新処理
*******************************************************************************/
void CBuildMap::Update(HINSTANCE hInstance, HWND hWnd)
{
	CManager *manager = GetManager();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildMap *m_BuildMap = BuildManager->GetBuildMap();
	CSceneInput *m_Input = manager->GetInput();
	CSceneMouse *m_Mouse = manager->GetMouse();
	CRenderer *renderer = manager->GetRenderer();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CBuildMenu_Enemy *m_BuildMenu_Enemy = BuildManager->GetBuildMenu_Enemy();
	CWall_001 *m_Wall_001 = BuildManager->GetBuildWall_001(0);
	CWall_002 *m_Wall_002 = BuildManager->GetBuildWall_002(0);
	CEnemy_001 *m_Enemy_001 = BuildManager->GetEnemy_001(0);
	CEnemy_002 *m_Enemy_002 = BuildManager->GetEnemy_002(0);
	CBuildMenu *m_BuildMenu = BuildManager->GetBuildMenu();
	CBuildLight *m_BuildLight = BuildManager->GetBuildLight();
	CTrail *m_Trail = BuildManager->GetBuildTrail();
	CCeiling *m_Ceiling = BuildManager->GetCeiling(0);
	CDoor *m_Door = BuildManager->GetDoor();
	CBuildMenu_Prop *m_BuildMenu_Prop = BuildManager->GetBuildMenu_Prop();
	CPoint *m_Point = BuildManager->GetPoint();
	CStart *m_Start = BuildManager->GetStart();
	CBuildMenu_Another *m_BuildMenu_Another = BuildManager->GetBuildMenu_Another();
	CEnd *m_End = BuildManager->GetEnd();
	CRobot *m_Robot = BuildManager->GetRobot();

	/*紹介robotの処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_ANOTHER
	//Another MenuのMenu:BUILD_MENU_ANOTHER_PRESENT
	if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ANOTHER && m_BuildMenu_Another->m_type == m_BuildMenu_Another->BUILD_MENU_ANOTHER_PRESENT)
	{
		//この以外のモノ全部FALSE
		m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
		m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
		m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
		m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
		m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
		m_Start->m_type = m_Start->START_BUILDING_FALSE;
		m_End->m_type = m_End->END_BUILDING_FALSE;
		//「I」ボタンが押す、
		//状態：ROBOT_BUILDING_FRONT（↑）
		if (m_Robot->m_type != m_Robot->ROBOT_BUILDING_FRONT && m_Input->GetKeyboardTrigger(DIK_I))
		{
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_FRONT;
		}
		//	マウスの左ボタン押す
		if (m_Robot->m_type == m_Robot->ROBOT_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置と向きをポインタから渡す
			p_Robot[0]->m_Position = m_Robot->m_Position;
			p_Robot[0]->m_Rotation = m_Robot->m_Rotation;

			//データの保存
			PosX = (int)p_Robot[i]->m_Position.x;
			PosY = (int)p_Robot[i]->m_Position.y;
			PosZ = (int)p_Robot[i]->m_Position.z;
			RotX = p_Robot[i]->m_Rotation.x;
			RotY = p_Robot[i]->m_Rotation.y;
			RotZ = p_Robot[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}

		//「K」ボタンが押す、
		//状態：ROBOT_BUILDING_BACK（↓）
		if (m_Robot->m_type != m_Robot->ROBOT_BUILDING_BACK &&m_Input->GetKeyboardTrigger(DIK_K))
		{
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_BACK;
		}

		//	マウスの左ボタン押す
		if (m_Robot->m_type == m_Robot->ROBOT_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置と向きをポインタから渡す
			p_Robot[0]->m_Position = m_Robot->m_Position;
			p_Robot[0]->m_Rotation = m_Robot->m_Rotation;

			//データの保存
			PosX = (int)p_Robot[i]->m_Position.x;
			PosY = (int)p_Robot[i]->m_Position.y;
			PosZ = (int)p_Robot[i]->m_Position.z;
			RotX = p_Robot[i]->m_Rotation.x;
			RotY = p_Robot[i]->m_Rotation.y;
			RotZ = p_Robot[i]->m_Rotation.z;


			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}

		//「J」ボタンが押す、
		//状態：ROBOT_BUILDING_LEFT（←）
		if (m_Robot->m_type != m_Robot->ROBOT_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
		{
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_LEFT;
		}

		//	マウスの左ボタン押す
		if (m_Robot->m_type == m_Robot->ROBOT_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置と向きをポインタから渡す
			p_Robot[0]->m_Position = m_Robot->m_Position;
			p_Robot[0]->m_Rotation = m_Robot->m_Rotation;
			//データの保存
			PosX = (int)p_Robot[i]->m_Position.x;
			PosY = (int)p_Robot[i]->m_Position.y;
			PosZ = (int)p_Robot[i]->m_Position.z;
			RotX = p_Robot[i]->m_Rotation.x;
			RotY = p_Robot[i]->m_Rotation.y;
			RotZ = p_Robot[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}

		//「L」ボタンが押す、
		//状態：ROBOT_BUILDING_RIGHT（→）
		if (m_Robot->m_type != m_Robot->ROBOT_BUILDING_RIGHT && m_Input->GetKeyboardTrigger(DIK_L))
		{
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_RIGHT;
		}

		//	マウスの左ボタン押す
		if (m_Robot->m_type == m_Robot->ROBOT_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置と向きをポインタから渡す
			p_Robot[0]->m_Position = m_Robot->m_Position;
			p_Robot[0]->m_Rotation = m_Robot->m_Rotation;
			//データの保存
			PosX = (int)p_Robot[i]->m_Position.x;
			PosY = (int)p_Robot[i]->m_Position.y;
			PosZ = (int)p_Robot[i]->m_Position.z;
			RotX = p_Robot[i]->m_Rotation.x;
			RotY = p_Robot[i]->m_Rotation.y;
			RotZ = p_Robot[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}
	}
	/*紹介robotの処理終了*/

	/*startの処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_ANOTHER
	//Another MenuのMenu:BUILD_MENU_ANOTHER_START
	if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ANOTHER && m_BuildMenu_Another->m_type == m_BuildMenu_Another->BUILD_MENU_ANOTHER_START)
	{
		//この以外のモノ全部FALSE
		m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
		m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
		m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
		m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
		m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
		m_Start->m_type = m_Start->START_BUILDING_TRUE;
		m_End->m_type = m_End->END_BUILDING_FALSE;
		m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;

		//	マウスの左ボタン押す(向き処理ない)
		if (m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置のポインタから渡す
			p_Start[0]->m_Position = m_Start->m_Position;
			//データの保存
			PosX = (int)p_Start[i]->m_Position.x;
			PosY = (int)p_Start[i]->m_Position.y;
			PosZ = (int)p_Start[i]->m_Position.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\start_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\n", PosX, PosY, PosZ);
			// ファイルクローズ
			fclose(pFile);

		}
	}
	/*startの処理終了*/

	/*endの処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_ANOTHER
	//Another MenuのMenu:BUILD_MENU_ANOTHER_END
	if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ANOTHER && m_BuildMenu_Another->m_type == m_BuildMenu_Another->BUILD_MENU_ANOTHER_END)
	{
		//この以外のモノ全部FALSE
		m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
		m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
		m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
		m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
		m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
		m_Start->m_type = m_Start->START_BUILDING_FALSE;
		m_End->m_type = m_End->END_BUILDING_TRUE;
		m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;
		//	マウスの左ボタン押す(向き処理ない)
		if (m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//位置のポインタから渡す
			p_End[0]->m_Position = m_End->m_Position;
			//データの保存
			PosX = (int)p_End[i]->m_Position.x;
			PosY = (int)p_End[i]->m_Position.y;
			PosZ = (int)p_End[i]->m_Position.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\ANOTHER\\end_Map01.txt", "w+");//「w+」とは書き込みと読み込み にする（上書き）
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\n", PosX, PosY, PosZ);
			// ファイルクローズ
			fclose(pFile);

		}
	}
	/*endの処理終了*/

	/*pointの処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_PROP
	//Another MenuのMenu:BUILD_MENU_PROP_POINT
	if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_PROP && m_BuildMenu_Prop->m_type == m_BuildMenu_Prop->BUILD_MENU_PROP_POINT)
	{
		//この以外のモノ全部FALSE
		m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
		m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
		m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
		m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
		m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		m_Point->m_type = m_Point->POINT_BUILDING_TRUE;
		m_Start->m_type = m_Start->START_BUILDING_FALSE;
		m_End->m_type = m_End->END_BUILDING_FALSE;
		m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;
		//	マウスの左ボタン押す(向き処理ない)
		if (m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Point[0] = CPoint::Create(D3DXVECTOR3((int)m_Point->m_Position.x, (int)m_Point->m_Position.y, (int)m_Point->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_POINT);
			//データの保存
			PosX = (int)p_Point[i]->m_Position.x;
			PosY = (int)p_Point[i]->m_Position.y;
			PosZ = (int)p_Point[i]->m_Position.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\PROP\\point_Map01.txt", "a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\n", PosX, PosY, PosZ);
			// ファイルクローズ
			fclose(pFile);
		}
	}
	/*pointの処理終了*/

	/*doorの処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_PROP
	//Another MenuのMenu:BUILD_MENU_PROP_DOOR
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_PROP && m_BuildMenu_Prop->m_type == m_BuildMenu_Prop->BUILD_MENU_PROP_DOOR)
		{
			//この以外のモノ全部FALSE
			m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
			m_Trail->m_type = m_Trail->TRAIL_BUILDING_FALSE;
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
			m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
			m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
			m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
			m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
			m_Start->m_type = m_Start->START_BUILDING_FALSE;
			m_End->m_type = m_End->END_BUILDING_FALSE;

			//「I」ボタンが押す、
			//状態：DOOR_BUILDING_FRONT（↑）
		if (m_Door->m_type != m_Door->DOOR_BUILDING_FRONT &&m_Input->GetKeyboardTrigger(DIK_I))
		{
			m_Door->m_type = m_Door->DOOR_BUILDING_FRONT;
		}
		//	マウスの左ボタン押す
		if (m_Door->m_type == m_Door->DOOR_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Door[0] = CDoor::Create(D3DXVECTOR3((int)m_Door->m_Position.x, (int)m_Door->m_Position.y, (int)m_Door->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
			//データの保存
			PosX = (int)p_Door[i]->m_Position.x;
			PosY = (int)p_Door[i]->m_Position.y;
			PosZ = (int)p_Door[i]->m_Position.z;
			RotX = p_Door[i]->m_Rotation.x;
			RotY = p_Door[i]->m_Rotation.y;
			RotZ = p_Door[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\PROP\\Door_Map01.txt", "a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);
		}
		//「K」ボタンが押す、
		//状態：DOOR_BUILDING_BACK（↓）
		if (m_Door->m_type != m_Door->DOOR_BUILDING_BACK && m_Input->GetKeyboardTrigger(DIK_K))
		{
			m_Door->m_type = m_Door->DOOR_BUILDING_BACK;
		}
		//	マウスの左ボタン押す
		if (m_Door->m_type == m_Door->DOOR_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Door[0] = CDoor::Create(D3DXVECTOR3((int)m_Door->m_Position.x, (int)m_Door->m_Position.y, (int)m_Door->m_Position.z), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
			//データの保存
			PosX = (int)p_Door[i]->m_Position.x;
			PosY = (int)p_Door[i]->m_Position.y;
			PosZ = (int)p_Door[i]->m_Position.z;
			RotX = p_Door[i]->m_Rotation.x;
			RotY = p_Door[i]->m_Rotation.y;
			RotZ = p_Door[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\PROP\\Door_Map01.txt", "a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}

		//「J」ボタンが押す、
		//状態：DOOR_BUILDING_LEFT（←）
		if (m_Door->m_type != m_Door->DOOR_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
		{
			m_Door->m_type = m_Door->DOOR_BUILDING_LEFT;
		}
		//	マウスの左ボタン押す
		if (m_Door->m_type == m_Door->DOOR_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Door[0] = CDoor::Create(D3DXVECTOR3((int)m_Door->m_Position.x, (int)m_Door->m_Position.y, (int)m_Door->m_Position.z), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
			//データの保存
			PosX = (int)p_Door[i]->m_Position.x;
			PosY = (int)p_Door[i]->m_Position.y;
			PosZ = (int)p_Door[i]->m_Position.z;	
			RotX = p_Door[i]->m_Rotation.x;
			RotY = p_Door[i]->m_Rotation.y;
			RotZ = p_Door[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\PROP\\Door_Map01.txt", "a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

		}

		//「L」ボタンが押す、
		//状態：DOOR_BUILDING_RIGHT（→）
		if (m_Door->m_type != m_Door->DOOR_BUILDING_RIGHT &&m_Input->GetKeyboardTrigger(DIK_L))
		{
			m_Door->m_type = m_Door->DOOR_BUILDING_RIGHT;
		}
		//	マウスの左ボタン押す
		if (m_Door->m_type == m_Door->DOOR_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Door[0] = CDoor::Create(D3DXVECTOR3((int)m_Door->m_Position.x, (int)m_Door->m_Position.y, (int)m_Door->m_Position.z), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
			//データの保存
			PosX = (int)p_Door[i]->m_Position.x;
			PosY = (int)p_Door[i]->m_Position.y;
			PosZ = (int)p_Door[i]->m_Position.z;
			RotX = p_Door[i]->m_Rotation.x;
			RotY = p_Door[i]->m_Rotation.y;
			RotZ = p_Door[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\PROP\\Door_Map01.txt", "a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);
		}
	}
	/*doorの処理終了*/


	/*天井板の処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_CEILING
	//ceiling MenuのMenu:NULL
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_CEILING)
		{
			//この以外のモノ全部FALSE
			m_Trail->m_type = m_Trail->TRAIL_BUILDING_FALSE;
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
			m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
			m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
			m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
			m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_TRUE;
			m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
			m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
			m_Start->m_type = m_Start->START_BUILDING_FALSE;
			m_End->m_type = m_End->END_BUILDING_FALSE;
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;
			//	マウスの左ボタン押す
			if (m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Ceiling[0] = CCeiling::Create(D3DXVECTOR3((int)m_Ceiling->m_Position.x, (int)m_Ceiling->m_Position.y, (int)m_Ceiling->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_CEILING_FILE);
				//データの保存
				PosX = (int)p_Ceiling[i]->m_Position.x;
				PosY = (int)p_Ceiling[i]->m_Position.y;
				PosZ = (int)p_Ceiling[i]->m_Position.z;


				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\CEILING\\ceiling_Map01.txt", "a");//「a」とは最後に追加書き込みする
				// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\n", PosX, PosY, PosZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*天井板の処理終了*/

	/*壁001の処理開始*/
	//処理条件:
	//Menu:BUILD_MENU_WALL
	//壁 MenuのMenu:BUILD_MENU_WALL_01
	if ( m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_WALL  && m_BuildMenu_Wall->m_type == m_BuildMenu_Wall->BUILD_MENU_WALL_01)
	{
		//この以外のモノ全部FALSE
		m_Trail->m_type = m_Trail->TRAIL_BUILDING_FALSE;
		m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
		m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
		m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
		m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
		m_Start->m_type = m_Start->START_BUILDING_FALSE;
		m_End->m_type = m_End->END_BUILDING_FALSE;
		m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;

		//「I」ボタンが押す、
		//状態：WALL_001_BUILDING_FRONT（↑）
		if (m_Wall_001->m_type != m_Wall_001->WALL_001_BUILDING_FRONT &&m_Input->GetKeyboardTrigger(DIK_I))
		{
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FRONT;
		}

		//	マウスの左ボタン押す
		if (m_Wall_001->m_type == m_Wall_001->WALL_001_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//描画する
			p_Wall_001[0] = CWall_001::Create(D3DXVECTOR3((int)m_Wall_001->m_Position.x, (int)m_Wall_001->m_Position.y, (int)m_Wall_001->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_001_FILE);
			//データの保存
			PosX = (int)p_Wall_001[i]->m_Position.x;
			PosY = (int)p_Wall_001[i]->m_Position.y;
			PosZ = (int)p_Wall_001[i]->m_Position.z;
			RotX = p_Wall_001[i]->m_Rotation.x;
			RotY = p_Wall_001[i]->m_Rotation.y;
			RotZ = p_Wall_001[i]->m_Rotation.z;

			FILE *pFile;
			// ファイルオープン
			pFile = fopen("data\\SCRIPT\\WALL\\wall_01_Map01.txt","a");//「a」とは最後に追加書き込みする
			// 書き出し
			fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
			// ファイルクローズ
			fclose(pFile);

			}

			//「K」ボタンが押す、
			//状態：WALL_001_BUILDING_BACK（↓）
			if (m_Wall_001->m_type != m_Wall_001->WALL_001_BUILDING_BACK &&m_Input->GetKeyboardTrigger(DIK_K))
			{
				m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_BACK;
			}

			//	マウスの左ボタン押す
			if (m_Wall_001->m_type == m_Wall_001->WALL_001_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_001[0] = CWall_001::Create(D3DXVECTOR3((int)m_Wall_001->m_Position.x, (int)m_Wall_001->m_Position.y, (int)m_Wall_001->m_Position.z), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_001_FILE);
				//データの保存
				PosX = (int)p_Wall_001[i]->m_Position.x;
				PosY = (int)p_Wall_001[i]->m_Position.y;
				PosZ = (int)p_Wall_001[i]->m_Position.z;
				RotX = p_Wall_001[i]->m_Rotation.x;
				RotY = p_Wall_001[i]->m_Rotation.y;
				RotZ = p_Wall_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
				// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}


			//「J」ボタンが押す、
			//状態：WALL_001_BUILDING_LEFT（←）
			if (m_Wall_001->m_type != m_Wall_001->WALL_001_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
			{
				m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_LEFT;
			}
			//	マウスの左ボタン押す
			if (m_Wall_001->m_type == m_Wall_001->WALL_001_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_001[0] = CWall_001::Create(D3DXVECTOR3((int)m_Wall_001->m_Position.x, (int)m_Wall_001->m_Position.y, (int)m_Wall_001->m_Position.z), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_001_FILE);
				//データの保存
				PosX = (int)p_Wall_001[i]->m_Position.x;
				PosY = (int)p_Wall_001[i]->m_Position.y;
				PosZ = (int)p_Wall_001[i]->m_Position.z;
				RotX = p_Wall_001[i]->m_Rotation.x;
				RotY = p_Wall_001[i]->m_Rotation.y;
				RotZ = p_Wall_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
				// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}

			//「L」ボタンが押す、
			//状態：WALL_001_BUILDING_RIGHT（→）
			if (m_Wall_001->m_type != m_Wall_001->WALL_001_BUILDING_RIGHT &&m_Input->GetKeyboardTrigger(DIK_L))
			{
				m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_RIGHT;
			}
			//	マウスの左ボタン押す
			if (m_Wall_001->m_type == m_Wall_001->WALL_001_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_001[0] = CWall_001::Create(D3DXVECTOR3((int)m_Wall_001->m_Position.x, (int)m_Wall_001->m_Position.y, (int)m_Wall_001->m_Position.z), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_001_FILE);
				//データの保存
				PosX = (int)p_Wall_001[i]->m_Position.x;
				PosY = (int)p_Wall_001[i]->m_Position.y;
				PosZ = (int)p_Wall_001[i]->m_Position.z;
				RotX = p_Wall_001[i]->m_Rotation.x;
				RotY = p_Wall_001[i]->m_Rotation.y;
				RotZ = p_Wall_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
				// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*壁001の処理終了*/
		/*壁002の処理開始*/
		//処理条件:
		//Menu:BUILD_MENU_WALL
		//壁 MenuのMenu:BUILD_MENU_WALL_02
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_WALL  && m_BuildMenu_Wall->m_type == m_BuildMenu_Wall->BUILD_MENU_WALL_02)
		{
			//この以外のモノ全部FALSE
			m_Trail->m_type = m_Trail->TRAIL_BUILDING_FALSE;
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
			m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
			m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
			m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
			m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
			m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
			m_Start->m_type = m_Start->START_BUILDING_FALSE;
			m_End->m_type = m_End->END_BUILDING_FALSE;
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;

			//「I」ボタンが押す、
			//状態：WALL_002_BUILDING_FRONT（↑）
			if (m_Wall_002->m_type != m_Wall_002->WALL_002_BUILDING_FRONT &&m_Input->GetKeyboardTrigger(DIK_I))
			{
				m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FRONT;
			}

			//	マウスの左ボタン押す
			if (m_Wall_002->m_type == m_Wall_002->WALL_002_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_002[0] = CWall_002::Create(D3DXVECTOR3((int)m_Wall_002->m_Position.x, (int)m_Wall_002->m_Position.y, (int)m_Wall_002->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_002_FILE);
				//データの保存
				PosX = (int)p_Wall_002[i]->m_Position.x;
				PosY = (int)p_Wall_002[i]->m_Position.y;
				PosZ = (int)p_Wall_002[i]->m_Position.z;
				RotX = p_Wall_002[i]->m_Rotation.x;
				RotY = p_Wall_002[i]->m_Rotation.y;
				RotZ = p_Wall_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}

			//「K」ボタンが押す、
			//状態：WALL_002_BUILDING_BACK（↓）
			if (m_Wall_002->m_type != m_Wall_002->WALL_002_BUILDING_BACK &&m_Input->GetKeyboardTrigger(DIK_K))
			{
				m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_BACK;
			}

			//	マウスの左ボタン押す
			if (m_Wall_002->m_type == m_Wall_002->WALL_002_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_002[0] = CWall_002::Create(D3DXVECTOR3((int)m_Wall_002->m_Position.x, (int)m_Wall_002->m_Position.y, (int)m_Wall_002->m_Position.z), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_002_FILE);
				//データの保存
				PosX = (int)p_Wall_002[i]->m_Position.x;
				PosY = (int)p_Wall_002[i]->m_Position.y;
				PosZ = (int)p_Wall_002[i]->m_Position.z;
				RotX = p_Wall_002[i]->m_Rotation.x;
				RotY = p_Wall_002[i]->m_Rotation.y;
				RotZ = p_Wall_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}


			//「J」ボタンが押す、
			//状態：WALL_002_BUILDING_LEFT（←）
			if (m_Wall_002->m_type != m_Wall_002->WALL_002_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
			{
				m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_LEFT;
			}
			//	マウスの左ボタン押す
			if (m_Wall_002->m_type == m_Wall_002->WALL_002_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_002[0] = CWall_002::Create(D3DXVECTOR3((int)m_Wall_002->m_Position.x, (int)m_Wall_002->m_Position.y, (int)m_Wall_002->m_Position.z), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_002_FILE);
				//データの保存
				PosX = (int)p_Wall_002[i]->m_Position.x;
				PosY = (int)p_Wall_002[i]->m_Position.y;
				PosZ = (int)p_Wall_002[i]->m_Position.z;
				RotX = p_Wall_002[i]->m_Rotation.x;
				RotY = p_Wall_002[i]->m_Rotation.y;
				RotZ = p_Wall_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}

			//「L」ボタンが押す、
			//状態：WALL_002_BUILDING_RIGHT（→）
			if (m_Wall_002->m_type != m_Wall_002->WALL_002_BUILDING_RIGHT &&m_Input->GetKeyboardTrigger(DIK_L))
			{
				m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_RIGHT;
			}
			//	マウスの左ボタン押す
			if (m_Wall_002->m_type == m_Wall_002->WALL_002_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Wall_002[0] = CWall_002::Create(D3DXVECTOR3((int)m_Wall_002->m_Position.x, (int)m_Wall_002->m_Position.y, (int)m_Wall_002->m_Position.z), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 200.0f, 200.0f, TEXTURE_WALL_002_FILE);
				//データの保存
				PosX = (int)p_Wall_002[i]->m_Position.x;
				PosY = (int)p_Wall_002[i]->m_Position.y;
				PosZ = (int)p_Wall_002[i]->m_Position.z;
				RotX = p_Wall_002[i]->m_Rotation.x;
				RotY = p_Wall_002[i]->m_Rotation.y;
				RotZ = p_Wall_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\WALL\\wall_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*壁002の処理終了*/

		/*敵001の処理開始*/
		//処理条件:
		//Menu:BUILD_MENU_ENEMY
		//敵 MenuのMenu:BUILD_MENU_ENEMY_01
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ENEMY  && m_BuildMenu_Enemy->m_type == m_BuildMenu_Enemy->BUILD_MENU_ENEMY_01)
		{
			//この以外のモノ全部FALSE
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
			m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
			m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FALSE;
			m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
			m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
			m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
			m_Start->m_type = m_Start->START_BUILDING_FALSE;
			m_End->m_type = m_End->END_BUILDING_FALSE;
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;

			//「I」ボタンが押す、
			//状態：ENEMY_001_BUILDING_FRONT（↑）
			if (m_Enemy_001->m_type != m_Enemy_001->ENEMY_001_BUILDING_FRONT &&m_Input->GetKeyboardTrigger(DIK_I))
			{
				m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FRONT;
				//状態：TRAIL_BUILDING_FRONT（↑）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_FRONT;

			}

			//	マウスの左ボタン押す
			if (m_Enemy_001->m_type == m_Enemy_001->ENEMY_001_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3((int)m_Enemy_001->m_Position.x, (int)m_Enemy_001->m_Position.y, (int)m_Enemy_001->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, MODEL_ENEMY_001);
				//データの保存
				PosX = (int)p_Enemy_001[i]->m_Position.x;
				PosY = (int)p_Enemy_001[i]->m_Position.y;
				PosZ = (int)p_Enemy_001[i]->m_Position.z;
				RotX = p_Enemy_001[i]->m_Rotation.x;
				RotY = p_Enemy_001[i]->m_Rotation.y;
				RotZ = p_Enemy_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}

			//「K」ボタンが押す、
			//状態：ENEMY_001_BUILDING_BACK（↓）
			if (m_Enemy_001->m_type != m_Enemy_001->ENEMY_001_BUILDING_BACK &&m_Input->GetKeyboardTrigger(DIK_K))
			{
				m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_BACK;
				//状態：TRAIL_BUILDING_BACK（↓）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_BACK;
			}

			//	マウスの左ボタン押す
			if (m_Enemy_001->m_type == m_Enemy_001->ENEMY_001_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3((int)m_Enemy_001->m_Position.x, (int)m_Enemy_001->m_Position.y, (int)m_Enemy_001->m_Position.z), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 200.0f, 200.0f, MODEL_ENEMY_001);
				//データの保存
				PosX = (int)p_Enemy_001[i]->m_Position.x;
				PosY = (int)p_Enemy_001[i]->m_Position.y;
				PosZ = (int)p_Enemy_001[i]->m_Position.z;
				RotX = p_Enemy_001[i]->m_Rotation.x;
				RotY = p_Enemy_001[i]->m_Rotation.y;
				RotZ = p_Enemy_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}


			//「J」ボタンが押す、
			//状態：ENEMY_001_BUILDING_LEFT（←）
			if (m_Enemy_001->m_type != m_Enemy_001->ENEMY_001_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
			{
				m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_LEFT;
				//状態：TRAIL_BUILDING_LEFT（←）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_LEFT;
			}
			//	マウスの左ボタン押す
			if (m_Enemy_001->m_type == m_Enemy_001->ENEMY_001_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3((int)m_Enemy_001->m_Position.x, (int)m_Enemy_001->m_Position.y, (int)m_Enemy_001->m_Position.z), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 200.0f, 200.0f, MODEL_ENEMY_001);
				//データの保存
				PosX = (int)p_Enemy_001[i]->m_Position.x;
				PosY = (int)p_Enemy_001[i]->m_Position.y;
				PosZ = (int)p_Enemy_001[i]->m_Position.z;
				RotX = p_Enemy_001[i]->m_Rotation.x;
				RotY = p_Enemy_001[i]->m_Rotation.y;
				RotZ = p_Enemy_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}

			//「L」ボタンが押す、
			//状態：ENEMY_001_BUILDING_RIGHT（→）
			if (m_Enemy_001->m_type != m_Enemy_001->ENEMY_001_BUILDING_RIGHT &&m_Input->GetKeyboardTrigger(DIK_L))
			{
				m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_RIGHT;
				//状態：TRAIL_BUILDING_RIGHT（→）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_RIGHT;
			}
			//	マウスの左ボタン押す
			if (m_Enemy_001->m_type == m_Enemy_001->ENEMY_001_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_001[0] = CEnemy_001::Create(D3DXVECTOR3((int)m_Enemy_001->m_Position.x, (int)m_Enemy_001->m_Position.y, (int)m_Enemy_001->m_Position.z), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 200.0f, 200.0f, MODEL_ENEMY_001);
				//データの保存
				PosX = (int)p_Enemy_001[i]->m_Position.x;
				PosY = (int)p_Enemy_001[i]->m_Position.y;
				PosZ = (int)p_Enemy_001[i]->m_Position.z;
				RotX = p_Enemy_001[i]->m_Rotation.x;
				RotY = p_Enemy_001[i]->m_Rotation.y;
				RotZ = p_Enemy_001[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*敵001の処理終了*/

		/*敵002の処理開始*/
		//処理条件:
		//Menu:BUILD_MENU_ENEMY
		//敵 MenuのMenu:BUILD_MENU_ENEMY_02
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ENEMY  && m_BuildMenu_Enemy->m_type == m_BuildMenu_Enemy->BUILD_MENU_ENEMY_02)
		{
			//この以外のモノ全部FALSE
			m_Enemy_001->m_type = m_Enemy_001->ENEMY_001_BUILDING_FALSE;
			m_Wall_001->m_type = m_Wall_001->WALL_001_BUILDING_FALSE;
			m_Wall_002->m_type = m_Wall_002->WALL_002_BUILDING_FALSE;
			m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
			m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
			m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
			m_Start->m_type = m_Start->START_BUILDING_FALSE;
			m_End->m_type = m_End->END_BUILDING_FALSE;
			m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;

			//「I」ボタンが押す、
			//状態：ENEMY_002_BUILDING_FRONT（↑）
			if (m_Enemy_002->m_type != m_Enemy_002->ENEMY_002_BUILDING_FRONT &&m_Input->GetKeyboardTrigger(DIK_I))
			{
				m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_FRONT;
				//状態：TRAIL_BUILDING_FRONT（↑）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_FRONT;
			}

			//	マウスの左ボタン押す
			if (m_Enemy_002->m_type == m_Enemy_002->ENEMY_002_BUILDING_FRONT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3((int)m_Enemy_002->m_Position.x, (int)m_Enemy_002->m_Position.y, (int)m_Enemy_002->m_Position.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
				//データの保存
				PosX = (int)p_Enemy_002[i]->m_Position.x;
				PosY = (int)p_Enemy_002[i]->m_Position.y;
				PosZ = (int)p_Enemy_002[i]->m_Position.z;
				RotX = p_Enemy_002[i]->m_Rotation.x;
				RotY = p_Enemy_002[i]->m_Rotation.y;
				RotZ = p_Enemy_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}

			//「K」ボタンが押す、
			//状態：ENEMY_002_BUILDING_BACK（↓）
			if (m_Enemy_002->m_type != m_Enemy_002->ENEMY_002_BUILDING_BACK &&m_Input->GetKeyboardTrigger(DIK_K))
			{
				m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_BACK;
				//状態：TRAIL_BUILDING_BACK（↓）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_BACK;
			}

			//	マウスの左ボタン押す
			if (m_Enemy_002->m_type == m_Enemy_002->ENEMY_002_BUILDING_BACK && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3((int)m_Enemy_002->m_Position.x, (int)m_Enemy_002->m_Position.y, (int)m_Enemy_002->m_Position.z), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
				//データの保存
				PosX = (int)p_Enemy_002[i]->m_Position.x;
				PosY = (int)p_Enemy_002[i]->m_Position.y;
				PosZ = (int)p_Enemy_002[i]->m_Position.z;
				RotX = p_Enemy_002[i]->m_Rotation.x;
				RotY = p_Enemy_002[i]->m_Rotation.y;
				RotZ = p_Enemy_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);

			}


			//「J」ボタンが押す、
			//状態：ENEMY_002_BUILDING_LEFT（←）
			if (m_Enemy_002->m_type != m_Enemy_002->ENEMY_002_BUILDING_LEFT &&m_Input->GetKeyboardTrigger(DIK_J))
			{
				m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_LEFT;
				//状態：TRAIL_BUILDING_LEFT（←）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_LEFT;
			}
			//	マウスの左ボタン押す
			if (m_Enemy_002->m_type == m_Enemy_002->ENEMY_002_BUILDING_LEFT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3((int)m_Enemy_002->m_Position.x, (int)m_Enemy_002->m_Position.y, (int)m_Enemy_002->m_Position.z), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
				//データの保存
				PosX = (int)p_Enemy_002[i]->m_Position.x;
				PosY = (int)p_Enemy_002[i]->m_Position.y;
				PosZ = (int)p_Enemy_002[i]->m_Position.z;
				RotX = p_Enemy_002[i]->m_Rotation.x;
				RotY = p_Enemy_002[i]->m_Rotation.y;
				RotZ = p_Enemy_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\wall_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}

			//「L」ボタンが押す、
			//状態：ENEMY_002_BUILDING_RIGHT（→）
			if (m_Enemy_002->m_type != m_Enemy_002->ENEMY_002_BUILDING_RIGHT &&m_Input->GetKeyboardTrigger(DIK_L))
			{
				m_Enemy_002->m_type = m_Enemy_002->ENEMY_002_BUILDING_RIGHT;
				//状態：TRAIL_BUILDING_RIGHT（→）軌跡
				m_Trail->m_type = m_Trail->TRAIL_BUILDING_RIGHT;
			}
			//	マウスの左ボタン押す
			if (m_Enemy_002->m_type == m_Enemy_002->ENEMY_002_BUILDING_RIGHT && m_Mouse->GetMouseTrigger(DIM_LEFT))
			{
				//描画する
				p_Enemy_002[0] = CEnemy_002::Create(D3DXVECTOR3((int)m_Enemy_002->m_Position.x, (int)m_Enemy_002->m_Position.y, (int)m_Enemy_002->m_Position.z), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
				//データの保存
				PosX = (int)p_Enemy_002[i]->m_Position.x;
				PosY = (int)p_Enemy_002[i]->m_Position.y;
				PosZ = (int)p_Enemy_002[i]->m_Position.z;
				RotX = p_Enemy_002[i]->m_Rotation.x;
				RotY = p_Enemy_002[i]->m_Rotation.y;
				RotZ = p_Enemy_002[i]->m_Rotation.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする
																			// 書き出し
				fprintf_s(pFile, "pos = %d %d %d\nrot = %.2f %.2f %.2f\n", PosX, PosY, PosZ, RotX, RotY, RotZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*敵002の処理終了*/

		/*敵001軌跡の処理開始*/
		//処理条件:
		//Menu:BUILD_MENU_ENEMY
		//敵 MenuのMenu:BUILD_MENU_ENEMY_01
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ENEMY && m_BuildMenu_Enemy->m_type == m_BuildMenu_Enemy->BUILD_MENU_ENEMY_01 && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//状態：TRAIL_BUILDING_FRONT（↑）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_FRONT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_001[i]->m_Position.x;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_001[i]->m_Position.z + m_Trail->Check;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
				// 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);

			}
			//状態：TRAIL_BUILDING_BACK（↓）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_BACK)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_001[i]->m_Position.x;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_001[i]->m_Position.z - m_Trail->Check;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
				// 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);

			}

			//状態：TRAIL_BUILDING_LEFT（←）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_LEFT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_001[i]->m_Position.x - m_Trail->Check;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_001[i]->m_Position.z ;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
				// 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);
			}
			//状態：TRAIL_BUILDING_RIGHT（→）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_RIGHT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_001[i]->m_Position.x + m_Trail->Check;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_001[i]->m_Position.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
				// 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*敵001軌跡の処理終了*/

		/*敵002軌跡の処理開始*/
		//処理条件:
		//Menu:BUILD_MENU_ENEMY
		//敵 MenuのMenu:BUILD_MENU_ENEMY_02
		if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_ENEMY && m_BuildMenu_Enemy->m_type == m_BuildMenu_Enemy->BUILD_MENU_ENEMY_02 && m_Mouse->GetMouseTrigger(DIM_LEFT))
		{
			//状態：TRAIL_BUILDING_FRONT（↑）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_FRONT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_002[i]->m_Position.x;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_002[i]->m_Position.z + m_Trail->Check;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
																			  // 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);

			}
			//状態：TRAIL_BUILDING_BACK（↓）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_BACK)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_002[i]->m_Position.x;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_002[i]->m_Position.z - m_Trail->Check;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
																			  // 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);

			}

			//状態：TRAIL_BUILDING_LEFT（←）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_LEFT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_002[i]->m_Position.x - m_Trail->Check;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_002[i]->m_Position.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
																			  // 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);
			}
			//状態：TRAIL_BUILDING_RIGHT（→）
			if (m_Trail->m_type == m_Trail->TRAIL_BUILDING_RIGHT)
			{
				//描画する
				p_Trail[0] = CTrail::Create(D3DXVECTOR3((int)m_Trail->m_Position.x, (int)m_Trail->m_Position.y, (int)m_Trail->m_Position.z), D3DXVECTOR3(m_Trail->m_Rotation.x, m_Trail->m_Rotation.y, m_Trail->m_Rotation.z), m_Trail->Check, m_Trail->m_width, TEXTURE_TRAIL_FILE);
				//データの保存
				m_Trail_PosX = (int)p_Enemy_002[i]->m_Position.x + m_Trail->Check;
				m_Trail_PosY = 0;
				m_Trail_PosZ = (int)p_Enemy_002[i]->m_Position.z;

				FILE *pFile;
				// ファイルオープン
				pFile = fopen("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", "a");//「a」とは最後に追加書き込みする(posとrot後)
																			  // 書き出し
				fprintf_s(pFile, "Trail = %d %d %d\n", m_Trail_PosX, m_Trail_PosY, m_Trail_PosZ);
				// ファイルクローズ
				fclose(pFile);
			}
		}
		/*敵002軌跡の処理終了*/
		//電球
		//if (m_BuildMenu->m_type == m_BuildMenu->BUILD_MENU_LIGHT)
		//{
		//	m_Ceiling->m_type = m_Ceiling->CEILING_BUILDING_FALSE;
		//	m_Door->m_type = m_Door->DOOR_BUILDING_FALSE;
		//	m_Point->m_type = m_Point->POINT_BUILDING_FALSE;
		//	m_Start->m_type = m_Start->START_BUILDING_FALSE;
		//	m_End->m_type = m_End->END_BUILDING_FALSE;
		//	m_Robot->m_type = m_Robot->ROBOT_BUILDING_FALSE;
		//	if (m_Mouse->GetMouseTrigger(DIM_LEFT))
		//	{
		//		p_Light[0] = CBuildLight::Create(D3DXVECTOR3((int)m_BuildLight->m_Position.x, (int)m_BuildLight->m_Position.y, (int)m_BuildLight->m_Position.z));
		//		PosX = m_BuildLight->m_Position.x;
		//		PosY = m_BuildLight->m_Position.y;
		//		PosZ = m_BuildLight->m_Position.z;
		//		// ファイルオープン
		//		pFile = fopen("data\\SCRIPT\\LIGHT\\light.txt", "a");
		//		// 書き出し
		//		fprintf_s(pFile, "pos = %d %d %d\n", PosX, PosY, PosZ);
		//		// ファイルクローズ
		//		fclose(pFile);
		//	}

		//}
		////読み込みの内容を消します
		//if (m_Input->GetKeyboardTrigger(DIK_C))
		//{
		//	// ファイルオープン
		//	pFile = fopen(FILE_SCRIPT_MAP_WALL_01, "w");
		//	// ファイルクローズ
		//	fclose(pFile);

		//	// ファイルオープン
		//	pFile = fopen(FILE_SCRIPT_MAP_WALL_02, "w");
		//	// ファイルクローズ
		//	fclose(pFile);
		//}

}

/*******************************************************************************
関数名：	void CBuildMap::Draw
戻り値：	void
引数：		void
説明：		CBuildMapの描画処理
*******************************************************************************/
void CBuildMap::Draw(void)
{

}