///********************************************************************************
//* タイトル　01
//* ファイル名　CTitleRobot.cpp
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* TitleRobot描画
//********************************************************************************/
#include "main.h"
#include "manager.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "CTitleRobot.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CTitleRobot::CTitleRobot()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ

	m_Mesh = NULL;

	m_BuffMat = NULL;
	m_bMove = true;
	m_flag = true;
	m_rot = false;
	m_Backrot = false;
	m_newMove = false;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CTitleRobot::~CTitleRobot()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CTitleRobot::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CRenderer *renderer = manager->GetRenderer();

	CEffect *m_Effect = game->GetEffect();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

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
	m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// 頂点座標
	m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// 回転

	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_wait = 0;
	m_Time = 0;
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CTitleRobot::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_BuffMat);
	RELEASE(m_Mesh);
}
//------------------------------------------------------------------------------
//	関数名:	void CTitleRobot::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CTitleRobot::Draw(void)
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
//	関数名:	void CTitleRobot::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CTitleRobot::Update(void)
{
	CManager *manager = GetManager();
	CTitle *Title = (CTitle*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();
	CTitle_R_Model *m_Title_R_Model = Title->GetTitle_R_Model();
	if (m_flag == true)
	{
		if (m_Position.x >= 300.0f)
		{
			m_bMove = true;
		}
		else if (m_Position.x <= -300.0f)
		{
			m_bMove = false;
		}
		if (m_bMove == true)
		{
			m_Position.x -= 1.0f;
		}
		else if (m_bMove == false)
		{
			m_Position.x += 1.0f;
		}
	}
	if (m_Title_R_Model->m_Rotation.x == -1.57f &&m_Position.x == m_Title_R_Model->m_Position.x)
	{
		m_flag = false;
	}
	if (m_flag == false)
	{
		if (m_wait >= 60)
		{
			m_rot = true;
			m_wait = 0;
		}
		else
		{
			m_wait++;
		}
		if (m_rot == true)
		{
			m_Rotation.y -= 0.0125f;
			if (m_Rotation.y <= -3.14f)
			{
				m_Rotation.y = -3.14f;
				if (m_wait >= 60)
				{
					m_Backrot = true;
					m_Time = 0;
				}
				else
				{
					m_Time++;
				}
			}
		}
		if (m_Backrot == true)
			{
				m_rot = false;
				m_Rotation.y += 0.0125f;
				if (m_Rotation.y >= 0.0f)
				{
					m_Rotation.y = 0.0f;
					m_Position.z += 0.25f;
					m_Title_R_Model->m_Rotation.x += 0.0375f;
					if (m_Position.z >= 450.0f)
					{
						m_Position.z  = 450.0f;
						m_newMove = true;
					}

				}
				if (m_Title_R_Model->m_Rotation.x >= 1.57f)
					{
						m_Title_R_Model->m_Rotation.x = 1.57f;
					
					}

			}
		if (m_newMove == true)
		{
			if (m_Position.x >= 300.0f)
			{
				m_bMove = true;
			}
			else if (m_Position.x <= -300.0f)
			{
				m_bMove = false;
			}
			if (m_bMove == true)
			{
				m_Position.x -= 1.0f;
			}
			else if (m_bMove == false)
			{
				m_Position.x += 1.0f;
			}
		}
	}

}
CTitleRobot* CTitleRobot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CTitleRobot *TitleRobot;
	TitleRobot = new CTitleRobot;
	TitleRobot->Init(pos, rot, height, width, TEXTURE_FILE);
	return TitleRobot;
}