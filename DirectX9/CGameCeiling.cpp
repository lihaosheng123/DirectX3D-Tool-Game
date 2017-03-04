/********************************************************************************
* タイトル　
* ファイル名　CGameCeiling.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/01/12

********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "CGameCeiling.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CGameCeiling::CGameCeiling()
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	//for (int i = 0; i < m_LoadMap->m_Ceiling_num; i++)
	//{
	//	m_data[i].m_bUse = false;
	//}
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CGameCeiling::~CGameCeiling()
{

}
CGameCeiling* CGameCeiling::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CGameCeiling *m_GameCeiling;
	m_GameCeiling = new CGameCeiling;
	m_GameCeiling->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_GameCeiling;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CGameCeiling::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
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
			sizeof(VERTEX_3D) * m_LoadMap->m_Ceiling_num * 4,
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
		for (int i = 0; i < m_LoadMap->m_Ceiling_num; i++, pVtx += 4)
		{
			pVtx[0].pos = D3DXVECTOR3(-m_width / 2, 0.0f, m_height / 2);	// 頂点座標
			pVtx[1].pos = D3DXVECTOR3(m_width / 2, 0.0f, m_height / 2);
			pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, -m_height / 2);
			pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, -m_height / 2);

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
		m_warp = 10;
	}
	if (manager->m_Build == true)
	{
		//頂点バッファの生成
		if (FAILED(device->CreateVertexBuffer(
			sizeof(VERTEX_3D) * m_BuildLoadMap->m_Ceiling_num * 4,
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
		for (int i = 0; i < m_BuildLoadMap->m_Ceiling_num; i++, pVtx += 4)
		{
			pVtx[0].pos = D3DXVECTOR3(-m_width / 2, 0.0f, m_height / 2);	// 頂点座標
			pVtx[1].pos = D3DXVECTOR3(m_width / 2, 0.0f, m_height / 2);
			pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, -m_height / 2);
			pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, -m_height / 2);

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
		m_warp = 10;
	}
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CGameCeiling::Draw(void)
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
		for (int i = 0; i < m_LoadMap->m_Ceiling_num; i++)
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
		for (int i = 0; i < m_BuildLoadMap->m_Ceiling_num; i++)
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
void CGameCeiling::Update(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	CSceneInput *m_Input = manager->GetInput();
	if (manager->m_Build == true)
	{
		for (int i = 0; i < m_BuildLoadMap->m_Ceiling_num; i++)
		{
			if (m_Input->GetKeyboardTrigger(DIK_Y))
			{
				m_data[i].m_bUse = false;
			}
			if (m_Input->GetKeyboardTrigger(DIK_H))
			{
				m_data[i].m_bUse = true;
			}
		}
	}
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CGameCeilingの終了処理
//  戻り値　：
//=============================================================================
void CGameCeiling::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
void CGameCeiling::SetGameCeiling(D3DXVECTOR3 pos)
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
		for (int i = 0; i < m_LoadMap->m_Ceiling_num; i++)
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
		for (int i = 0; i < m_BuildLoadMap->m_Ceiling_num; i++)
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