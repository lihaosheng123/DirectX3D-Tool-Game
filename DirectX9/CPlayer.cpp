/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　sceneX.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/25
Xポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "sceneX.h"
#include "CField.h"
#include "manager.h"
#include "CPlayer.h"
//////////////
//REVOLVER初期化数値
/*
	{40,//Frame数
   {{0.0f,50.0f,0.0f,0.0f,0.0f,0.0f},
	{-0.8f,-7.0f,12.0f,0.0f,0.0f,0.0f},

	{11.5f,9.5f,13.5f,0.0f,0.0f,0.0f},
	{0.7f,4.0f,6.0f,0.0f,0.0f,0.0f},

	{5.0f,8.7f,26.0f,0.0f,0.0f,0.0f},
	{-1.5f,6.4f,7.0f,0.0f,0.0f,0.0f},


	{-1.0f,8.0f,27.5f,0.0f,0.0f,0.0f},
	{-1.4f,4.6f,7.0f,0.0f,0.0f,0.0f},

	{-7.5f,8.5f,25.0f,0.0f,0.0f,0.0f},
	{-1.0f,5.0f,5.0f,0.0f,0.0f,0.0f},

	{-10.0f,7.7f,20.0f,0.0f,0.0f,0.0f},
	{-3.5f,1.8f,6.3f,0.0f,0.0f,0.0f},
								}},
								*/
/*
{50,//Frame数
{{10.0f,-0.5f,-3.0f,0.0f,0.0f,0.0f},//
{-0.3f,7.0f,28.0f,0.0f,-0.2f,0.0f},//

{-2.0f,4.0f,14.0f,0.0f,0.0f,0.0f},//

{0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f},//
{-1.0f,6.8f,4.5f,0.0f,0.0f,0.0f},//

{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
}}
	*/
