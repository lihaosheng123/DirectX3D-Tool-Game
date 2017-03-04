/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　CPortal.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/08/23
りんごXポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "Camera.h"
#include "sceneX.h"
#include "manager.h"
#include "scene.h"
#include "portal.h"
#include "sceneMouse.h"
#include "score.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CPortal::CPortal()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	m_Buse = true;
	m_OneCheck = false;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CPortal::~CPortal()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CPortal::Init (D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ


	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CRenderer *renderer = manager -> GetRenderer();

	CEffect *m_Effect = game ->GetEffect();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
////////////

		D3DXCreateTextureFromFile(device,"data\\TEXTURE\\portal.png",&m_pTexture);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( TEXTURE_FILE,
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   device,
									   NULL,
									   &m_BuffMat,		// マテリアル情報
									   NULL,
									   &m_nNumMat,			// マテリアル数
									   &m_Mesh ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}
		// モデルの初期設定
		m_Position = D3DXVECTOR3(pos.x,pos.y,pos.z);	// 頂点座標
		m_Rotation = D3DXVECTOR3(rot.x,rot.y,rot.z);	// 回転
		m_scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		m_Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		m_Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = m_Mesh->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( m_Mesh->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		m_Mesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x <m_Min.x )		m_Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > m_Max.x )		m_Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < m_Min.y )		m_Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > m_Max.y )		m_Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < m_Min.z )		m_Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > m_Max.z )		m_Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		m_Mesh->UnlockVertexBuffer();



		// 衝突判定の長さの設定
		if( m_Size.x < m_Size.z )
		{
			m_Collisoin = m_Size.z;
		}
		else
		{
			m_Collisoin = m_Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CPortal:: Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	関数名:	void CPortal::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CPortal::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。
	if(m_Buse== true)
	{
	// 現在のマテリアル情報を取得する。
	device->GetMaterial( &matDef );
	// レンダーステートの設定（zテスト）
	device->SetRenderState( D3DRS_ZENABLE, TRUE );
	device->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新
	// レンダーステートの設定（アルファテスト）


	//モデルに明るになる
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &m_mtxWorld );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z );
		D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z );	// y,x,z
		D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );



		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, m_Position.x, m_Position.y, m_Position.z );
		D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTrans );



		// ワールドマトリックスを設定
		device->SetTransform( D3DTS_WORLD, &m_mtxWorld );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )m_BuffMat->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )m_nNumMat; nCntMat++ )
		{
			// マテリアルの設定
			device->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			device->SetTexture( 0, m_pTexture);		
			// メッシュの描画
			m_Mesh->DrawSubset( nCntMat );
		}
	// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。
	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	device->SetMaterial( &matDef );
	}
}
//------------------------------------------------------------------------------
//	関数名:	void CPortal::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CPortal::Update(void)
{
	//  デバイスのゲッター
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CCamera *m_Camera = game->GetCCamera();
	CSceneInput *m_Input = manager -> GetInput();
	CScore *m_Score = game ->GetScore();
	CTransferEffect *m_TransferEffect = game->GetTransferEffect();
	//for( int index = 0; index < MAX_BALL; index++ )
	//{
	//	CBall *m_Ball = game ->GetBall(index);
	//	D3DXVECTOR3 vpe_Portal = m_Ball->m_Position - m_Position;//始点から終点までのベクトル
	//	//ballとの当たり判定
	//	if( Length( &vpe_Portal ) < 120.0f )
	//		{
	//			if(m_Ball->m_state == BALL_COMMON)
	//			{
	//				m_Ball->m_DrawUse = false;
	//				//m_OneCheck = true;
	//				m_Ball->Release();
	//				m_Score->AddScore(1);
	//				return;
	//			}
	//		}
	//}
	//if(m_OneCheck == true)
	//{
	//	m_Score->AddScore(1);
	//	m_OneCheck = false;
	//}
}
CPortal* CPortal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{
	CPortal *Portal;
	Portal = new CPortal;
	Portal->Init(pos,rot,height ,width,TEXTURE_FILE);
	return Portal;
}
float  CPortal::Length( D3DXVECTOR3 *Vector )
{

	float len = sqrtf( Vector->x * Vector->x +
						Vector->y * Vector->y +
						Vector->z * Vector->z );

	return len;

}

void CPortal::Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 )
{

	*Vector = *Vector1 / Length( Vector1 );

}