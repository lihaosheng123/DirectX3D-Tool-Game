#include "main.h"
#include "manager.h"
#include "CColumnar.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CColumnar::CColumnar()
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	CLoadMap *m_LoadMap = game->GetLoadMap();
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ

	m_bUse = true;
	m_bMove = false;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CColumnar::~CColumnar()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CColumnar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
		m_Position = pos;	// 頂点座標
		m_Rotation = rot;	// 回転
		m_height = height;
		m_width = width;
		m_scl.x = 1.0f;		//地面のXのスケール初期化
		m_scl.y = 1.0f;		//地面のYのスケール初期化
		m_scl.z = 1.0f;		//地面のZのスケール初期化
		Point_num = m_LoadMap->m_Point_num;
	//頂点バッファの生成
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 66,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL
	)))
	{
		return E_FAIL;
	}

	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < 33; i++)
		{
			pVtx->pos.x = cosf(PI / 16.0f * i) * m_width;
			pVtx->pos.y = m_height;
			pVtx->pos.z = sinf(PI / 16.0f * i) * m_width;

			pVtx->tex = D3DXVECTOR2(i / 16.0f, 0.0f);

			pVtx->col = D3DCOLOR_RGBA(100, 255, 255, 255);

			pVtx++;


			pVtx->pos.x = cosf(PI / 16.0f * i) * m_width;
			pVtx->pos.y = -height;
			pVtx->pos.z = sinf(PI / 16.0f * i) * m_width;

			pVtx->tex = D3DXVECTOR2(i / 16.0f, 1.0f);

			pVtx->col = D3DCOLOR_RGBA(100, 255, 255, 255);

			pVtx++;

		}
	
	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();
	m_Life = 8;

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CColumnar::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
//------------------------------------------------------------------------------
//	関数名:	void CColumnar::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CColumnar::Draw(void)
{

	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *m_Camera = game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

		if (m_bUse == true)
		{
			// ビューマトリックスを取得
			device->GetTransform(D3DTS_VIEW, &m_Matrix.View);

			// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
			device->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ブレンド加算処理
		//	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		//	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定
			device->SetFVF(FVF_VERTEX_3D);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Matrix.World);


			// スケールを反映
			D3DXMatrixScaling(&m_Matrix.Scl, m_scl.x, m_scl.y, m_scl.z);
			D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_Matrix.Rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot);

			// 位置を反映
			D3DXMatrixTranslation(&m_Matrix.Trans, m_Position.x, m_Position.y, m_Position.z);
			D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans);

			// ワールドマトリックスを設定
			device->SetTransform(D3DTS_WORLD, &m_Matrix.World);

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																					// テクスチャの設定
			device->SetTexture(0, NULL);


			// ポリゴンの描画
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
				(0 * 4),								// 描画する最初の頂点
				64);										// 描画するプリミティブ数

															// レンダーステートの設定をデフォルトに戻す。
		//	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
		//	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。

																			// ライト点灯
			device->SetRenderState(D3DRS_LIGHTING, TRUE);
		}

}
//------------------------------------------------------------------------------
//	関数名:	void CColumnar::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CColumnar::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CScore *m_Score = game->GetScore();
	CHpScore *m_HpScore = game->GetHpScore();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CPlayer *m_Player = game->GetPlayer();
	CGlass *m_Glass = game->GetGlass();
		if (m_Life < 0)
		{
			m_Life = 0;
			m_bMove = true;
			
		}
		if (m_bMove == true)
		{
			m_Position.y -= 0.98f;
			m_Rotation.x -= 0.0125f;
		}
		if (m_Position.y < 20.0f && m_bUse == true)
		{
			m_Position.y = 20.0f;
			m_bUse = false;
			m_HpScore->AddScore(1);
			m_LoadMap->now_Point -=1;
			m_Player->m_Power += 25;
		}
		if (m_Rotation.x <= -1.57f)
		{
			m_Rotation.x = -1.57f;
		}
}
CColumnar* CColumnar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CColumnar *Columnar;
	Columnar = new CColumnar;
	Columnar->Init(pos, rot, height, width, TEXTURE_FILE);
	return Columnar;
}
