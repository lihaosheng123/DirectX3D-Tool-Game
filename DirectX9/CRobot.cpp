///********************************************************************************
//* タイトル　01
//* ファイル名　CRobot.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Robot描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CRobot.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CRobot::CRobot()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_Mesh = NULL;

	m_BuffMat = NULL;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CRobot::~CRobot()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CRobot::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildLoadMap *m_BuildLoadMap = BuildManager->GetBuildLoadMap();
	CRenderer *renderer = manager->GetRenderer();


	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	////////////
	D3DXCreateTextureFromFile(device, "data\\TEXTURE\\robot.png", &m_pTexture);// テクスチャ読み込み
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
	// モデルの初期設定
	m_Position = m_BuildLoadMap->m_Pos_Robot[0];	// 頂点座標
	m_Rotation = m_BuildLoadMap->m_Rot_Robot[0];	// 回転
	m_Changge = 0;
	m_scl = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CRobot::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	関数名:	void CRobot::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CRobot::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

							// 現在のマテリアル情報を取得する。
	device->GetMaterial(&matDef);
	// レンダーステートの設定（zテスト）
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新
															// レンダーステートの設定（アルファテスト）


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



	// ワールドマトリックスを設定
	device->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// キャスト変換
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		device->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		device->SetTexture(0, m_pTexture);
		// メッシュの描画
		m_Mesh->DrawSubset(nCntMat);
	}
	// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	device->SetMaterial(&matDef);


}
//------------------------------------------------------------------------------
//	関数名:	void CRobot::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CRobot::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CRobot *m_Robot = BuildManager->GetRobot();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	m_NumCheck.x = (int)(m_BuildCamera->m_3DPos.x) - (int)(m_BuildCamera->m_3DPos.x) % 50;
	m_NumCheck.z = (int)(m_BuildCamera->m_3DPos.z) - (int)(m_BuildCamera->m_3DPos.z) % 50;
	m_NumCheck.y = 0 ;
	switch (m_type)
	{
	case CRobot::ROBOT_BUILDING_FRONT:
		m_Robot->m_Position.x = (int)m_NumCheck.x;	// 頂点座標
		m_Robot->m_Position.z = (int)m_NumCheck.z;
		m_Robot->m_Position.y = (int)m_NumCheck.y;
		m_Robot->m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		break;
	case CRobot::ROBOT_BUILDING_BACK:
		m_Robot->m_Position.x = (int)m_NumCheck.x;	// 頂点座標
		m_Robot->m_Position.z = (int)m_NumCheck.z;
		m_Robot->m_Position.y = (int)m_NumCheck.y;
		m_Robot->m_Rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);

		break;
	case CRobot::ROBOT_BUILDING_LEFT:
		m_Robot->m_Position.x = (int)m_NumCheck.x;	// 頂点座標
		m_Robot->m_Position.z = (int)m_NumCheck.z;
		m_Robot->m_Position.y = (int)m_NumCheck.y;
		m_Robot->m_Rotation = D3DXVECTOR3(0.0f, -1.57f, 0.0f);

		break;
	case CRobot::ROBOT_BUILDING_RIGHT:
		m_Robot->m_Position.x = (int)m_NumCheck.x;	// 頂点座標
		m_Robot->m_Position.z = (int)m_NumCheck.z;
		m_Robot->m_Position.y = (int)m_NumCheck.y;
		m_Robot->m_Rotation = D3DXVECTOR3(0.0f, 1.57f, 0.0f);

		break;
	case CRobot::ROBOT_BUILDING_FALSE:
		m_Robot->m_Position.x = 5000.0f;
		m_Robot->m_Position.z = 5000.0f;
		m_Robot->m_Position.y = 5000.0f;

		break;
	case CRobot::ROBOT_MAX:
		break;
	default:
		break;
	}

}
CRobot* CRobot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CRobot *Robot;
	Robot = new CRobot;
	Robot->Init(pos, rot, height, width, TEXTURE_FILE);
	return Robot;
}