/*Revolverモデル位置開始*/
KEY_INFO_REVOLVER g_KeyNeutral[]=
{
	{60,//Frame数
   {{5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f},//
	{-0.3f,7.0f,28.0f,0.0f,0.0f,0.0f},//

	{-2.0f,4.0f,14.0f,0.0f,0.0f,0.0f},//

	{0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f},//
	{-1.0f,6.8f,4.5f,0.0f,0.0f,0.0f},//

	{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
	}},

{60,//Frame数
{ { 5.0f,0.0f,-4.0f,0.f,0.0f,0.0f },//
{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
}}

};

KEY_INFO_REVOLVER g_Shoot[] =
{
	{ 3,//Frame数
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },

	{ 10,//Frame数
	{ { 5.0f,-0.2f,-6.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,-0.4f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },

	{ 5,//Frame数
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },


	{ 10,//Frame数
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} }
};

KEY_INFO_REVOLVER g_SixShoot[] =
{
	{ 2,//Frame数
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },

	{ 10,//Frame数
	{ { 5.0f,0.2f,-6.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,-0.5f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },

	{ 3,//Frame数
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//

	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} }
};
KEY_INFO_REVOLVER g_KeyRun[]=
{
	{15,//Frame数0
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{-2.0f,4.0f,14.0f,0.0f,0.0f,0.0f},//

	{0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f},//
	{-1.0f,6.8f,4.5f,0.0f,0.0f,0.0f},//

	{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
	}},


	{15,//Frame数1
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//

	{-2.0f,4.0f,14.0f,0.4f,0.0f,0.0f},//
	
	{0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f},//
	{-1.0f,6.8f,4.5f,0.0f,0.0f,0.0f},//
	{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
	}},


	{15,//Frame数2
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{-2.0f,4.0f,14.0f,0.4f,0.0f,0.0f},//
	
	{0.0f,-1.5f,-4.0f,0.0f,0.0f,1.57f},//
	{-1.0f,6.8f,4.5f,0.0f,0.0f,0.0f},//
	{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
	}},
	

	{15,//Frame数3
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{-2.0f,4.0f,14.0f,0.4f,0.0f,0.0f},//
	
	{0.0f,-1.5f,-4.0f,0.0f,0.0f,1.57f},//
	{-1.0f,6.8f,4.5f,-1.0f,0.0f,0.0f},//
	{-0.7f,1.4f,8.7f,0.0f,0.0f,0.0f},//
	}},


	{15,//Frame数4
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{-2.0f,4.0f,14.0f,0.4f,0.0f,0.0f},//
	
	{0.0f,-1.5f,-4.0f,0.0f,0.0f,1.57f},//
	{-1.0f,6.8f,4.5f,-1.0f,0.0f,0.0f},//
	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	}},

	{15,//Frame数5
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{ -2.0f,4.0f,14.0f,0.4f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,-1.0f,0.0f,0.0f },//
	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	}},

	{ 15,//Frame数6
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{ -2.0f,4.0f,14.0f,0.4f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//
	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} },

	{ 15,//Frame数7
	{ { 5.0f,-0.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -0.3f,7.0f,28.0f,0.0f,0.0f,0.0f },//
	{ -2.0f,4.0f,14.0f,0.0f,0.0f,0.0f },//

	{ 0.0f,-1.5f,-4.0f,0.0f,0.0f,0.0f },//
	{ -1.0f,6.8f,4.5f,0.0f,0.0f,0.0f },//
	{ -0.7f,1.4f,8.7f,0.0f,0.0f,0.0f },//
	} }
};
/*Machineモデル位置開始*/
KEY_INFO_MACHINEGUN g_Machine_KeyNeutral[] =
{
	{ 60,
	{ { 5.0f,-0.5f,7.0f,0.0f,0.0f,0.0f },//
	} },

	{ 60,
	{ { 5.0f,0.0f,7.0f,0.0f,0.0f,0.0f },//
	} }
};
/*Machineモデル位置終了*/

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	for(int i = 0;i<6;i++)
	{
		m_RevolverModel[i] = new CRevolverModel;
		m_RevolverModel[i]->m_Mesh = NULL;                  // メッシュの情報
	}
	for (int i = 0; i<1; i++)
	{
		m_MachineModel[i] = new CModel;
		m_MachineModel[i]->m_Mesh = NULL;                  // メッシュの情報
	}

	m_Numjia = false;
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_Repeating = false;
	m_Dead = false;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *m_Camera = game->GetCCamera();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	m_Camera->m_3DPos = D3DXVECTOR3(m_LoadMap->m_Pos_Start[0].x,100.0f, m_LoadMap->m_Pos_Start[0].z);
/*Revolverモデル読み込み開始*/
	m_RevolverModel[0] = CRevolverModel::Create("data\\MODEL\\GUN\\hand_shoubi.x");
	m_RevolverModel[1] = CRevolverModel::Create("data\\MODEL\\GUN\\gun00.x");
	m_RevolverModel[2] = CRevolverModel::Create("data\\MODEL\\GUN\\gun01.x");
	m_RevolverModel[3] = CRevolverModel::Create("data\\MODEL\\GUN\\gun02.x");
	m_RevolverModel[4] = CRevolverModel::Create("data\\MODEL\\GUN\\gun03.x");
	m_RevolverModel[5] = CRevolverModel::Create("data\\MODEL\\GUN\\gun04.x");


	m_RevolverModel[0]->SetParent(NULL);	// 頂点座標

	m_RevolverModel[1]->SetParent(m_RevolverModel[0]);	// 頂点座標

	m_RevolverModel[2]->SetParent(m_RevolverModel[1]);	// 頂点座標
	m_RevolverModel[3]->SetParent(m_RevolverModel[2]);	// 頂点座標

	m_RevolverModel[4]->SetParent(m_RevolverModel[1]);	// 頂点座標

	m_RevolverModel[5]->SetParent(m_RevolverModel[1]);	// 頂点座標
/*Revolverモデル読み込み終了*/

/*MachineModelモデル読み込み開始*/
	m_MachineModel[0] = CModel::Create("data\\MODEL\\GUN\\SciFiRifle.x");
	m_MachineModel[0]->SetParent(NULL);	// 頂点座標
/*MachineModelモデル読み込み終了*/

	// モデルの初期設定
	m_Position = D3DXVECTOR3(m_LoadMap->m_Pos_Start[0].x,100.0f, m_LoadMap->m_Pos_Start[0].z);	// 頂点座標
	m_OldPos = D3DXVECTOR3(m_LoadMap->m_Pos_Start[0].x, 100.0f, m_LoadMap->m_Pos_Start[0].z);	// 頂点座標
	m_Rotation = D3DXVECTOR3(rot.x,rot.y,rot.z);	// 回転

	m_scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
	m_frame = 0;
	m_Power = 0;
	cnt = 0;
	m_HP = 50;
	m_time_Power = 0;
	m_Hp_Time = 0;
	m_type = GUN_MACHINEGUNS;
	SetMotion(MOTIONTYPE_NEUTRAL);
	return S_OK;
}

