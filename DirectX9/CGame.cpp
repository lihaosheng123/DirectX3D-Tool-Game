/********************************************************************************
* タイトル　GAMEモード
* ファイル名　CGame.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
GAMEのモード処理
********************************************************************************/
#include "CGame.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//------------------------------------------------------------------------------
//	関数名:	CGame::CGame
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CGame::CGame()
{
	CManager *manager = GetManager();
	manager->m_Build = false;
	manager->m_MouseDraw = true;
}

//------------------------------------------------------------------------------
//	関数名:	CGame::~CGame
//	引数:	なし
//	戻り値:	CGame
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CGame::~CGame()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CGame::Init(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	m_Light = new CLight;
	m_Light->Init();

	m_Camera = new CCamera;
	m_Camera->Init();

	m_Number = new CNumber;
	m_Number->Init();

	m_LoadMap = new CLoadMap;
	m_LoadMap->Init();
	m_GameWall_001 = CGameWall_001::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 201.0f, 201.0f, GAME_TEXTURE_WALL_001_FILE);
	m_GameWall_002 = CGameWall_002::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 201.0f, 201.0f, GAME_TEXTURE_WALL_002_FILE);
	m_GameEnemy_001 = CGameEnemy_001::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_001);
	m_GameEnemy_002 = CGameEnemy_002::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_ENEMY_002);
	m_GameDoor = CGameDoor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_DOOR);
	m_GamePoint = CGamePoint::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_POINT);

	m_GameCeiling = CGameCeiling::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_CEILING_FILE);
	m_GameRobot = CGameRobot::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_GAMEROBOT);
	m_SetMap = new SetMap;
	m_SetMap->Init();

	m_sky = CSkybox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, "NULL");

	m_Bullet = CBullet::Create(D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 2.0f, TEXTURE_BULLET_FILE);
	m_Enemy_Bullet_Up = CEnemy_Bullet_Up::Create(D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, TEXTURE_ENEMY_BULLET_UP_FILE);
	m_Enemy_Bullet_Down = CEnemy_Bullet_Down::Create(D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, TEXTURE_ENEMY_BULLET_DOWN_FILE);
	m_Enemy_Bullet_Left = CEnemy_Bullet_Left::Create(D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, TEXTURE_ENEMY_BULLET_LEFT_FILE);
	m_Enemy_Bullet_Right = CEnemy_Bullet_Right::Create(D3DXVECTOR3(5000.0f, 5000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, TEXTURE_ENEMY_BULLET_RIGHT_FILE);
	CLoadMap *m_LoadMap = game->GetLoadMap();
	m_Player = CPlayer::Create(D3DXVECTOR3(m_LoadMap->m_Pos_Start[0].x, 100.0f, m_LoadMap->m_Pos_Start[0].z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, "NULL");
	m_Field = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, MESHFIELD_TEXTURE_FILE00);
	for (int i = 0; i < m_LoadMap->m_Point_num; i++)
	{
		m_Columnar[i] = CColumnar::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 30.0f, "NULL");
	}
	for (int i = 0; i < m_LoadMap->m_Door_num; i++)
	{
		m_Door_Effect[i] = CDoor_Effect::Create(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 170.0f, 170.0f, "NULL");
	}
	m_Smoke = CSmoke::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, TEXTURE_SMOKE);
	m_Explosion = CExplosion::Create(D3DXVECTOR3(0.0f, 7000-.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, TEXTURE_EXPLOSION);
	m_Glass = CGlass::Create(D3DXVECTOR3(0.0f, 7000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f,40.0f, TEXTURE_GLASS);
	m_Textbubble = CTextbubble::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 250.0f, TEXTURE_TEXTBUBBLE_FILE);
	m_TalkRobotImage = CTalkRobotImage::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT / 1.7, SCREEN_WIDTH / 2, TEXTURE_TALKROBOTIMAGE_FILE);
	m_PowerPoly = CPowerPoly::Create(D3DXVECTOR3(1075.0f, 35.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 0.0f, "NULL");
	m_HpScore = CHpScore::Create(D3DXVECTOR3(28.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 70.0f, TEXTURE_HPSCORE_FILE);
	m_HpImage = CHpImage::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, TEXTURE_HPIMAGE_FILE);
	m_PowerImage = CPowerImage::Create(D3DXVECTOR3(1170.0f, 35.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 200.0f, TEXTURE_POWERIMAGE_FILE);
	m_PowerMax = CPowerMax::Create(D3DXVECTOR3(1170.0f, 35.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180.0f, TEXTURE_POWERMAX_FILE);


#ifdef _DEBUG
	m_Debug = new CDebugProc;
	m_Debug->Init();
#endif
	
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	delete m_LoadMap;

	m_Number->Uninit();
	delete m_Number;


	m_Camera->Uninit();
	delete m_Camera;

	delete m_Light;

	m_SetMap->Uninit();
	delete m_SetMap;



	CScene::UninitAll();
#ifdef _DEBUG
	m_Debug->Uninit();
	delete m_Debug;
#endif
	
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CGame::Update(void)
{
	CManager *manager = GetManager();
	CSceneInput *m_Input = manager -> GetInput();

	m_Number->Update();
	m_Camera->Update();

	CScene::UpdateAll();
#ifdef _DEBUG
	m_Debug -> Update();
#endif

	m_LoadMap->Update();

}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGame::Draw(void)
{	

	CScene::DrawAll();
#ifdef _DEBUG
	m_Debug -> Draw();
#endif


}

CField* CGame::GetField ( void)
{
	return m_Field;
}

CCamera* CGame::GetCCamera ( void )
{
	return m_Camera;
}

CScore* CGame::GetScore ( void )
{
	return m_score;
}
CHpScore* CGame::GetHpScore(void)
{
	return m_HpScore;
}
CNumber* CGame::GetNum(void)
{
	return m_Number;
}
CEffect* CGame::GetEffect(void)
{
	return m_Effect;
}

CPlayer* CGame::GetPlayer(void)
{
	return m_Player;
}


CBullet* CGame::GetBullet(void)
{
	return m_Bullet;
}
CExplosion* CGame::GetExplosion( void)
{
	return m_Explosion;
}
CGlass* CGame::GetGlass(void)
{
	return m_Glass;
}
CSpark* CGame::GetSpark(void)
{
	return m_Spark;
}
CTime*  CGame::GetTime(void)
{
	return m_Time;
}
CTransferEffect* CGame::GetTransferEffect(void)
{
	return m_TransferEffect;
}
CGameWall_001* CGame::GetGameWall_001(void)
{
	return m_GameWall_001;
}
CGameWall_002* CGame::GetGameWall_002(void)
{
	return m_GameWall_002;
}
CGameEnemy_001* CGame::GetGameEnemy_001(void)
{
	return m_GameEnemy_001;
}
CGameEnemy_002* CGame::GetGameEnemy_002(void)
{
	return m_GameEnemy_002;
}
CBulletHoles* CGame::GetBulletHoles(void)
{
	return m_BulletHoles;
}
CEnemy* CGame::GetEnemy(void)
{
	return m_Enemy;
}
COrbit* CGame::GetOrbit(void)
{
	return m_Orbit;
}
CUnique_skill* CGame::GetUnique_skill(void)
{
	return m_Unique_skill;
}
Cskillbg* CGame::Getskillbg(void)
{
	return m_Cskillbg;
}
CSmoke* CGame::GetSmoke(void)
{
	return m_Smoke;
} 
CLoadMap* CGame::GetLoadMap(void)
{
	return m_LoadMap;
}

CGameEnemy_001_data* CGame::GetGameEnemy_001_data(void)
{
	return m_GameEnemy_001_data;
}
CEnemy_Bullet_Up* CGame::GetEnemy_Bullet_Up(void)
{
	return m_Enemy_Bullet_Up;
}
CEnemy_Bullet_Down* CGame::GetEnemy_Bullet_Down(void)
{
	return m_Enemy_Bullet_Down;
}
CEnemy_Bullet_Left* CGame::GetEnemy_Bullet_Left(void)
{
	return m_Enemy_Bullet_Left;
}
CEnemy_Bullet_Right* CGame::GetEnemy_Bullet_Right(void)
{
	return m_Enemy_Bullet_Right;
}
CEnemy_Effect* CGame::GetEnemy_Effect(void)
{
	return m_Enemy_Effect;
}
CGameCeiling* CGame::GetGameCeiling(void)
{
	return m_GameCeiling;
}
CGameDoor* CGame::GetGameDoor(void)
{
	return m_GameDoor;
}
CDoor_Effect* CGame::GetDoor_Effect(int Index)
{
	return m_Door_Effect[Index];
}
CGamePoint* CGame::GetGamePoint(void)
{
	return m_GamePoint;
}
CGameRobot* CGame::GetGameRobot(void)
{
	return m_GameRobot;
}
CColumnar* CGame::GetColumnar(int Index)
{
	return m_Columnar[Index];
}
CHpImage* CGame::GetHpImage(void)
{
	return m_HpImage;
}
CTalkRobotImage* CGame::GetTalkRobotImage(void)
{
	return m_TalkRobotImage;
}