/********************************************************************************
* タイトル　
* ファイル名　CEnd.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
天井板の描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "CEnd.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CEnd::CEnd()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CEnd::~CEnd()
{

}
CEnd* CEnd::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CEnd *m_BuildEnd;
	m_BuildEnd = new CEnd;
	m_BuildEnd->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_BuildEnd;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT0
//=============================================================================
HRESULT CEnd::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	CRenderer *renderer = manager->GetRenderer();


	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	m_Position = m_BuildLoadMap->m_Pos_End[0];
	m_Rotation = rot;	// 回転

	m_height = height;
	m_width = width;


	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;

	m_Changge = 50;
	//頂点バッファの生成	
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 1 * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL
	)))
	{
		return E_FAIL;
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);

	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_width / 2, 0.0f, m_height / 2);	// 頂点座標
	pVtx[1].pos = D3DXVECTOR3(m_width / 2, 0.0f, m_height / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, -m_height / 2);
	pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, -m_height / 2);

	// 頂点色設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 23, 140, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 23, 140, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 23, 140, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 23, 140, 255);


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


	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CEnd::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	// ビューマトリックスを取得
	device->GetTransform(D3DTS_VIEW, &mtxView);

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// レンダーステートの設定（zテスト）
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);



	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスを設定
	device->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
	device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																			// テクスチャの設定
	device->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
		(0 * 4),								// 描画する最初の頂点
		2);										// 描画するプリミティブ数

												// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																	// ライト点灯
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CEnd::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CEnd *m_End = BuildManager->GetEnd();
	m_NumCheck.x = (int)(m_BuildCamera->m_3DPos.x) - (int)(m_BuildCamera->m_3DPos.x) % 50;
	m_NumCheck.z = (int)(m_BuildCamera->m_3DPos.z) - (int)(m_BuildCamera->m_3DPos.z) % 50;
	m_NumCheck.y = 2.0f;
	if (m_NumCheck.y <= 0.0)
	{
		m_NumCheck.y = 2.0f;
	}
	switch (m_type)
	{
	case CEnd::END_NORMAL:
		break;
	case CEnd::END_BUILDING_TRUE:
		m_End->m_Position.x = (int)m_NumCheck.x;	// 頂点座標
		m_End->m_Position.z = (int)m_NumCheck.z;
		m_End->m_Position.y = (int)m_NumCheck.y;

		//フィールド頂点バッファの初期化
		VERTEX_3D *pVtx;

		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-m_width / 2, 0.0f, m_height / 2);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_width / 2, 0.0f, m_height / 2);
		pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, -m_height / 2);
		pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, -m_height / 2);


		/* 頂点情報 カギ締め */
		m_pVtxBuffer->Unlock();
		break;
	case CEnd::END_BUILDING_FALSE:
		m_End->m_Position.x = 5000.0f;	// 頂点座標
		m_End->m_Position.z = 5000.0f;
		m_End->m_Position.y = 5000.0f;

		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-m_width / 2, 0.0f, m_height / 2);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_width / 2, 0.0f, m_height / 2);
		pVtx[2].pos = D3DXVECTOR3(-m_width / 2, 0.0f, -m_height / 2);
		pVtx[3].pos = D3DXVECTOR3(m_width / 2, 0.0f, -m_height / 2);

		/* 頂点情報 カギ締め */
		m_pVtxBuffer->Unlock();
		break;
	case CEnd::END_MAX:
		break;
	default:
		break;
	}
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CEndの終了処理
//  戻り値　：
//=============================================================================
void CEnd::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}