//================================================================================================================================================================================================
// Uninit関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CPlayer::Uninit( void )
{
	//RELEASE(m_pTexture);

		for (int i = 0; i < 6; i++)
		{
			RELEASE(m_RevolverModel[i]->m_Mesh);
		}

		for (int i = 0; i < 1; i++)
		{
			RELEASE(m_MachineModel[i]->m_Mesh);
		}
}

//================================================================================================================================================================================================
// Update関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CPlayer::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CSceneMouse *m_Mouse = manager->GetMouse();
	CRenderer *renderer = manager->GetRenderer();

	CCamera *m_Camera = game->GetCCamera();

	CUnique_skill *m_Unique_skill = game->GetUnique_skill();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CScore *m_Score = game->GetScore();
	COrbit *m_Orbit = game->GetOrbit();
	CBullet *m_Bullet = game->GetBullet();
	Cskillbg *m_skillbg = game->Getskillbg();

	CSpark *m_Spark = game->GetSpark();
	CHpScore *m_HpScore = game->GetHpScore();
	CGameWall_001 *m_Wall_001 = game->GetGameWall_001();
	CGameWall_002 *m_Wall_002 = game->GetGameWall_002();
	CGameEnemy_001 *m_Enemy_001 = game->GetGameEnemy_001();
	CGameEnemy_002 *m_Enemy_002 = game->GetGameEnemy_002();
	CGameCeiling *m_Ceiling = game->GetGameCeiling();
	CGamePoint *m_Point = game->GetGamePoint();
	CGameDoor *m_Door = game->GetGameDoor();
	CDoor_Effect *m_Door_Effect = game->GetDoor_Effect(0);
	if (m_Power >= 100)
	{
		m_Power = 100;
	}
	if (m_Power <= 0)
	{
		m_Power = 0;
	}
	if (m_HP >= 50)
	{
		m_HP = 50;
	}
	if (m_HP <= 0)
	{
		m_HP = 0;
	}
	if (m_time_Power > 60)
	{
		m_HP += 1.0f;
		m_Power += 1.0f;
		m_time_Power = 0;
	}
	else
	{
		m_time_Power+= 1.0f;
	}

	if (m_Hp_Time > 120)
	{
		m_HpScore->AddScore(1);
		m_Hp_Time = 0;
	}	
	else
	{
		m_Hp_Time += 1.0f;
	}
	//ゲーム終了条件
	if (m_OldPos.x <= m_LoadMap->m_Pos_End[0].x + 200.0f &&
		m_OldPos.x >= m_LoadMap->m_Pos_End[0].x - 200.0f &&
		m_OldPos.z <= m_LoadMap->m_Pos_End[0].z + 200.0f &&
		m_OldPos.z >= m_LoadMap->m_Pos_End[0].z - 200.0f)
	{
		CManager::SetMode(CManager::MODE_TITLE);
	}
	if (m_HP <= 0 && m_Dead == false)
	{
		m_Dead = true;
	}

	if(m_Position.y <= 0)
		{
			m_Position.y = 0;
		}
	if (m_HP > 0 && m_Dead == false)
	{
		UpdateMotion();
		if (m_Input->GetKeyboardPress(DIK_W))
		{
			if (m_Input->GetKeyboardPress(DIK_A))				//左上移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI * 0.75f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI * 0.75f) * MODEL_MOVE;

			}
			else if ((m_Input->GetKeyboardPress(DIK_D)))	//右上移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y - D3DX_PI * 0.75f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y - D3DX_PI * 0.75f) * MODEL_MOVE;


			}
			else											//前移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI) * MODEL_MOVE;


			}

			//カリング
		}
		else if (m_Input->GetKeyboardPress(DIK_S))
		{
			if (m_Input->GetKeyboardPress(DIK_A))				//左下移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI * 0.25f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI * 0.25f) * MODEL_MOVE;

			}
			else if ((m_Input->GetKeyboardPress(DIK_D)))	//右下移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y - D3DX_PI * 0.25f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y - D3DX_PI * 0.25f) * MODEL_MOVE;

			}
			else											//後移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y) * MODEL_MOVE;

			}


		}
		else if (m_Input->GetKeyboardPress(DIK_A))
		{
			if (m_Input->GetKeyboardPress(DIK_W))				//左上移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI * 0.75f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI * 0.75f) * MODEL_MOVE;

			}
			else if ((m_Input->GetKeyboardPress(DIK_S)))		//左下移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI * 0.25f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI * 0.25f) * MODEL_MOVE;


			}
			else											//左移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y + D3DX_PI * 0.5f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y + D3DX_PI * 0.5f) * MODEL_MOVE;


			}


		}
		else if (m_Input->GetKeyboardPress(DIK_D))
		{
			if (m_Input->GetKeyboardPress(DIK_W))				//右上移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y - D3DX_PI * 0.75f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y - D3DX_PI * 0.75f) * MODEL_MOVE;

			}
			else if ((m_Input->GetKeyboardPress(DIK_S)))		//右下移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y - D3DX_PI * 0.25f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y - D3DX_PI * 0.25f) * MODEL_MOVE;

			}
			else											//右移動
			{
				m_OldPos.x -= sinf(m_Camera->rot.y - D3DX_PI * 0.5f) * MODEL_MOVE;
				m_OldPos.z -= cosf(m_Camera->rot.y - D3DX_PI * 0.5f) * MODEL_MOVE;

			}

		}

		//向き角度のチェック
		if (m_Rotation.y > D3DX_PI)
		{
			m_Rotation.y -= D3DX_PI * 2.0f;
		}
		else if (m_Rotation.y < -D3DX_PI)
		{
			m_Rotation.y += D3DX_PI * 2.0f;
		}

		if (m_Input->GetKeyboardTrigger(DIK_1))
		{
			m_type = GUN_REVOLVER;
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if (m_Input->GetKeyboardTrigger(DIK_2))
		{
			m_type = GUN_MACHINEGUNS;
			SetMotion(MOTIONTYPE_NEUTRAL);
		}
		switch (m_type)
		{
		case GUN_REVOLVER:
			if (m_Input->GetKeyboardTrigger(DIK_R) && m_MotionType != MOTIONTYPE_RUN && m_Bullet->m_Num < 6)
			{
				SetMotion(MOTIONTYPE_RUN);
			}
			if (m_MotionType != MOTIONTYPE_RUN && m_Bullet->m_Num <= 0 && m_MotionType != MOTIONTYPE_ATTACK&& m_MotionType != MOTIONTYPE_SIXATTACK)
			{
				SetMotion(MOTIONTYPE_RUN);
			}
			if (m_Numjia == true)
			{
				m_Bullet->m_Num = 6;
				SetMotion(MOTIONTYPE_NEUTRAL);
				m_Numjia = false;
			}
			// It's Highhhhhhhhhhhhhhhhhhhhh Noon!
			//if (m_Input->GetKeyboardTrigger(DIK_Q) &&/* m_Unique_skill->m_CheckUse == false*/m_Power == 100)
			//{
			//	m_Power = 0;
			//	//m_Unique_skill->SetUnique_skill(D3DXVECTOR3(m_Fox->m_Position.x, m_Fox->m_Position.y + 130.0f, m_Fox->m_Position.z));
			//	m_Unique_skill->m_bgUse = true;
			//}
			//普通の攻撃
			if (m_Mouse->GetMouseTrigger(DIM_LEFT) && m_MotionType == MOTIONTYPE_NEUTRAL && m_Bullet->m_Num > 0 && m_MotionType != MOTIONTYPE_ATTACK)
			{
				SetMotion(MOTIONTYPE_ATTACK);

				m_Bullet->SetBullet(D3DXVECTOR3(m_Camera->m_posV.x, (m_Camera->m_posV.y), m_Camera->m_posV.z));
				m_Bullet->m_Num -= 1;
			}
			//特別の攻撃
			if (m_Mouse->GetMouseTrigger(DIM_RIGHT) && m_MotionType == MOTIONTYPE_NEUTRAL && m_Bullet->m_Num > 0)
			{
				m_Repeating = true;
			}
			if (m_Bullet->m_Num <= 0)
			{
				m_Repeating = false;
			}
			if (m_Repeating == true)
			{
				if (m_frame > (15 * 6))
				{
					m_frame = 0;
				}
				else
				{
					m_frame++;
				}
				for (int i = 0; i < 6; i++)
				{
					if (m_frame == 15 * i)
					{
						SetMotion(MOTIONTYPE_SIXATTACK);
						m_Bullet->SetBullet(D3DXVECTOR3(m_Camera->m_posV.x, (m_Camera->m_posV.y), m_Camera->m_posV.z));
						m_Bullet->m_Num -= 1;
					}
				}
			}
			break;

		case GUN_MACHINEGUNS:
			if (m_Mouse->GetMousePress(DIM_LEFT))
			{
				if (cnt > 10)
				{
					m_Bullet->SetBullet(D3DXVECTOR3(m_Camera->m_posV.x, (m_Camera->m_posV.y), m_Camera->m_posV.z));
					cnt = 0;
				}
				else
				{
					cnt++;
				}
			}
			break;

		default:
			break;

		}
		//	m_Position.x = m_OldPos.x;
		//	m_Position.z = m_OldPos.z;
			//座標を更新（慣性）
		m_Position.x += (m_OldPos.x - m_Position.x) * 0.095f;
		m_Position.z += (m_OldPos.z - m_Position.z) * 0.095f;
	}
	if (m_Dead == true  && m_HP <= 0)
	{
		m_Rotation.z -= 0.025f;
		if (m_Rotation.z <= -1.57f)
		{
			m_Rotation.z = -1.57f;
		}
		
	}
}

