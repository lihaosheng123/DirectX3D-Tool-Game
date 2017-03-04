/********************************************************************************
* タイトル　
* ファイル名　CGameWall_002.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/01/12

********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "CGameWall_002.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CGameWall_002::CGameWall_002()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CGameWall_002::~CGameWall_002()
{

}
CGameWall_002* CGameWall_002::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CGameWall_002 *m_GameWall_002;
	m_GameWall_002 = new CGameWall_002;
	m_GameWall_002->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_GameWall_002;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CGameWall_002::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
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
		//頂点バッファの生成
		if (FAILED(device->CreateVertexBuffer(
			sizeof(VERTEX_3D) * m_LoadMap->m_Wall002_num * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuffer,
			NULL
		)))
		{
			return E_FAIL;
		}
		m_width = width;
		m_height = height;
		D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);

		//フィールド頂点バッファの初期化
		VERTEX_3D *pVtx;

		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
		for (int i = 0; i < m_LoadMap->m_Wall002_num; i++, pVtx += 4)
		{
			pVtx[0].pos = D3DXVECTOR3(-m_width / 2, m_height, 0.0f);	// 頂点座標
			pVtx[1].pos = D3DXVECTOR3(m_width / 2, m_height, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, 0.0f);

			// 頂点色設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


			//UV設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);



			// 座標変換済み頂点設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		}
		/* 頂点情報 カギ締め */
		m_pVtxBuffer->Unlock();
		m_warp = 15;
	}

	if (manager->m_Build == true)
	{
		//頂点バッファの生成
		if (FAILED(device->CreateVertexBuffer(
			sizeof(VERTEX_3D) * m_BuildLoadMap->m_Wall002_num * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuffer,
			NULL
		)))
		{
			return E_FAIL;
		}
		m_width = width;
		m_height = height;
		D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);

		//フィールド頂点バッファの初期化
		VERTEX_3D *pVtx;

		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
		for (int i = 0; i < m_BuildLoadMap->m_Wall002_num; i++, pVtx += 4)
		{
			pVtx[0].pos = D3DXVECTOR3(-m_width / 2, m_height, 0.0f);	// 頂点座標
			pVtx[1].pos = D3DXVECTOR3(m_width / 2, m_height, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, 0.0f);

			// 頂点色設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


			//UV設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);



			// 座標変換済み頂点設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		}
		/* 頂点情報 カギ締め */
		m_pVtxBuffer->Unlock();
		m_warp = 5;
	}
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CGameWall_002::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Wall002_num; i++)
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

				// ビューマトリックスを取得
				device->GetTransform(D3DTS_VIEW, &m_data[i].Matrix.View);

				// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
				device->SetRenderState(D3DRS_LIGHTING, FALSE);

				// レンダーステートの設定（zテスト）
				device->SetRenderState(D3DRS_ZENABLE, TRUE);
				device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新

				device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				// 頂点フォーマットの設定
				device->SetFVF(FVF_VERTEX_3D);


				// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
				device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																						// テクスチャの設定
				device->SetTexture(0, m_pTexture);

				// ポリゴンの描画
				device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
					(i * 4),								// 描画する最初の頂点
					2);										// 描画するプリミティブ数

				device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。

				device->SetRenderState(D3DRS_LIGHTING, TRUE);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}
		}
	}

	if (manager->m_Build == true)
	{
		for (int i = 0; i < m_BuildLoadMap->m_Wall002_num; i++)
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

				// ビューマトリックスを取得
				device->GetTransform(D3DTS_VIEW, &m_data[i].Matrix.View);

				// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
				device->SetRenderState(D3DRS_LIGHTING, FALSE);

				// レンダーステートの設定（zテスト）
				device->SetRenderState(D3DRS_ZENABLE, TRUE);
				device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新

				device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				// 頂点フォーマットの設定
				device->SetFVF(FVF_VERTEX_3D);


				// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
				device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																						// テクスチャの設定
				device->SetTexture(0, m_pTexture);

				// ポリゴンの描画
				device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
					(i * 4),								// 描画する最初の頂点
					2);										// 描画するプリミティブ数

				device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
				device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。

				device->SetRenderState(D3DRS_LIGHTING, TRUE);
				device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}
		}
	}
}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CGameWall_002::Update(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CPlayer *m_Player = game->GetPlayer();
	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Wall002_num; i++)
		{
			if (m_data[i].m_bUse == true && m_data[i].m_Position.y <100.0f)
			{
				if (m_Player->m_OldPos.x <= (m_data[i].m_Position.x + m_warp) &&
					m_Player->m_OldPos.x >= (m_data[i].m_Position.x - m_warp) &&
					(m_data[i].m_Position.z + 100.0f + m_warp) >= m_Player->m_OldPos.z &&
					m_Player->m_OldPos.z >= (m_data[i].m_Position.z - 100.0f - m_warp) &&
					(m_data[i].m_Rotation.y == -1.57f))
				{
					m_Player->m_OldPos.x = (m_data[i].m_Position.x + m_warp);
				}

				if (m_Player->m_OldPos.x >= (m_data[i].m_Position.x - m_warp) &&
					m_Player->m_OldPos.x <= (m_data[i].m_Position.x + m_warp) &&
					(m_data[i].m_Position.z + 100.0f + m_warp) >= m_Player->m_OldPos.z &&
					m_Player->m_OldPos.z >= (m_data[i].m_Position.z - 100.0f - m_warp) &&
					(m_data[i].m_Rotation.y == 1.57f))
				{
					m_Player->m_OldPos.x = (m_data[i].m_Position.x - m_warp);
				}

				if (m_Player->m_OldPos.z >= (m_data[i].m_Position.z - m_warp) &&
					m_Player->m_OldPos.z <= (m_data[i].m_Position.z + m_warp) &&
					(m_data[i].m_Position.x + 100.0f + m_warp) >= m_Player->m_OldPos.x &&
					m_Player->m_OldPos.x >= (m_data[i].m_Position.x - 100.0f - m_warp) &&
					(m_data[i].m_Rotation.y == 0.0f))
				{

					m_Player->m_OldPos.z = (m_data[i].m_Position.z - m_warp);
				}


				if (m_Player->m_OldPos.z <= (m_data[i].m_Position.z + m_warp) &&
					m_Player->m_OldPos.z >= (m_data[i].m_Position.z - m_warp) &&
					(m_data[i].m_Position.x + 100.0f + m_warp) >= m_Player->m_OldPos.x &&
					m_Player->m_OldPos.x >= (m_data[i].m_Position.x - 100.0f - m_warp) &&
					(m_data[i].m_Rotation.y == 3.14f))
				{
					m_Player->m_OldPos.z = (m_data[i].m_Position.z + m_warp);
				}

			}
		}
	}
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CGameWall_002の終了処理
//  戻り値　：
//=============================================================================
void CGameWall_002::Uninit(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CLoadMap *m_LoadMap = game->GetLoadMap();

			RELEASE(m_pTexture);
			RELEASE(m_pVtxBuffer);

}
void CGameWall_002::SetGameWall_002(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	if (manager->m_Build == false)
	{
		for (int i = 0; i < m_LoadMap->m_Wall002_num; i++)
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
		for (int i = 0; i < m_BuildLoadMap->m_Wall002_num; i++)
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