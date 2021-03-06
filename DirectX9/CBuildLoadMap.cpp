/********************************************************************************
* ファイル名　CBuildLoadMap.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップの数値読み込みの管理
********************************************************************************/

/*******************************************************************************
インクルード宣言
*******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include "main.h"
#include "scene3D.h"
#include "manager.h"
#include "scene.h"
#include "CBuildLoadMap.h"

//------------------------------------------------------------------------------
//	関数名:	CBuildLoadMap::CBuildLoadMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBuildLoadMap::CBuildLoadMap()
{


}

//------------------------------------------------------------------------------
//	関数名:	CBuildLoadMap::~CBuildLoadMap
//	引数:	なし
//	戻り値:	
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBuildLoadMap::~CBuildLoadMap()
{

}

/*******************************************************************************
関数名：	void CBuildLoadMap::Init
戻り値：	void
引数：		void
説明：		CBuildLoadMapの初期化処理
*******************************************************************************/
void CBuildLoadMap::Init(void)
{
	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CGameWall_001 *m_GameWall_001 = BuildManager->GetGameWall_001();
	CGameWall_002 *m_GameWall_002 = BuildManager->GetGameWall_002();
	CGameEnemy_001 *m_GameEnemy_001 = BuildManager->GetGameEnemy_001();
	CGameEnemy_002 *m_GameEnemy_002 = BuildManager->GetGameEnemy_002();
	CGameCeiling *m_GameCeiling = BuildManager->GetGameCeiling();
	CGameDoor *m_GameDoor = BuildManager->GetGameDoor();
	CGamePoint *m_GamePoint = BuildManager->GetGamePoint();
	//読み込みの数の初期化
	m_Wall001_num = 0;
	m_Wall002_num = 0;
	m_Enemy001_num = 0;
	m_Enemy002_num = 0;
	m_Point_num = 0;
	m_Ceiling_num = 0;
	m_Door_num = 0;

	//テスト用読み込み
	if (access("data\\SCRIPT\\WALL\\wall_01_Map01.txt", 0) == 0)
	{
		LoadTest("data\\SCRIPT\\WALL\\wall_01_Map01.txt", hInstance, hWnd);
	}

	//壁001の読み込み
	if (access("data\\SCRIPT\\WALL\\wall_01_Map01.txt", 0) == 0)
	{
		LoadWall_001("data\\SCRIPT\\WALL\\wall_01_Map01.txt", hInstance, hWnd);
	}

	//壁002の読み込み
	if (access("data\\SCRIPT\\WALL\\wall_02_Map01.txt", 0) == 0)
	{
		LoadWall_002("data\\SCRIPT\\WALL\\wall_02_Map01.txt", hInstance, hWnd);
	}

	//敵001の読み込み
	if (access("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", 0) == 0)
	{
		LoadEnemy_001("data\\SCRIPT\\ENEMY\\enemy_01_Map01.txt", hInstance, hWnd);
	}

	//敵002の読み込み
	if (access("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", 0) == 0)
	{
		LoadEnemy_002("data\\SCRIPT\\ENEMY\\enemy_02_Map01.txt", hInstance, hWnd);
	}

	//天井板の読み込み
	if (access("data\\SCRIPT\\CEILING\\ceiling_Map01.txt", 0) == 0)
	{
		LoadCeiling("data\\SCRIPT\\CEILING\\ceiling_Map01.txt", hInstance, hWnd);
	}

	//ドアモデルの読み込み
	if (access("data\\SCRIPT\\PROP\\Door_Map01.txt", 0) == 0)
	{
		LoadDoor("data\\SCRIPT\\PROP\\Door_Map01.txt", hInstance, hWnd);
	}

	//条件モデルの読み込み
	if (access("data\\SCRIPT\\PROP\\point_Map01.txt", 0) == 0)
	{
		LoadPoint("data\\SCRIPT\\PROP\\point_Map01.txt", hInstance, hWnd);
	}

	//プレイヤー最初位置の読み込み
	if (access("data\\SCRIPT\\ANOTHER\\start_Map01.txt", 0) == 0)
	{
		LoadStart("data\\SCRIPT\\ANOTHER\\start_Map01.txt", hInstance, hWnd);
	}

	//ゲーム終了位置の読み込み
	if (access("data\\SCRIPT\\ANOTHER\\end_Map01.txt", 0) == 0)
	{
		LoadEnd("data\\SCRIPT\\ANOTHER\\end_Map01.txt", hInstance, hWnd);
	}

	//ルールを説明するのモデルの読み込み
	if (access("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", 0) == 0)
	{
		LoadRobot("data\\SCRIPT\\ANOTHER\\Robot_Map01.txt", hInstance, hWnd);
	}

}

/*******************************************************************************
関数名：	void CBuildLoadMap::Uninit
戻り値：	void
引数：		void
説明：		CBuildLoadMapの終了処理
*******************************************************************************/
void CBuildLoadMap::Uninit(void)
{

}

