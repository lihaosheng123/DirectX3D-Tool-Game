/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　sceneBillboard.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
meshfieldの描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneBillboard.h"


//=============================================================================
// クラスコンストラクタ
//=============================================================================
CSceneBillboard::CSceneBillboard()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CSceneBillboard::~CSceneBillboard()
{

}
CSceneBillboard* CSceneBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CSceneBillboard *sceneBillboard;
	sceneBillboard = new CSceneBillboard;
	sceneBillboard->Init(pos,rot,height ,width,TEXTURE_FILE);
	return sceneBillboard;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CSceneBillboard::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();


	m_Position = pos;	// 頂点座標
	m_Rotation = rot;	// 回転

	m_height = height;
	m_width = width;


	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;


	//頂点バッファの生成
	if( FAILED ( device -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * 1 * 4,
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
	D3DXCreateTextureFromFile( device, TEXTURE_FILE, &m_pTexture );

	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	m_pVtxBuffer -> Lock( 0, 0, ( void** ) &pVtx, 0 );



		pVtx[ 0 ].pos = D3DXVECTOR3(- m_width/2, m_height,0.0f);	// 頂点座標
		pVtx[ 1 ].pos = D3DXVECTOR3( m_width/2, m_height,0.0f);
		pVtx[ 2 ].pos = D3DXVECTOR3( - m_width/2,0.0f,0.0f);
		pVtx[ 3 ].pos = D3DXVECTOR3( m_width/2,0.0f,0.0f);

		// 頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//UV設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	

	// 座標変換済み頂点設定
	pVtx[0].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[1].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[2].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	pVtx[3].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	
	/* 頂点情報 カギ締め */
	m_pVtxBuffer -> Unlock();
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CSceneBillboard::Draw (void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	//CRenderer *m_Renderer =  GetRenderer();
	//LPDIRECT3DDEVICE9 device = m_Renderer->GetDevice();
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	// ビューマトリックスを取得
	device->GetTransform( D3DTS_VIEW, &mtxView );

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	device->SetRenderState( D3DRS_LIGHTING, FALSE );

	// レンダーステートの設定（zテスト）
	device->SetRenderState( D3DRS_ZENABLE, TRUE );
	device->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新
	// レンダーステートの設定（アルファテスト）
	device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	device->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。
	// 頂点フォーマットの設定
	device->SetFVF( FVF_VERTEX_3D );

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld );

	// ビューマトリックスの逆行列を求める。
	D3DXMatrixInverse( &m_mtxWorld, NULL, &mtxView );

	m_mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
	m_mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
	m_mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア

	// スケールを反映
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl );

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );

	// 位置を反映
	D3DXMatrixTranslation( &mtxTrans, m_Position.x, m_Position.y, m_Position.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans );

	// ワールドマトリックスを設定
	device->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
	device->SetStreamSource( 0, m_pVtxBuffer, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

	// テクスチャの設定
	device->SetTexture( 0,m_pTexture );

	// ポリゴンの描画
	device->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
							( 0 * 4 ),								// 描画する最初の頂点
							2 );										// 描画するプリミティブ数
		

	// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。

	// ライト点灯
	device->SetRenderState( D3DRS_LIGHTING, TRUE );

}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CSceneBillboard::Update(void)
{

}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CSceneBillboardの終了処理
//  戻り値　：
//=============================================================================
void CSceneBillboard::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
