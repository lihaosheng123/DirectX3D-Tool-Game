/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　Unique_skill.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/08/23
りんごXポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "Camera.h"
#include "sceneX.h"
#include "manager.h"
#include "scene.h"
#include "sceneMouse.h"
#include "score.h"
#include "CSmoke.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CSmoke::CSmoke()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	for (int i = 0; i<SMOKE_MAX; i++)
	{
		m_Smoke[i].m_Buse = false;
	}
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CSmoke::~CSmoke()
{

}
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CSmoke *smoke;
	smoke = new CSmoke;

	smoke->Init(pos, rot, height, width, TEXTURE_FILE);

	return smoke;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CSmoke::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D) * SMOKE_MAX * 4,
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
	for (int i = 0; i<SMOKE_MAX; i++)
	{

		m_Smoke[i].m_Position = pos;	// 頂点座標
		m_Smoke[i].m_Rotation = rot;	// 回転

		m_Smoke[i].m_height = height;
		m_Smoke[i].m_width = width;


		m_Smoke[i].m_scl.x = 1.0f;
		m_Smoke[i].m_scl.y = 1.0f;
		m_Smoke[i].m_scl.z = 1.0f;

		m_Smoke[i].nCount = 0;			// カウンタ
		m_Smoke[i].nPattern = 0;		// パターンNo.	

		m_Smoke[i].m_Buse = false;
	}
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i<SMOKE_MAX; i++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-m_Smoke[i].m_width / 2, m_Smoke[i].m_height, 0.0f);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_Smoke[i].m_width / 2, m_Smoke[i].m_height, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_Smoke[i].m_width / 2, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Smoke[i].m_width / 2, 0.0f, 0.0f);

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



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SMOKE, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_SMOKE);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SMOKE, TEXTURE_SIZE_Y_SMOKE);
	}
	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CSmoke::Draw(void)
{


	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	for (int i = 0; i<SMOKE_MAX; i++)
	{
		if (m_Smoke[i].m_Buse == true)
		{
			// ビューマトリックスを取得
			device->GetTransform(D3DTS_VIEW, &m_Smoke[i].mtxView);

			// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
			device->SetRenderState(D3DRS_LIGHTING, FALSE);

			// レンダーステートの設定（zテスト）
			device->SetRenderState(D3DRS_ZENABLE, TRUE);
			device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新
						
																	// レンダーステートの設定（アルファテスト）
			device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// アルファ値を判定して、該当のピクセルを描画するようにする。
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 下の値よりアルファ値が大きければ描画する。
			device->SetRenderState(D3DRS_ALPHAREF, 200);						// アルファ値。0で透明な部分。
																				// 頂点フォーマットの設定
			device->SetFVF(FVF_VERTEX_3D);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Smoke[i].m_mtxWorld);

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse(&m_Smoke[i].m_mtxWorld, NULL, &m_Smoke[i].mtxView);

			m_Smoke[i].m_mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			m_Smoke[i].m_mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			m_Smoke[i].m_mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア
															// スケールを反映
			D3DXMatrixScaling(&m_Smoke[i].mtxScl, m_Smoke[i].m_scl.x, m_Smoke[i].m_scl.y, m_Smoke[i].m_scl.z);
			D3DXMatrixMultiply(&m_Smoke[i].m_mtxWorld, &m_Smoke[i].m_mtxWorld, &m_Smoke[i].mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_Smoke[i].mtxRot, m_Smoke[i].m_Rotation.y, m_Smoke[i].m_Rotation.x, m_Smoke[i].m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply(&m_Smoke[i].m_mtxWorld, &m_Smoke[i].m_mtxWorld, &m_Smoke[i].mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&m_Smoke[i].mtxTrans, m_Smoke[i].m_Position.x, m_Smoke[i].m_Position.y, m_Smoke[i].m_Position.z);
			D3DXMatrixMultiply(&m_Smoke[i].m_mtxWorld, &m_Smoke[i].m_mtxWorld, &m_Smoke[i].mtxTrans);

			// ワールドマトリックスを設定
			device->SetTransform(D3DTS_WORLD, &m_Smoke[i].m_mtxWorld);

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																					// テクスチャの設定
			device->SetTexture(0, m_pTexture);
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			// ブレンド加算処理

			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定


			// ポリゴンの描画
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
				(i * 4),								// 描画する最初の頂点
				2);										// 描画するプリミティブ数


			device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
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
}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CSmoke::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CBullet *m_Bullet = game->GetBullet();
	CScore *m_Score = game->GetScore();
	CSceneMouse *m_Mouse = manager->GetMouse();
	CPlayer *m_Player = game->GetPlayer();

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < SMOKE_MAX; i++)
	{
		if (m_Smoke[i].m_Buse == true)
		{
			m_Smoke[i].nCount++;
			if ((m_Smoke[i].nCount % INTERVAL_PATTERN_SMOKE) == 0)
			{// アニメーション切り替え
				m_Smoke[i].nPattern++;
				if (m_Smoke[i].nPattern >= NUM_PATTERN_SMOKE)
				{// アニメーションパターンが終了
					m_Smoke[i].nCount = 0;
					m_Smoke[i].nPattern = NUM_PATTERN_SMOKE;
					m_Smoke[i].m_Buse = false;
				}

			}
		}
	}

	for (int i = 0; i < SMOKE_MAX; i++, pVtx += 4)
	{
		if (m_Smoke[i].m_Buse == true)
		{
			pVtx[0].tex = D3DXVECTOR2(m_Smoke[i].nPattern * TEXTURE_SIZE_X_SMOKE, m_Smoke[i].nPattern * TEXTURE_SIZE_Y_SMOKE);
			pVtx[1].tex = D3DXVECTOR2((m_Smoke[i].nPattern + 1) * TEXTURE_SIZE_X_SMOKE, m_Smoke[i].nPattern * TEXTURE_SIZE_Y_SMOKE);
			pVtx[2].tex = D3DXVECTOR2(m_Smoke[i].nPattern * TEXTURE_SIZE_X_SMOKE, (m_Smoke[i].nPattern + 1) * TEXTURE_SIZE_Y_SMOKE);
			pVtx[3].tex = D3DXVECTOR2((m_Smoke[i].nPattern + 1) * TEXTURE_SIZE_X_SMOKE, (m_Smoke[i].nPattern + 1) * TEXTURE_SIZE_Y_SMOKE);
		}
	}
	// 頂点データをアンロックする
	m_pVtxBuffer->Unlock();
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：Unique_skillの終了処理
//  戻り値　：
//=============================================================================
void CSmoke::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
void CSmoke::SetSmoke(D3DXVECTOR3 pos)
{

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		m_Smoke[i].m_Position = pos;
		m_Smoke[i].nCount = 0;
		m_Smoke[i].nPattern = 0;
		m_Smoke[i].m_Buse = true;
		break;
	}
}