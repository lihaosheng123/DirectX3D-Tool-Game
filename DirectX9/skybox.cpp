#include "main.h"
#include "manager.h"
#include "skybox.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CSkybox::CSkybox()
{
	for(int i = 0;i < 6 ; i ++ )
	{
	m_pTexture[i] = NULL;			// Direct3Dテクスチャのポインタ
	}
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ

	m_Position.x = 0.0f;		//地面のXの初期化
	m_Position.y = 0.0f;		//地面のYの初期化
	m_Position.z = 0.0f;		//地面のZの初期化

	m_Rotation.x = 0.0f;		//地面のXの回転初期化
	m_Rotation.y = 0.0f;		//地面のYの回転初期化
	m_Rotation.z = 0.0f;		//地面のZの回転初期化

	m_scl.x = 1.0f;		//地面のXのスケール初期化
	m_scl.y = 1.0f;		//地面のYのスケール初期化
	m_scl.z = 1.0f;		//地面のZのスケール初期化

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CSkybox::~CSkybox()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CSkybox::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	m_Position = D3DXVECTOR3(m_Position.x,m_Position.y,m_Position.z);	// 頂点座標
	//m_Rotation = rot;	// 回転
	//m_height = height;
	//m_width = width;
	//頂点バッファの生成
	if( FAILED ( device -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * 6 *4,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&m_pVtxBuffer,
												NULL
	) ) )
	{
		return E_FAIL;
	}
	//テクスチャの読み込み

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_lf.tga", &m_pTexture[0] );

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_bk.tga", &m_pTexture[1] );

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_rt.tga", &m_pTexture[2] );

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_ft.tga", &m_pTexture[3] );

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_up.tga", &m_pTexture[4] );

	D3DXCreateTextureFromFile( device, "data\\TEXTURE\\sandstorm_dn.tga", &m_pTexture[5] );




	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;
	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int i = 0; i < 6; i++ ,pVtx += 4 )
	{
		switch(i)
		{
			//左方向の面
		case 0:
		
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z +50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の前
		case 1:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y + 50000.0f,m_Position.z+50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の右
		case 2:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の後
		case 3:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

		//面の上
		case 4:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;
		

		//面の下
		case 5:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;
		}

	}
	/* 頂点情報 カギ締め */
	m_pVtxBuffer -> Unlock();

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CSkybox:: Uninit(void)
{
	for(int i = 0;i < 6 ; i ++ )
	{
	RELEASE(m_pTexture[i]);
	}
	RELEASE(m_pVtxBuffer);
}
//------------------------------------------------------------------------------
//	関数名:	void CSkybox::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CSkybox::Draw(void)
{

	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_Matrix.World);

	// スケールを反映
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &mtxScl );

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z );	// y,x,z
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &mtxRot );

	// 位置を反映
	D3DXMatrixTranslation( &mtxTrans, m_Position.x, m_Position.y, m_Position.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &mtxTrans );
		

	// ワールドマトリックスを設定
	device -> SetTransform( D3DTS_WORLD, &m_Matrix.World );

	device->SetRenderState( D3DRS_LIGHTING, FALSE );
	// 頂点色フォーマット
	device -> SetFVF ( FVF_VERTEX_3D );




	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//線だかあるの場合
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//device ->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_MODULATE );
	for(int i = 0;i < 6 ; i ++ )
	{
	// テクスチャの設定
	device -> SetTexture ( 0, m_pTexture[i] );


	// 頂点バッファをデータストリームにバインドする
	device -> SetStreamSource(
								0,
								m_pVtxBuffer,
								0,
								sizeof(VERTEX_3D)
								);
	

	device ->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	device ->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	// ポリゴンの描画
	device -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP, // プリミティブの種類
							  i * 4,                   // 最初の頂点のインデックス
							  2                     // 描画するプリミティブ数
							);

	}


	// レンダーステートの設定をデフォルトに戻す。
	device ->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device ->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。

	// ライト点灯
	device->SetRenderState( D3DRS_LIGHTING, TRUE );
}
//------------------------------------------------------------------------------
//	関数名:	void CSkybox::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CSkybox::Update(void)
{
	//  デバイスのゲッター

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CCamera *m_Camera =game->GetCCamera();
	CPlayer *m_Player = game->GetPlayer();
	m_Position.x = m_Player->m_Position.x;
	m_Position.y = m_Player->m_Position.y;
	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;
	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int i = 0; i < 6; i++ ,pVtx += 4 )
	{
		switch(i)
		{
			//左方向の面
		case 0:
		
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z +50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の前
		case 1:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y + 50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y + 50000.0f,m_Position.z+50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の右
		case 2:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

			//面の後
		case 3:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;

		//面の上
		case 4:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z-50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y+ 50000.0f,m_Position.z+50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;
		

		//面の下
		case 5:
			
		pVtx[ 0 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z+50000.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3(m_Position.x-50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3(m_Position.x+50000.0f,m_Position.y -50000.0f,m_Position.z-50000.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	

		// 座標変換済み頂点設定
		pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		break;
		}

	}
	/* 頂点情報 カギ締め */
	m_pVtxBuffer -> Unlock();


}
CSkybox* CSkybox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CSkybox *skybox;
	skybox = new CSkybox;
	skybox->Init(pos,rot,height ,width,TEXTURE_FILE);
	return skybox;
}