/*******************************************************************************
関数名：	void CBuildLoadMap::Update
戻り値：	void
引数：		void
説明：		CBuildLoadMapの更新処理
*******************************************************************************/
void CBuildLoadMap::Update()
{


}

/*******************************************************************************
関数名：	void CBuildLoadMap::Draw
戻り値：	void
引数：		void
説明：		CBuildLoadMapの描画処理
*******************************************************************************/
void CBuildLoadMap::Draw(void)
{

}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadWall_001(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Wall001)
*******************************************************************************/
void CBuildLoadMap::LoadWall_001(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;

	// ファイル読込
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得するぎょう
			//文字列の比較
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			else if (strcmp(aStr, "rot") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);

				m_Pos_Wall_001[i].x = fPosX[i];
				m_Pos_Wall_001[i].y = fPosY[i];
				m_Pos_Wall_001[i].z = fPosZ[i];

				m_Rot_Wall_001[i].x = fRotX[i];
				m_Rot_Wall_001[i].y = fRotY[i];
				m_Rot_Wall_001[i].z = fRotZ[i];
				i++;
				m_Wall001_num = i - 1;
			}
		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadWall_002(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Wall002)
*******************************************************************************/
void CBuildLoadMap::LoadWall_002(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;
	// ファイル読込
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{

				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			else if (strcmp(aStr, "rot") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);

				m_Pos_Wall_002[i].x = fPosX[i];
				m_Pos_Wall_002[i].y = fPosY[i];
				m_Pos_Wall_002[i].z = fPosZ[i];

				m_Rot_Wall_002[i].x = fRotX[i];
				m_Rot_Wall_002[i].y = fRotY[i];
				m_Rot_Wall_002[i].z = fRotZ[i];
				i++;
				m_Wall002_num = i - 1;
			}
		}
	}

	fclose(pFile);

}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadEnemy_001(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Enemy001)
*******************************************************************************/
void CBuildLoadMap::LoadEnemy_001(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fPos_To[i].x = 0.0f;
		fPos_To[i].y = 0.0f;
		fPos_To[i].z = 0.0f;
	}
	i = 0;
	// ファイル読込
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			if (strcmp(aStr, "rot") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);
			}
			else if (strcmp(aStr, "Trail") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fPos_To[i].x, &fPos_To[i].y, &fPos_To[i].z);
				m_Pos_Enemy_001[i].x = fPosX[i];
				m_Pos_Enemy_001[i].y = fPosY[i];
				m_Pos_Enemy_001[i].z = fPosZ[i];

				m_Rot_Enemy_001[i].x = fRotX[i];
				m_Rot_Enemy_001[i].y = fRotY[i];
				m_Rot_Enemy_001[i].z = fRotZ[i];
				//敵001の軌跡
				m_Pos_To_Enemy_001[i].x = fPos_To[i].x;
				m_Pos_To_Enemy_001[i].y = fPos_To[i].y;
				m_Pos_To_Enemy_001[i].z = fPos_To[i].z;
				i++;
				m_Enemy001_num = i - 1;
			}
		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadEnemy_002(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Enemy002)
*******************************************************************************/
void CBuildLoadMap::LoadEnemy_002(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fPos_To[i].x = 0.0f;
		fPos_To[i].y = 0.0f;
		fPos_To[i].z = 0.0f;
	}
	i = 0;
	// ファイル読込

	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			if (strcmp(aStr, "rot") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);
			}
			else if (strcmp(aStr, "Trail") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fPos_To[i].x, &fPos_To[i].y, &fPos_To[i].z);
				m_Pos_Enemy_002[i].x = fPosX[i];
				m_Pos_Enemy_002[i].y = fPosY[i];
				m_Pos_Enemy_002[i].z = fPosZ[i];

				m_Rot_Enemy_002[i].x = fRotX[i];
				m_Rot_Enemy_002[i].y = fRotY[i];
				m_Rot_Enemy_002[i].z = fRotZ[i];
				//敵002の軌跡
				m_Pos_To_Enemy_002[i].x = fPos_To[i].x;
				m_Pos_To_Enemy_002[i].y = fPos_To[i].y;
				m_Pos_To_Enemy_002[i].z = fPos_To[i].z;
				i++;
				m_Enemy002_num = i - 1;
			}
		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadCeiling(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Ceiling)
