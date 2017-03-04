/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　CRevolverModel.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/08/23
りんごXポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "Camera.h"
#include "sceneX.h"
#include "manager.h"
#include "scene.h"
#include "CRevolverModel.h"
#include "sceneMouse.h"
#include "score.h"
//=============================================================================
// クラスコンストラクタ
//=============================	================================================
CRevolverModel::CRevolverModel()
{
	m_BuffMat = NULL;             // 頂点バッファへのポインタ
	m_Mesh = NULL;                  // メッシュの情報
	m_nNumMat = NULL;                     // マテリアル数x
	m_pTexture = NULL;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CRevolverModel::~CRevolverModel()
{

}

//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT CRevolverModel::Init(LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	D3DXCreateTextureFromFile(device, "data\\TEXTURE\\??.png", &m_pTexture);// テクスチャ読み込み
																					 // Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_FILE,
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
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	return S_OK;
}

//================================================================================================================================================================================================
// Uninit関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CRevolverModel::Uninit(void)
{
	//RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}

//================================================================================================================================================================================================
// Update関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CRevolverModel::Update(void)
{

}

//================================================================================
//================================================================================================================
// Draw関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CRevolverModel::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	if (m_Parent != NULL)
	{
		parentMatrix = m_Parent->GetWorldMatrix();

	}
	else
	{
		device->GetTransform(D3DTS_WORLD, &parentMatrix);
	}

	// 現在のマテリアル情報を取得する。
	device->GetMaterial(&matDef);

	//レンダーステートの設定（zテスト）
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新
															//レンダーステートの設定（アルファテスト）
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// アルファ値を判定して、該当のピクセルを描画するようにする。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 下の値よりアルファ値が大きければ描画する。
	device->SetRenderState(D3DRS_ALPHAREF, 200);						// アルファ値。0で透明な部分。


																		//モデルに明るになる
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);

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

	//モデル描画

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parentMatrix);
	// ワールドマトリックスを設定
	device->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// キャスト変換
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		device->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		device->SetTexture(0, m_pTexture);

		// メッシュの描画
		m_Mesh->DrawSubset(nCntMat);
	}
	// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																	// ライト点灯
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。
	device->SetMaterial(&matDef);

}

D3DXMATRIX CRevolverModel::GetWorldMatrix(void)
{
	return m_mtxWorld;
}
void CRevolverModel::SetParent(CRevolverModel *Parent)
{
	m_Parent = Parent;
}
void CRevolverModel::SetPosition(D3DXVECTOR3 Position)
{
	m_Position = Position;
}
void CRevolverModel::SetRotation(D3DXVECTOR3 Rotation)
{
	m_Rotation = Rotation;
}
CRevolverModel* CRevolverModel::Create(LPCSTR TEXTURE_FILE)
{
	CRevolverModel *sceneX;
	sceneX = new CRevolverModel;
	sceneX->Init(TEXTURE_FILE);
	return sceneX;
}
