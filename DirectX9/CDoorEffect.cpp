/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　m_Door_Effect.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
meshfieldの描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "bullet.h"
//=============================================================================
// クラスコンストラクタ
//=============================================================================
CDoor_Effect::CDoor_Effect()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	m_bUse = true;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CDoor_Effect::~CDoor_Effect()
{


}
CDoor_Effect* CDoor_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CDoor_Effect *m_Door_Effect;
	m_Door_Effect = new CDoor_Effect;
	m_Door_Effect->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_Door_Effect;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CDoor_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{

	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	//頂点バッファの生成
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL
	)))
	{
		return E_FAIL;
	}

		m_Position = pos;	// 頂点座標
		m_Rotation = rot;	// 回転
		m_height = height;
		m_width = width;


		m_scl.x = 1.0f;
		m_scl.y = 1.0f;
		m_scl.z = 1.0f;
		alpha = 100;

	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-m_width/2, m_height, 0.0f);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_width/2, m_height, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_width/2, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_width/2, 0.0f, 0.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, alpha);
		pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, alpha);
		pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, alpha);
		pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, alpha);


		// テクスチャ座標の設定
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
void CDoor_Effect::Draw(void)
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
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定
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
				2);										// 描画するプリミティブ数

														// レンダーステートの設定をデフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																			// 通常ブレンド
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
																			// ライト点灯
			device->SetRenderState(D3DRS_LIGHTING, TRUE);
		}

}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CDoor_Effect::Update(void)
{

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CScore *m_Score = game->GetScore();

	CCamera *m_Camera = game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CGameDoor *m_Door = game->GetGameDoor();
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CDoor_Effectの終了処理
//  戻り値　：
//=============================================================================
void CDoor_Effect::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
		
}