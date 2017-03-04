///********************************************************************************
//* タイトル　01
//* ファイル名　CGameRobot.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameRobot描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CGameRobot.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CGameRobot::CGameRobot()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_Mesh = NULL;

	m_BuffMat = NULL;

	m_bUse = true;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CGameRobot::~CGameRobot()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CGameRobot::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CLoadMap *m_LoadMap = game->GetLoadMap();
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
	m_Position = m_LoadMap->m_Pos_GameRobot[0];	// 頂点座標
	m_Rotation = m_LoadMap->m_Rot_GameRobot[0];	// 回転

	m_scl = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CGameRobot::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	関数名:	void CGameRobot::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGameRobot::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	if (m_bUse == true)
	{
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

}
//------------------------------------------------------------------------------
//	関数名:	void CGameRobot::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGameRobot::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CGameRobot *m_GameRobot = game->GetGameRobot();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CPlayer *m_Player = game->GetPlayer();
	CTalkRobotImage *m_TalkRobotImage = game->GetTalkRobotImage();
	if (m_bUse == true)
	{
		D3DXVECTOR3 vpe = m_Position - m_Player->m_Position;
		vpe.y = 0.0f;
		if (Length(&vpe) < 250.0f)
		{
			if (m_Input->GetKeyboardTrigger(DIK_T) && m_TalkRobotImage->m_bUse == false)
			{
				m_TalkRobotImage->m_bUse = true;
			}
		}
		else
		{
			m_TalkRobotImage->m_bUse = false;
		}
	}

}
CGameRobot* CGameRobot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CGameRobot *GameRobot;
	GameRobot = new CGameRobot;
	GameRobot->Init(pos, rot, height, width, TEXTURE_FILE);
	return GameRobot;
}
float  CGameRobot::Length(D3DXVECTOR3 *Vector)
{
	float len = sqrtf(Vector->x * Vector->x +
		Vector->y * Vector->y +
		Vector->z * Vector->z);

	return len;

}