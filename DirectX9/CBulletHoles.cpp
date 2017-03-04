/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　m_BulletHoles.cpp
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
CBulletHoles::CBulletHoles()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	for(int i = 0;i<BULLETHOLES_MAX;i++)
	{
		m_BulletHoles[i].m_bUse = false;
	}

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CBulletHoles::~CBulletHoles()
{

}
CBulletHoles* CBulletHoles::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CBulletHoles *m_BulletHoles;
	m_BulletHoles = new CBulletHoles;
	m_BulletHoles->Init(pos,rot,height ,width,TEXTURE_FILE);
	return m_BulletHoles;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CBulletHoles::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	//頂点バッファの生成
	if( FAILED ( device -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * BULLETHOLES_MAX * 4,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&m_pVtxBuffer,
												NULL
	) ) )
	{
		return E_FAIL;
	}
	for(int i = 0;i<BULLETHOLES_MAX;i++)
	{

		m_BulletHoles[i].m_Position = pos;	// 頂点座標
		m_BulletHoles[i].m_Rotation = rot;	// 回転
		m_BulletHoles[i].m_height = height;
		m_BulletHoles[i].m_width = width;

		m_BulletHoles[i].m_Life = 200;

		m_BulletHoles[i].nCount = 0;			// カウンタ
		m_BulletHoles[i].nPattern = 0;		// パターンNo.	

		m_BulletHoles[i].m_scl.x = 1.0f;
		m_BulletHoles[i].m_scl.y = 1.0f;
		m_BulletHoles[i].m_scl.z = 1.0f;

	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile( device, TEXTURE_FILE, &m_pTexture );
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for(int i = 0;i<BULLETHOLES_MAX;i++, pVtx += 4 )
	{

		pVtx[ 0 ].pos = D3DXVECTOR3(m_BulletHoles[i].m_Position.x- m_BulletHoles[i].m_width/2,m_BulletHoles[i].m_Position.y+ m_BulletHoles[i].m_height/2,0.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_BulletHoles[i].m_Position.x+ m_BulletHoles[i].m_width/2,m_BulletHoles[i].m_Position.y+ m_BulletHoles[i].m_height/2,0.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_BulletHoles[i].m_Position.x- m_BulletHoles[i].m_width/2,m_BulletHoles[i].m_Position.y- m_BulletHoles[i].m_height/2,0.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_BulletHoles[i].m_Position.x+ m_BulletHoles[i].m_width/2,m_BulletHoles[i].m_Position.y- m_BulletHoles[i].m_height/2,0.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_BULLETHOLES, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_BULLETHOLES);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_BULLETHOLES, TEXTURE_SIZE_Y_BULLETHOLES);
	
	}
	/* 頂点情報 カギ締め */
	m_pVtxBuffer -> Unlock();
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CBulletHoles::Draw (void)
{

	CManager *manager = GetManager();
	CRenderer *renderer = manager->GetRenderer();
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *m_Camera =game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	for (int i = 0; i<BULLETHOLES_MAX; i++)
	{
		if (m_BulletHoles[i].m_bUse == true)
		{
			// ビューマトリックスを取得
			device->GetTransform(D3DTS_VIEW, &m_BulletHoles[i].mtxView);

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
			D3DXMatrixIdentity(&m_BulletHoles[i].m_mtxWorld);


			// スケールを反映
			D3DXMatrixScaling(&m_BulletHoles[i].mtxScl, m_BulletHoles[i].m_scl.x, m_BulletHoles[i].m_scl.y, m_BulletHoles[i].m_scl.z);
			D3DXMatrixMultiply(&m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_BulletHoles[i].mtxRot, m_BulletHoles[i].m_Rotation.y, m_BulletHoles[i].m_Rotation.x, m_BulletHoles[i].m_Rotation.z);	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply(&m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&m_BulletHoles[i].mtxTrans, m_BulletHoles[i].m_Position.x, m_BulletHoles[i].m_Position.y, m_BulletHoles[i].m_Position.z);
			D3DXMatrixMultiply(&m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].m_mtxWorld, &m_BulletHoles[i].mtxTrans);

			// ワールドマトリックスを設定
			device->SetTransform(D3DTS_WORLD, &m_BulletHoles[i].m_mtxWorld);

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
void CBulletHoles::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CSceneInput *m_Input = manager -> GetInput();

	CRenderer *renderer = manager -> GetRenderer();

	CScore *m_Score = game ->GetScore();

	CCamera *m_Camera = game->GetCCamera();
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	for (int i = 0; i < BULLETHOLES_MAX; i++)
	{
		if (m_BulletHoles[i].m_bUse == true)
		{
			m_BulletHoles[i].m_Life--;
			if (m_BulletHoles[i].m_Life <= 0)
			{
				m_BulletHoles[i].m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
				m_BulletHoles[i].m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
				m_BulletHoles[i].m_Life = 200;
				m_BulletHoles[i].m_bUse = false;
			}
		}
	}
	////頂点バッファの中身を埋める
	//VERTEX_3D *pVtx;
	//// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//for (int i = 0; i < BULLETHOLES_MAX; i++)
	//{
	//	if (m_BulletHoles[i].m_bUse == true)
	//	{
	//		m_BulletHoles[i].nCount++;
	//		if ((m_BulletHoles[i].nCount % INTERVAL_PATTERN_BULLETHOLES) == 0)
	//		{// アニメーション切り替え
	//			m_BulletHoles[i].nPattern++;
	//			if (m_BulletHoles[i].nPattern >= NUM_PATTERN_BULLETHOLES)
	//			{// アニメーションパターンが終了
	//				m_BulletHoles[i].m_bUse = false;
	//			}
	//		}

	//	}
	//}
		//for (int i = 0; i < BULLETHOLES_MAX; i++, pVtx += 4)
		//	{
		//		if (m_BulletHoles[i].m_bUse == true)
		//		{
		//			pVtx[0].tex = D3DXVECTOR2(m_BulletHoles[i].nPattern * TEXTURE_SIZE_X_BULLETHOLES, m_BulletHoles[i].nPattern * TEXTURE_SIZE_Y_BULLETHOLES);
		//			pVtx[1].tex = D3DXVECTOR2((m_BulletHoles[i].nPattern + 1) * TEXTURE_SIZE_X_BULLETHOLES, m_BulletHoles[i].nPattern * TEXTURE_SIZE_Y_BULLETHOLES);
		//			pVtx[2].tex = D3DXVECTOR2(m_BulletHoles[i].nPattern * TEXTURE_SIZE_X_BULLETHOLES, (m_BulletHoles[i].nPattern + 1) * TEXTURE_SIZE_Y_BULLETHOLES);
		//			pVtx[3].tex = D3DXVECTOR2((m_BulletHoles[i].nPattern + 1) * TEXTURE_SIZE_X_BULLETHOLES, (m_BulletHoles[i].nPattern + 1) * TEXTURE_SIZE_Y_BULLETHOLES);
		//			// 頂点データをアンロックする
		//			m_pVtxBuffer->Unlock();
		//		}
		//	}
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CBulletHolesの終了処理
//  戻り値　：
//=============================================================================
void CBulletHoles::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
float  CBulletHoles::Length( D3DXVECTOR3 *Vector )
{
	float len = sqrtf( Vector->x * Vector->x +
						Vector->y * Vector->y +
						Vector->z * Vector->z );

	return len;

}

void CBulletHoles::Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 )
{
	*Vector = *Vector1 / Length( Vector1 );
}
void CBulletHoles::SetBulletHoles( D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CSceneInput *m_Input = manager -> GetInput();

	CRenderer *renderer = manager -> GetRenderer();

	for( int nCnt = 0; nCnt < BULLETHOLES_MAX; nCnt++)
	{
		//弾が使っていないなら
		if(m_BulletHoles[nCnt].m_bUse == false )
		{
			m_BulletHoles[nCnt].m_Position = pos;
			m_BulletHoles[nCnt].m_Rotation = rot;
			m_BulletHoles[nCnt].nCount = 0;
			m_BulletHoles[nCnt].nPattern = 0;
			m_BulletHoles[nCnt].m_bUse	= true;		//弾が使用している
			break;
		}
	}
}
