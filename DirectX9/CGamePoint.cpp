///********************************************************************************
//* タイトル　01
//* ファイル名　CGamePoint.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GamePoint描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CGamePoint.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CGamePoint::CGamePoint()
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	CLoadMap *m_LoadMap = game->GetLoadMap();

	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ

	m_Mesh = NULL;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CGamePoint::~CGamePoint()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CGamePoint::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	CLoadMap *m_LoadMap = game->GetLoadMap();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	D3DXCreateTextureFromFile(device, "data\\TEXTURE\\point.png", &m_pTexture);// テクスチャ読み込み
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
	m_Flag = false;
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CGamePoint::Uninit(void)
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
//	関数名:	void CGamePoint::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGamePoint::Draw(void)
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
		for (int i = 0; i < m_LoadMap->m_Point_num; i++)
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
		for (int i = 0; i < m_BuildLoadMap->m_Point_num; i++)
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
//	関数名:	void CGamePoint::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGamePoint::Update(void)
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
		for (int i = 0; i < m_LoadMap->m_Point_num; i++)
		{
			if (m_data[i].m_bUse == true)
			{
			CColumnar *m_Columnar = game->GetColumnar(i);
				if (m_Columnar->m_bMove == false)
				{
					m_Columnar->m_Position.x = m_data[i].m_Position.x;
					m_Columnar->m_Position.y = m_data[i].m_Position.y + 100.0f;
					m_Columnar->m_Position.z = m_data[i].m_Position.z;
				}
			}
		}


	}
}
CGamePoint* CGamePoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CGamePoint *GamePoint;
	GamePoint = new CGamePoint;
	GamePoint->Init( pos,  rot,  height,  width, TEXTURE_FILE);
	return GamePoint;
}
void CGamePoint::SetGamePoint(D3DXVECTOR3 pos)
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
		for (int i = 0; i < m_LoadMap->m_Point_num; i++)
		{
			if (m_data[i].m_bUse == false)
			{
				m_data[i].m_Position = pos;
				m_data[i].m_bUse = true;
				break;
			}
		}
	}

	if (manager->m_Build == true)
	{
		for (int i = 0; i < m_BuildLoadMap->m_Point_num; i++)
		{
			if (m_data[i].m_bUse == false)
			{
				m_data[i].m_Position = pos;
				m_data[i].m_bUse = true;
				break;
			}
		}
	}
}
CGamePoint_data* CGamePoint::Get(int Index)
{
	return &m_data[Index];
}
float  CGamePoint::Length(D3DXVECTOR3 *Vector)
{
	float len = sqrtf(Vector->x * Vector->x +
		Vector->y * Vector->y +
		Vector->z * Vector->z);

	return len;

}