//================================================================================
//================================================================================================================
// Draw関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CPlayer::Draw( void )
{
		CManager *manager = GetManager();

		CRenderer *renderer = manager->GetRenderer();

		LPDIRECT3DDEVICE9 device = renderer->GetDevice();
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Matrix.World);

		// スケールを反映
		D3DXMatrixScaling(&m_Matrix.Scl, m_scl.x, m_scl.y, m_scl.z);
		D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&m_Matrix.Rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot);

		// 位置を反映
		D3DXMatrixTranslation(&m_Matrix.Trans, m_Position.x, m_Position.y, m_Position.z);
		D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans);

		// ワールドマトリックスを設定
		device->SetTransform(D3DTS_WORLD, &m_Matrix.World);

		switch (m_type)
		{
		case GUN_REVOLVER:
			for (int i = 0; i < 6; i++)
			{
				m_RevolverModel[i]->Draw();
			}
			break;

		case GUN_MACHINEGUNS:
			for (int i = 0; i < 1; i++)
			{
				m_MachineModel[i]->Draw();
			}
			break;

		default:
			break;
		}
		// レンダーステートの設定をデフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
		// ライト点灯
		device->SetRenderState(D3DRS_LIGHTING, TRUE);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	
}
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CPlayer *GunManager;
	GunManager = new CPlayer;
	GunManager->Init(pos,rot,height ,width,TEXTURE_FILE);
	return GunManager;
}
float  CPlayer::Length( D3DXVECTOR3 *Vector )
{

	float len = sqrtf( Vector->x * Vector->x +
						Vector->y * Vector->y +
						Vector->z * Vector->z );

	return len;

}