*******************************************************************************/
void CBuildLoadMap::LoadCeiling(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;
	// ファイル読込

	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{

				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
				m_Pos_Ceiling[i].x = fPosX[i];
				m_Pos_Ceiling[i].y = fPosY[i];
				m_Pos_Ceiling[i].z = fPosZ[i];
				i++;
				m_Ceiling_num = i - 1;
			}
		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadDoor(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Door)
*******************************************************************************/
void CBuildLoadMap::LoadDoor(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000;
		fPosY[i] = 5000;
		fPosZ[i] = 5000;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			else if (strcmp(aStr, "rot") == 0)
			{

				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);

				m_Pos_Door[i].x = fPosX[i];
				m_Pos_Door[i].y = fPosY[i];
				m_Pos_Door[i].z = fPosZ[i];

				m_Rot_Door[i].x = fRotX[i];
				m_Rot_Door[i].y = fRotY[i];
				m_Rot_Door[i].z = fRotZ[i];
				i++;
				m_Door_num = i - 1;
			}
		}
	}
	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadPoint(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Point)
*******************************************************************************/
void CBuildLoadMap::LoadPoint(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000;
		fPosY[i] = 5000;
		fPosZ[i] = 5000;
	}

	i = 0;
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
				m_Pos_Point[i].x = fPosX[i];
				m_Pos_Point[i].y = fPosY[i];
				m_Pos_Point[i].z = fPosZ[i];
				i++;
				m_Point_num = i - 1;
			}

		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadStart(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Start)
*******************************************************************************/
void CBuildLoadMap::LoadStart(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < 1; i++)
	{
		fPosX[i] = 5000;
		fPosY[i] = 5000;
		fPosZ[i] = 5000;
	}

	i = 0;
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
 				m_Pos_Start[i].x = fPosX[i];
				m_Pos_Start[i].y = fPosY[i];
				m_Pos_Start[i].z = fPosZ[i];
			}

		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadEnd(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(End)
*******************************************************************************/
void CBuildLoadMap::LoadEnd(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < 1; i++)
	{
		fPosX[i] = 5000;
		fPosY[i] = 5000;
		fPosZ[i] = 5000;
	}

	i = 0;
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
				m_Pos_End[i].x = fPosX[i];
				m_Pos_End[i].y = fPosY[i];
				m_Pos_End[i].z = fPosZ[i];
			}

		}
	}

	fclose(pFile);
}



/*******************************************************************************
関数名：	void CBuildLoadMap::LoadTest(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Test用)
*******************************************************************************/
void CBuildLoadMap::LoadTest(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < MAX_WALL; i++)
	{
		fPosX[i] = 5000.0f;
		fPosY[i] = 5000.0f;
		fPosZ[i] = 5000.0f;
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;
	// ファイル読込

	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{

				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			else if (strcmp(aStr, "rot") == 0)
			{
				CManager *manager = GetManager();
				CGame *game = (CGame*)CManager::GetMode();
				CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();

				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);

				m_Pos_Test[i].x = fPosX[i];
				m_Pos_Test[i].y = fPosY[i];
				m_Pos_Test[i].z = fPosZ[i];

				m_Rot_Test[i].x = fRotX[i];
				m_Rot_Test[i].y = fRotY[i];
				m_Rot_Test[i].z = fRotZ[i];
				i++;
			}
		}
	}

	fclose(pFile);
}

/*******************************************************************************
関数名：	void CBuildLoadMap::LoadRobot(const char *fileName, HINSTANCE hInstance, HWND hWnd)
戻り値：	void
説明：		マップの初期設定の読込(Robot)
*******************************************************************************/
void CBuildLoadMap::LoadRobot(const char *fileName, HINSTANCE hInstance, HWND hWnd)
{
	// 変数の初期化
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStr, sizeof(aData));

	for (int i = 0; i < 1; i++)
	{
		fPosX[i] = 5000;
		fPosY[i] = 5000;
		fPosZ[i] = 5000;
	}
	for (int i = 0; i < 1; i++)
	{
		fRotX[i] = 0;
		fRotY[i] = 0;
		fRotZ[i] = 0;
	}
	i = 0;
	if ((fopen_s(&pFile, fileName, "r")) == NULL)
	{

	}
	// 終了文字までスクリプト内の探索
	if (pFile)
	{
		while (!feof(pFile))
		{
			fscanf_s(pFile, "%s", aStr, sizeof(aStr)); // 行データを取得する
			if (strcmp(aStr, "pos") == 0)
			{
				// 座標情報
				fscanf_s(pFile, "%s %d %d %d", aData, sizeof(aData), &fPosX[i], &fPosY[i], &fPosZ[i]);
			}
			else if (strcmp(aStr, "rot") == 0)
			{

				// 座標情報
				fscanf_s(pFile, "%s %f %f %f", aData, sizeof(aData), &fRotX[i], &fRotY[i], &fRotZ[i]);

				m_Pos_Robot[i].x = fPosX[i];
				m_Pos_Robot[i].y = fPosY[i];
				m_Pos_Robot[i].z = fPosZ[i];

				m_Rot_Robot[i].x = fRotX[i];
				m_Rot_Robot[i].y = fRotY[i];
				m_Rot_Robot[i].z = fRotZ[i];
			}
		}
	}
	fclose(pFile);
}