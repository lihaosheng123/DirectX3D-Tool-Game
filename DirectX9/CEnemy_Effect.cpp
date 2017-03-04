/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　m_Enemy_Effect.cpp
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
CEnemy_Effect::CEnemy_Effect()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	for (int i = 0; i<ENEMY_EFFECT_MAX; i++)
	{
		m_Enemy_Effect[i].m_bUse = false;
	}
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CEnemy_Effect::~CEnemy_Effect()
{


}
CEnemy_Effect* CEnemy_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CEnemy_Effect *m_Enemy_Effect;
	m_Enemy_Effect = new CEnemy_Effect;
	m_Enemy_Effect->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_Enemy_Effect;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CEnemy_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{

	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	//頂点バッファの生成
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ENEMY_EFFECT_MAX * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL
	)))
	{
		return E_FAIL;
	}
	for (int i = 0; i < ENEMY_EFFECT_MAX; i++)
	{
		m_Enemy_Effect[i].m_Position = pos;	// 頂点座標
		m_Enemy_Effect[i].m_Rotation = rot;	// 回転
		m_Enemy_Effect[i].m_height = height;
		m_Enemy_Effect[i].m_width = width;


		m_Enemy_Effect[i].m_scl.x = 1.0f;
		m_Enemy_Effect[i].m_scl.y = 1.0f;
		m_Enemy_Effect[i].m_scl.z = 1.0f;

		m_Enemy_Effect[i].nCount = 0;			// カウンタ
		m_Enemy_Effect[i].nPattern = 0;		// パターンNo.	
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);
	}
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < ENEMY_EFFECT_MAX; i++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-m_Enemy_Effect[i].m_width , 0.0f, m_Enemy_Effect[i].m_height);	// 頂点座標
		pVtx[1].pos = D3DXVECTOR3(m_Enemy_Effect[i].m_width , 0.0f, m_Enemy_Effect[i].m_height);
		pVtx[2].pos = D3DXVECTOR3(-m_Enemy_Effect[i].m_width, 0.0f, -m_Enemy_Effect[i].m_height);
		pVtx[3].pos = D3DXVECTOR3(m_Enemy_Effect[i].m_width, 0.0f, -m_Enemy_Effect[i].m_height);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_EFFECT_ENEMY, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_EFFECT_ENEMY);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_EFFECT_ENEMY, TEXTURE_SIZE_Y_EFFECT_ENEMY);

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	}
	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();
	cnt = 0;
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CEnemy_Effect::Draw(void)
{

	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *m_Camera = game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	for (int i = 0; i < ENEMY_EFFECT_MAX; i++)
	{
		if (m_Enemy_Effect[i].m_bUse == true)
		{
			// ビューマトリックスを取得
			device->GetTransform(D3DTS_VIEW, &m_Enemy_Effect[i].m_Matrix.View);

			// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
			device->SetRenderState(D3DRS_LIGHTING, FALSE);

																				// ブレンド加算処理
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定
			device->SetFVF(FVF_VERTEX_3D);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Enemy_Effect[i].m_Matrix.World);


																// スケールを反映
			D3DXMatrixScaling(&m_Enemy_Effect[i].m_Matrix.Scl, m_Enemy_Effect[i].m_scl.x, m_Enemy_Effect[i].m_scl.y, m_Enemy_Effect[i].m_scl.z);
			D3DXMatrixMultiply(&m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.Scl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_Enemy_Effect[i].m_Matrix.Rot, m_Enemy_Effect[i].m_Rotation.y, m_Enemy_Effect[i].m_Rotation.x, m_Enemy_Effect[i].m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply(&m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.Rot);

			// 位置を反映
			D3DXMatrixTranslation(&m_Enemy_Effect[i].m_Matrix.Trans, m_Enemy_Effect[i].m_Position.x, m_Enemy_Effect[i].m_Position.y, m_Enemy_Effect[i].m_Position.z);
			D3DXMatrixMultiply(&m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.World, &m_Enemy_Effect[i].m_Matrix.Trans);

			// ワールドマトリックスを設定
			device->SetTransform(D3DTS_WORLD, &m_Enemy_Effect[i].m_Matrix.World);

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔

																					// テクスチャの設定
			device->SetTexture(0, m_pTexture);


			// ポリゴンの描画
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
				(i * 4),								// 描画する最初の頂点
				2);										// 描画するプリミティブ数

														// レンダーステートの設定をデフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。

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
void CEnemy_Effect::Update(void)
{

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CScore *m_Score = game->GetScore();

	CCamera *m_Camera = game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CEnemy *m_Enemy = game->GetEnemy();
	COrbit *m_Orbit = game->GetOrbit();
	CSmoke *m_Smoke = game->GetSmoke();
	CGameEnemy_001 *m_Enemy_001 = game->GetGameEnemy_001();
	CGameEnemy_001_data *m_Enemy_001_data = m_Enemy_001->Get(0);

	cnt = 0;
	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < ENEMY_EFFECT_MAX; i++, cnt++)
	{
		if (m_Enemy_Effect[i].m_Position.x >= 1000 || m_Enemy_Effect[i].m_Position.y >= 1000 || m_Enemy_Effect[i].m_Position.z >= 1000)
		{
			m_Enemy_Effect[i].m_bUse = false;
		}
		if (m_Enemy_Effect[i].m_bUse == true)
		{
			m_Enemy_Effect[i].nCount++;
			if ((m_Enemy_Effect[i].nCount % INTERVAL_PATTERN_EFFECT_ENEMY) == 0)
			{// アニメーション切り替え
				m_Enemy_Effect[i].nPattern++;
				if (m_Enemy_Effect[i].nPattern >= NUM_PATTERN_EFFECT_ENEMY)
				{// アニメーションパターンが終了
					m_Enemy_Effect[i].nCount = 0;
					m_Enemy_Effect[i].nPattern = 0;
				}
			}
			m_Enemy_Effect[i].m_Position = D3DXVECTOR3((m_Enemy_001_data+cnt)->m_Position.x, (m_Enemy_001_data + cnt)->m_Position.y+1.0f, (m_Enemy_001_data + cnt)->m_Position.z);
 
		}
	}
	for (int nCnt = 0;  nCnt < ENEMY_EFFECT_MAX;  nCnt++, pVtx += 4)
	{
		if (m_Enemy_Effect[nCnt].m_bUse == true)
		{
			pVtx[0].tex = D3DXVECTOR2(m_Enemy_Effect[nCnt].nPattern * TEXTURE_SIZE_X_EFFECT_ENEMY, m_Enemy_Effect[ nCnt].nPattern * TEXTURE_SIZE_Y_EFFECT_ENEMY);
			pVtx[1].tex = D3DXVECTOR2((m_Enemy_Effect[ nCnt].nPattern + 1) * TEXTURE_SIZE_X_EFFECT_ENEMY, m_Enemy_Effect[ nCnt].nPattern * TEXTURE_SIZE_Y_EFFECT_ENEMY);
			pVtx[2].tex = D3DXVECTOR2(m_Enemy_Effect[ nCnt].nPattern * TEXTURE_SIZE_X_EFFECT_ENEMY, (m_Enemy_Effect[ nCnt].nPattern + 1) * TEXTURE_SIZE_Y_EFFECT_ENEMY);
			pVtx[3].tex = D3DXVECTOR2((m_Enemy_Effect[ nCnt].nPattern + 1) * TEXTURE_SIZE_X_EFFECT_ENEMY, (m_Enemy_Effect[ nCnt].nPattern + 1) * TEXTURE_SIZE_Y_EFFECT_ENEMY);
		}
	}
	// 頂点データをアンロックする
	m_pVtxBuffer->Unlock();
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CEnemy_Effectの終了処理
//  戻り値　：
//=============================================================================
void CEnemy_Effect::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);

}
void CEnemy_Effect::SetEffect(D3DXVECTOR3 pos)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CCamera *m_Camera = game->GetCCamera();
	CPlayer *m_Player = game->GetPlayer();
	CGameEnemy_001 *m_Enemy_001 = game->GetGameEnemy_001();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	for (int nCnt = 0; nCnt < ENEMY_EFFECT_MAX; nCnt++)
	{
		//	使っていないなら
		if (m_Enemy_Effect[nCnt].m_bUse == false)
		{
			m_Enemy_Effect[nCnt].m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	//位置
			m_Enemy_Effect[nCnt].nCount = 0;
			m_Enemy_Effect[nCnt].nPattern = 0;
			m_Enemy_Effect[nCnt].m_bUse = true;		//弾が使用している
			break;
		}
	}

}
ENEMY_EFFECT* CEnemy_Effect::GetEnemy_Effect(void)
{
	return &m_Enemy_Effect[0];
}