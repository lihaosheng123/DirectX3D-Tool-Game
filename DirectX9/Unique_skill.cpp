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
#include "Unique_skill.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CUnique_skill::CUnique_skill()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	for (int i = 0; i<UNIQUE_SKILL_MAX; i++)
	{
		m_Unique_skill[i].m_Buse = false;
	}
	m_bgUse = false;
	m_CheckUse = false;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CUnique_skill::~CUnique_skill()
{

}
CUnique_skill* CUnique_skill::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CUnique_skill *sceneUnique_skill;
	sceneUnique_skill = new CUnique_skill;

	sceneUnique_skill->Init(pos, rot, height, width, TEXTURE_FILE);

	return sceneUnique_skill;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CUnique_skill::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	if (FAILED(device->CreateVertexBuffer(
			sizeof(VERTEX_3D) * UNIQUE_SKILL_MAX * 4,
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
	for (int i = 0; i<UNIQUE_SKILL_MAX; i++)
	{

			m_Unique_skill[i].m_Position = pos;	// 頂点座標
			m_Unique_skill[i].m_Rotation = rot;	// 回転

			m_Unique_skill[i].m_height = height;
			m_Unique_skill[i].m_width = width;


			m_Unique_skill[i].m_scl.x = 1.0f;
			m_Unique_skill[i].m_scl.y = 1.0f;
			m_Unique_skill[i].m_scl.z = 1.0f;

			nCount = 0;			// カウンタ
			nPattern = 0;		// パターンNo.	
			m_frame = 0;
												
			m_Unique_skill[i].m_Buse = false;
	}
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i<UNIQUE_SKILL_MAX; i++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-m_Unique_skill[i].m_width / 2, m_Unique_skill[i].m_height, 0.0f);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_Unique_skill[i].m_width / 2, m_Unique_skill[i].m_height, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_Unique_skill[i].m_width / 2, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Unique_skill[i].m_width / 2, 0.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_UNIQUE_SKILL, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_UNIQUE_SKILL);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_UNIQUE_SKILL, TEXTURE_SIZE_Y_UNIQUE_SKILL);
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
void CUnique_skill::Draw(void)
{


	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	for (int i = 0; i<UNIQUE_SKILL_MAX; i++)
	{
		if (m_Unique_skill[i].m_Buse == true)
		{
			// ビューマトリックスを取得
			device->GetTransform(D3DTS_VIEW, &m_Unique_skill[i].mtxView);

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
			D3DXMatrixIdentity(&m_Unique_skill[i].m_mtxWorld);

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse(&m_Unique_skill[i].m_mtxWorld, NULL, &m_Unique_skill[i].mtxView);

			m_Unique_skill[i].m_mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			m_Unique_skill[i].m_mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			m_Unique_skill[i].m_mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア
															// スケールを反映
			D3DXMatrixScaling(&m_Unique_skill[i].mtxScl, m_Unique_skill[i].m_scl.x, m_Unique_skill[i].m_scl.y, m_Unique_skill[i].m_scl.z);
			D3DXMatrixMultiply(&m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_Unique_skill[i].mtxRot, m_Unique_skill[i].m_Rotation.y, m_Unique_skill[i].m_Rotation.x, m_Unique_skill[i].m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply(&m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&m_Unique_skill[i].mtxTrans, m_Unique_skill[i].m_Position.x, m_Unique_skill[i].m_Position.y, m_Unique_skill[i].m_Position.z);
			D3DXMatrixMultiply(&m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].m_mtxWorld, &m_Unique_skill[i].mtxTrans);

			// ワールドマトリックスを設定
			device->SetTransform(D3DTS_WORLD, &m_Unique_skill[i].m_mtxWorld);

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																					// テクスチャの設定
			device->SetTexture(0, m_pTexture);
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			// ブレンド加算処理

		//	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定


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
void CUnique_skill::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CBullet *m_Bullet = game->GetBullet();
	CScore *m_Score = game->GetScore();
	CSceneMouse *m_Mouse = manager->GetMouse();
	Cskillbg *m_skillbg = game->Getskillbg();
	CPlayer *m_Player = game->GetPlayer();
	if (m_bgUse == true)
	{
		m_skillbg = Cskillbg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, "NULL");
		m_bgUse = false;
	}
	//if (m_CheckUse != false)
	//{
	//	m_CheckUse = true;
	//}

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < UNIQUE_SKILL_MAX; i++)
	{
		if (m_frame == 0)
		{
			m_CheckUse = false;
		}
		if (m_frame >240)
		{
			m_Unique_skill[i].m_Buse = false;
			m_frame = 0;
		}
		else
		{
			m_frame++;
		}
	
		if (m_Unique_skill[i].m_Buse == true)
		{

			nCount++;
			{
			//	m_Score->AddScore(1);
			}
			if ((nCount % INTERVAL_PATTERN_UNIQUE_SKILL) == 0)
			{// アニメーション切り替え
				nPattern++;
				if (nPattern >= NUM_PATTERN_UNIQUE_SKILL)
				{// アニメーションパターンが終了
					nCount = 0;
					nPattern = NUM_PATTERN_UNIQUE_SKILL;
					//m_Unique_skill[i].m_Buse = false;
				}

			}
		}
	}

	for (int i = 0; i < UNIQUE_SKILL_MAX; i++, pVtx += 4)
	{
		if (m_Unique_skill[i].m_Buse == true)
		{
			
			pVtx[0].pos = D3DXVECTOR3(-m_Unique_skill[i].m_width / 2, m_Unique_skill[i].m_height, 0.0f);	// 頂点座標
			pVtx[1].pos = D3DXVECTOR3(m_Unique_skill[i].m_width / 2, m_Unique_skill[i].m_height, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_Unique_skill[i].m_width / 2, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Unique_skill[i].m_width / 2, 0.0f, 0.0f);

			pVtx[0].tex = D3DXVECTOR2(nPattern * TEXTURE_SIZE_X_UNIQUE_SKILL, nPattern * TEXTURE_SIZE_Y_UNIQUE_SKILL);
			pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * TEXTURE_SIZE_X_UNIQUE_SKILL, nPattern * TEXTURE_SIZE_Y_UNIQUE_SKILL);
			pVtx[2].tex = D3DXVECTOR2(nPattern * TEXTURE_SIZE_X_UNIQUE_SKILL, (nPattern + 1) * TEXTURE_SIZE_Y_UNIQUE_SKILL);
			pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * TEXTURE_SIZE_X_UNIQUE_SKILL, (nPattern + 1) * TEXTURE_SIZE_Y_UNIQUE_SKILL);
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
void CUnique_skill::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
void CUnique_skill::SetUnique_skill(D3DXVECTOR3 pos)
{

	for (int i = 0; i < UNIQUE_SKILL_MAX; i++)
	{
			m_Unique_skill[i].m_Position = pos;
			nCount = 0;
			nPattern = 0;
			m_frame = 0;
			m_CheckUse = true;
			m_Unique_skill[i].m_Buse = true;
			break;
	}
}