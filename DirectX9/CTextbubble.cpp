/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　m_BuildTextbubble.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
meshfieldの描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "CTextbubble.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CTextbubble::CTextbubble()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	m_use = true;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CTextbubble::~CTextbubble()
{

}
CTextbubble* CTextbubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CTextbubble *m_BuildTextbubble;
	m_BuildTextbubble = new CTextbubble;
	m_BuildTextbubble->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_BuildTextbubble;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT0
//=============================================================================
HRESULT CTextbubble::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();

	m_Position = pos;	// 頂点座標
	m_Rotation = rot;	// 回転

	m_height = height;
	m_width = width;


	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;

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


	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();

	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CTextbubble::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	if (m_use == true)
	{
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

}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CTextbubble::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CGameRobot *m_Robot = game->GetGameRobot();
	if (m_use == true)
	{
		m_Position.x = m_Robot->m_Position.x;
		m_Position.z = m_Robot->m_Position.z + 100.0f;
		m_Position.y = m_Robot->m_Position.y + 120.0f;
		m_Rotation.y = -m_Robot->m_Rotation.y;
	}

}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CTextbubbleの終了処理
//  戻り値　：
//=============================================================================
void CTextbubble::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}