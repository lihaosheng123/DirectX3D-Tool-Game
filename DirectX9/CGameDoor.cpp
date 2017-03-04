///********************************************************************************
//* タイトル　01
//* ファイル名　CGameDoor.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameDoor描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CGameDoor.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CGameDoor::CGameDoor()
{

	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ

	m_Mesh = NULL;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CGameDoor::~CGameDoor()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CGameDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	CLoadMap *m_LoadMap = game->GetLoadMap();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	D3DXCreateTextureFromFile(device, "data\\TEXTURE\\door.png", &m_pTexture);// テクスチャ読み込み
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_FILE,
		D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。
		device,
		NULL,
		&m_BuffMat,		// マテリアル情報
		NULL,
		&m_nNumMat,			// マテリアル数
		&m_Mesh)))		// メッシュ情報
	{
		return E_FAIL;
	}
	m_warp = 5;
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CGameDoor::Uninit(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CLoadMap *m_LoadMap = game->GetLoadMap();

			RELEASE(m_pTexture);
			RELEASE(m_BuffMat);
			RELEASE(m_Mesh);

}
//------------------------------------------------------------------------------
//	関数名:	void CGameDoor::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGameDoor::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Door_num; i++)
		{
			if (m_data[i].m_bUse == true)
			{
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&m_data[i].Matrix.World);


				// スケールを反映
				D3DXMatrixScaling(&m_data[i].Matrix.Scl, m_data[i].m_scl.x, m_data[i].m_scl.y, m_data[i].m_scl.z);
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Scl);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&m_data[i].Matrix.Rot, m_data[i].m_Rotation.y, m_data[i].m_Rotation.x, m_data[i].m_Rotation.z);	// y,x,z
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Rot);

				// 位置を反映
				D3DXMatrixTranslation(&m_data[i].Matrix.Trans, m_data[i].m_Position.x, m_data[i].m_Position.y, m_data[i].m_Position.z);
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Trans);

				// ワールドマトリックスを設定
				device->SetTransform(D3DTS_WORLD, &m_data[i].Matrix.World);
				D3DXMATERIAL *pMat;		// マテリアル情報
				D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。


										// 現在のマテリアル情報を取得する。
				device->GetMaterial(&matDef);
				// レンダーステートの設定（zテスト）
				device->SetRenderState(D3DRS_ZENABLE, TRUE);
				device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新
																		// レンダーステートの設定（アルファテスト）


																		//モデルに明るになる
				device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
				device->SetRenderState(D3DRS_SPECULARENABLE, true);

				// キャスト変換
				pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
				{
					// マテリアルの設定
					device->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					device->SetTexture(0, m_pTexture);
					// メッシュの描画
					m_Mesh->DrawSubset(nCntMat);
				}
				// レンダーステートの設定をデフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																				// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
				device->SetMaterial(&matDef);
			}
		}
	}

	if (manager->m_Build == true)
	{
		for (int i = 0; i < m_BuildLoadMap->m_Door_num; i++)
		{
			if (m_data[i].m_bUse == true)
			{
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&m_data[i].Matrix.World);


				// スケールを反映
				D3DXMatrixScaling(&m_data[i].Matrix.Scl, m_data[i].m_scl.x, m_data[i].m_scl.y, m_data[i].m_scl.z);
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Scl);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&m_data[i].Matrix.Rot, m_data[i].m_Rotation.y, m_data[i].m_Rotation.x, m_data[i].m_Rotation.z);	// y,x,z
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Rot);

				// 位置を反映
				D3DXMatrixTranslation(&m_data[i].Matrix.Trans, m_data[i].m_Position.x, m_data[i].m_Position.y, m_data[i].m_Position.z);
				D3DXMatrixMultiply(&m_data[i].Matrix.World, &m_data[i].Matrix.World, &m_data[i].Matrix.Trans);

				// ワールドマトリックスを設定
				device->SetTransform(D3DTS_WORLD, &m_data[i].Matrix.World);
				D3DXMATERIAL *pMat;		// マテリアル情報
				D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。


										// 現在のマテリアル情報を取得する。
				device->GetMaterial(&matDef);
				// レンダーステートの設定（zテスト）
				device->SetRenderState(D3DRS_ZENABLE, TRUE);
				device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新
																		// レンダーステートの設定（アルファテスト）


																		//モデルに明るになる
				device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
				device->SetRenderState(D3DRS_SPECULARENABLE, true);

				// キャスト変換
				pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
				{
					// マテリアルの設定
					device->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					device->SetTexture(0, m_pTexture);
					// メッシュの描画
					m_Mesh->DrawSubset(nCntMat);
				}
				// レンダーステートの設定をデフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																				// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
				device->SetMaterial(&matDef);
			}
		}
	}

}
//------------------------------------------------------------------------------
//	関数名:	void CGameDoor::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGameDoor::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CEnemy_Bullet_Up *m_Enemy_Bullet_Up = game->GetEnemy_Bullet_Up();
	CEnemy_Bullet_Down *m_Enemy_Bullet_Down = game->GetEnemy_Bullet_Down();
	CEnemy_Bullet_Left *m_Enemy_Bullet_Left = game->GetEnemy_Bullet_Left();
	CEnemy_Bullet_Right *m_Enemy_Bullet_Right = game->GetEnemy_Bullet_Right();
	CPlayer *m_Player = game->GetPlayer();
	CScore *m_Score = game->GetScore();
	CEnemy_Effect *m_Enemy_Effect = game->GetEnemy_Effect();

	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();

	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Door_num; i++)
		{
			CDoor_Effect *m_Door_Effect = game->GetDoor_Effect(i);
			if (m_data[i].m_bUse == true)
			{
				m_Door_Effect->m_Position = m_data[i].m_Position;
				m_Door_Effect->m_Rotation = m_data[i].m_Rotation;
				if(m_data[i].m_bEffectUse == true)
				{
					//当たり判定
					if (m_Player->m_OldPos.x <= (m_Door_Effect->m_Position.x + m_warp) &&
						m_Player->m_OldPos.x >= (m_Door_Effect->m_Position.x - m_warp) &&
						(m_Door_Effect->m_Position.z + 100.0f + m_warp) >= m_Player->m_OldPos.z &&
						m_Player->m_OldPos.z >= (m_Door_Effect->m_Position.z - 100.0f - m_warp) &&
						(m_Door_Effect->m_Rotation.y == -1.57f))
					{
						m_Player->m_OldPos.x = (m_Door_Effect->m_Position.x + m_warp);
					}

					if (m_Player->m_OldPos.x >= (m_Door_Effect->m_Position.x - m_warp) &&
						m_Player->m_OldPos.x <= (m_Door_Effect->m_Position.x + m_warp) &&
						(m_Door_Effect->m_Position.z + 100.0f + m_warp) >= m_Player->m_OldPos.z &&
						m_Player->m_OldPos.z >= (m_Door_Effect->m_Position.z - 100.0f - m_warp) &&
						(m_Door_Effect->m_Rotation.y == 1.57f))
					{
						m_Player->m_OldPos.x = (m_Door_Effect->m_Position.x - m_warp);
					}

					if (m_Player->m_OldPos.z >= (m_Door_Effect->m_Position.z - m_warp) &&
						m_Player->m_OldPos.z <= (m_Door_Effect->m_Position.z + m_warp) &&
						(m_Door_Effect->m_Position.x + 100.0f + m_warp) >= m_Player->m_OldPos.x &&
						m_Player->m_OldPos.x >= (m_Door_Effect->m_Position.x - 100.0f - m_warp) &&
						(m_Door_Effect->m_Rotation.y == 0.0f))
					{

						m_Player->m_OldPos.z = (m_Door_Effect->m_Position.z - m_warp);
					}


					if (m_Player->m_OldPos.z <= (m_Door_Effect->m_Position.z + m_warp) &&
						m_Player->m_OldPos.z >= (m_Door_Effect->m_Position.z - m_warp) &&
						(m_Door_Effect->m_Position.x + 100.0f + m_warp) >= m_Player->m_OldPos.x &&
						m_Player->m_OldPos.x >= (m_Door_Effect->m_Position.x - 100.0f - m_warp) &&
						(m_Door_Effect->m_Rotation.y == 3.14f))
					{
						m_Player->m_OldPos.z = (m_Door_Effect->m_Position.z + m_warp);
					}
				}

				if (m_Player->m_Power >= 100)
				{
					D3DXVECTOR3 vpe = m_Player->m_Position - m_data[i].m_Position;
					vpe.y = 0.0f;
					if (Length(&vpe) < 150.0f)
					{
						if (m_Input->GetKeyboardTrigger(DIK_T))
						{
							m_Door_Effect->m_bUse = false;
							m_data[i].m_bEffectUse = false;
							m_Player->m_Power = 0;
						}
					}
				}
			}
		}
	}
}
CGameDoor* CGameDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CGameDoor *GameDoor;
	GameDoor = new CGameDoor;
	GameDoor->Init(pos, rot, height, width, TEXTURE_FILE);
	return GameDoor;
}
void CGameDoor::SetGameDoor(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Door_num; i++)
		{
			if (m_data[i].m_bUse == false)
			{
				m_data[i].m_Position = pos;
				m_data[i].m_Rotation = rot;
				m_data[i].m_bUse = true;
				break;
			}
		}
	}

	if (manager->m_Build == true)
	{
		for (int i = 0; i < m_BuildLoadMap->m_Door_num; i++)
		{
			if (m_data[i].m_bUse == false)
			{
				m_data[i].m_Position = pos;
				m_data[i].m_Rotation = rot;
				m_data[i].m_bUse = true;
				break;
			}
		}
	}
}
CGameDoor_data* CGameDoor::Get(int Index)
{
	return &m_data[Index];
}
float  CGameDoor::Length(D3DXVECTOR3 *Vector)
{
	float len = sqrtf(Vector->x * Vector->x +
		Vector->y * Vector->y +
		Vector->z * Vector->z);

	return len;

}