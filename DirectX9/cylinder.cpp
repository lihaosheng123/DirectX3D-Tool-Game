///********************************************************************************
//* タイトル　01
//* ファイル名　cylinder.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Fox描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "cylinder.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
cylinder::cylinder()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
cylinder::~cylinder()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT cylinder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	CEffect *m_Effect = game->GetEffect();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	////////////
	//3D
																			 // Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MODEL_CYLINDER_TEXTURE,
		D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
		device,
		NULL,
		&m_BuffMat,		// マテリアル情報
		NULL,
		&m_nNumMat,			// マテリアル数
		&m_Mesh)))		// メッシュ情報
	{
		return E_FAIL;
	}
	// モデルの初期設定
	m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// 頂点座標
	m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// 回転
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//2D
	//オブジェクトの頂点バッファを生成
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法
		FVF_VERTEX_2D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuffer,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void cylinder::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	関数名:	void cylinder::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void cylinder::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);	// y,x,z
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスを設定
	device->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 現在のマテリアル情報を取得する。
	device->GetMaterial(&matDef);

	device->SetTexture(0, NULL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//z値更新しない
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);	//ステンシルバッファへ書き込み宣言
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);

	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILREF, 1);		// ステンシル参照値

	//半透明用
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//円柱表を＋１で描画
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//円柱描画開始

	// キャスト変換
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		device->SetMaterial(&pMat[nCntMat].MatD3D);
		// メッシュの描画
		m_Mesh->DrawSubset(nCntMat);
	}


	//円柱描画終わり


	//円柱裏を-１で描画
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//円柱描画開始

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		device->SetMaterial(&pMat[nCntMat].MatD3D);
		// メッシュの描画
		m_Mesh->DrawSubset(nCntMat);
	}

	device->SetMaterial(&matDef);
	//円柱描画終わり

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	//全画面2Dポリゴン描画
	//頂点色フォーマット
	device->SetFVF(FVF_VERTEX_2D);

	// 頂点バッファをデータストリームにバインドする
	device->SetStreamSource(
		0,
		m_pVtxBuffer,
		0,
		sizeof(VERTEX_2D)
	);
	// フェードの描画設定内容
	device->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,		// 最初の頂点のインデックス
		2			// 描画するプリミティブ数
	);


	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	
}
//------------------------------------------------------------------------------
//	関数名:	void cylinder::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void cylinder::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();


}
cylinder* cylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	cylinder *Fox;
	Fox = new cylinder;
	Fox->Init(pos, rot, height, width, TEXTURE_FILE);
	return Fox;
}