void CPlayer::Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 )
{

	*Vector = *Vector1 / Length( Vector1 );

}

void CPlayer::SetMotion(MOTIONTYPE MotionType)
{
	switch (m_type)
	{
	case GUN_REVOLVER:
		switch (MotionType)
		{
		case MOTIONTYPE_NEUTRAL:
		{
			m_KeyInfo_Revolver = g_KeyNeutral;
			m_NumKey = 2;
			m_stopMotion = MOTIONTYPE_NEUTRAL;
			break;
		}

		case MOTIONTYPE_RUN:
		{
			m_KeyInfo_Revolver = g_KeyRun;
			m_NumKey = 8;
			m_stopMotion = MOTIONTYPE_RUN;
			break;
		}

		case MOTIONTYPE_ATTACK:
		{
			m_KeyInfo_Revolver = g_Shoot;
			m_NumKey = 4;
			m_stopMotion = MOTIONTYPE_ATTACK;
			break;
		}

		case MOTIONTYPE_SIXATTACK:
		{
			m_KeyInfo_Revolver = g_SixShoot;
			m_NumKey = 3;
			m_stopMotion = MOTIONTYPE_SIXATTACK;
			break;
		}


		}
		m_Key = 0;
		m_Frame = 0;
		m_MotionType = MotionType;
		break;

	case GUN_MACHINEGUNS:
		switch (MotionType)
		{
		case MOTIONTYPE_NEUTRAL:
		{
			m_KeyInfo_Machinegun = g_Machine_KeyNeutral;
			m_NumKey = 2;
			m_stopMotion = MOTIONTYPE_NEUTRAL;
			break;
		}
		}
		m_Key = 0;
		m_Frame = 0;
		m_MotionType = MotionType;
		break;


	default:
		break;
	}
}
void CPlayer::UpdateMotion( void )
{

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CSceneInput *m_Input = manager -> GetInput();
	CField *meshField = game -> GetField();
	CSceneMouse *m_Mouse = manager -> GetMouse();
	CRenderer *renderer = manager -> GetRenderer();

	
	CCamera *m_Camera = game->GetCCamera();

	CScore *m_Score = game ->GetScore();


	
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	switch (m_type)
	{
	case GUN_REVOLVER:
		for (int i = 0; i < 6; i++)
		{
			KEY *key, *keyNext;
			float rate;
			D3DXVECTOR3 pos, rot;

			//補間用
			key = &m_KeyInfo_Revolver[m_Key].m_Revolver_Key[i];		//前のキー
			keyNext = &m_KeyInfo_Revolver[(m_Key + 1) % m_NumKey].m_Revolver_Key[i];		//次キー
			rate = (float)m_Frame / m_KeyInfo_Revolver[m_Key].Frame;

			//線形補間
			pos.x = key->PositionX * (1.0f - rate) + keyNext->PositionX * rate;
			pos.y = key->PositionY * (1.0f - rate) + keyNext->PositionY * rate;
			pos.z = key->PositionZ * (1.0f - rate) + keyNext->PositionZ * rate;
			rot.x = key->RotationX * (1.0f - rate) + keyNext->RotationX * rate;
			rot.y = key->RotationY * (1.0f - rate) + keyNext->RotationY * rate;
			rot.z = key->RotationZ * (1.0f - rate) + keyNext->RotationZ * rate;

			m_RevolverModel[i]->SetPosition(pos);
			m_RevolverModel[i]->SetRotation(rot);

		}
		switch (m_stopMotion)
		{
		case  MOTIONTYPE_NEUTRAL:
			m_Frame++;
			if (m_Frame >= m_KeyInfo_Revolver[m_Key].Frame)
			{
				m_Key = (m_Key + 1) % m_NumKey;
				m_Frame = 0;
			}
			break;
		case MOTIONTYPE_RUN:
			if (m_Key <= m_NumKey - 2)
			{
				m_Frame++;
				if (m_Frame >= m_KeyInfo_Revolver[m_Key].Frame)
				{
					m_Key = (m_Key + 1) % m_NumKey;
					m_Frame = 0;
				}
			}
			else
			{
				m_Key = m_NumKey - 2;
				m_Frame = m_KeyInfo_Revolver[m_Key].Frame;
				SetMotion(MOTIONTYPE_NEUTRAL);
				m_Numjia = true;
			}
			break;
		case MOTIONTYPE_ATTACK:
			if (m_Key <= m_NumKey - 2)
			{
				m_Frame++;
				if (m_Frame >= m_KeyInfo_Revolver[m_Key].Frame)
				{
					m_Key = (m_Key + 1) % m_NumKey;
					m_Frame = 0;
				}
			}
			else
			{
				m_Key = m_NumKey - 2;
				m_Frame = m_KeyInfo_Revolver[m_Key].Frame;
				SetMotion(MOTIONTYPE_NEUTRAL);
			}
			break;

		case MOTIONTYPE_SIXATTACK:
			if (m_Key <= m_NumKey - 2)
			{
				m_Frame++;
				if (m_Frame >= m_KeyInfo_Revolver[m_Key].Frame)
				{
					m_Key = (m_Key + 1) % m_NumKey;
					m_Frame = 0;
				}
			}
			else
			{
				m_Key = m_NumKey - 2;
				m_Frame = m_KeyInfo_Revolver[m_Key].Frame;
				SetMotion(MOTIONTYPE_NEUTRAL);
			}
			break;

		default:
			break;
		}
		break;
/********************************************************************/
	case GUN_MACHINEGUNS:
		for (int i = 0; i < 1; i++)
		{
			KEY *key, *keyNext;
			float rate;
			D3DXVECTOR3 pos, rot;

			//補間用
			key = &m_KeyInfo_Machinegun[m_Key].m_MachineGuns_key[i];		//前のキー
			keyNext = &m_KeyInfo_Machinegun[(m_Key + 1) % m_NumKey].m_MachineGuns_key[i];		//次キー
			rate = (float)m_Frame / m_KeyInfo_Machinegun[m_Key].Frame;

			//線形補間
			pos.x = key->PositionX * (1.0f - rate) + keyNext->PositionX * rate;
			pos.y = key->PositionY * (1.0f - rate) + keyNext->PositionY * rate;
			pos.z = key->PositionZ * (1.0f - rate) + keyNext->PositionZ * rate;
			rot.x = key->RotationX * (1.0f - rate) + keyNext->RotationX * rate;
			rot.y = key->RotationY * (1.0f - rate) + keyNext->RotationY * rate;
			rot.z = key->RotationZ * (1.0f - rate) + keyNext->RotationZ * rate;

			m_MachineModel[i]->SetPosition(pos);
			m_MachineModel[i]->SetRotation(rot);

		}
		switch (m_stopMotion)
		{
		case  MOTIONTYPE_NEUTRAL:
			m_Frame++;
			if (m_Frame >= m_KeyInfo_Machinegun[m_Key].Frame)
			{
				m_Key = (m_Key + 1) % m_NumKey;
				m_Frame = 0;
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}



}