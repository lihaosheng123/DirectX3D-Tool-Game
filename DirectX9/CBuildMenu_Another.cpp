/********************************************************************************
* ファイル名　CBuildMenu_Another.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/17
2Dポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "CBuildMenu_Another.h"

//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CBuildMenu_Another::CBuildMenu_Another()
{
	for (int i = 0; i < MENU_ANOTHER_NUM; i++)
	{
		m_pTexture_Build_Another[i] = NULL;
		m_pVtxBuffer_Build_Another[i] = NULL;	//頂点パッファへのポインタ
	}
	m_bUse = false;

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CBuildMenu_Another::~CBuildMenu_Another()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CBuildMenu_Another::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


	m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// 頂点座標
	m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// 回転

	m_height = height;
	m_width = width;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\start.png",		// ファイルの名前
		&m_pTexture_Build_Another[0]);	// 読み込むメモリ

									// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\end.png",		// ファイルの名前
		&m_pTexture_Build_Another[1]);	// 読み込むメモリ

										// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\present.png",		// ファイルの名前
		&m_pTexture_Build_Another[2]);	// 読み込むメモリ


	for (int i = 0; i < MENU_ANOTHER_NUM; i++)
	{
		//オブジェクトの頂点バッファを生成
		if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法
			FVF_VERTEX_2D,							// 使用する頂点フォーマット
			D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
			&m_pVtxBuffer_Build_Another[i],						// 頂点バッファインターフェースへのポインタ
			NULL)))									// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[i]->Lock(0, 0, (void**)&pVtx, 0);


			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2 + i*120.0f, m_Position.y - m_height / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2 + i*120.0f, m_Position.y - m_height / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2 + i*120.0f, m_Position.y + m_height / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2 + i*120.0f, m_Position.y + m_height / 2, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		m_pVtxBuffer_Build_Another[i]->Unlock();
	}
	m_type = BUILD_MENU_ANOTHER_00;
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CBuildMenu_Another::Uninit(void)
{
	for (int i = 0; i < MENU_ANOTHER_NUM; i++)
	{
		RELEASE(m_pTexture_Build_Another[i]);
		RELEASE(m_pVtxBuffer_Build_Another[i]);
	}
}
//=============================================================================
//  関数名　：Draw
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void CBuildMenu_Another::Draw(void)
{
	if (m_bUse == true)
	{
		CManager *manager = GetManager();

		CRenderer *renderer = manager->GetRenderer();

		LPDIRECT3DDEVICE9 device = renderer->GetDevice();
		for (int i = 0; i < MENU_ANOTHER_NUM; i++)
		{
			// 頂点色フォーマット
			device->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			device->SetTexture(0, m_pTexture_Build_Another[i]);

			// 頂点バッファをデータストリームにバインドする
			device->SetStreamSource(
				0,
				m_pVtxBuffer_Build_Another[i],
				0,
				sizeof(VERTEX_2D)
			);
			// フェードの描画設定内容
			device->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,		// プリミティブの種類
				0,		// 最初の頂点のインデックス
				2			// 描画するプリミティブ数
			);
			// レンダーステートの設定をデフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
		}
	}
}
//=============================================================================
//  関数名　：Update
//  機能概要：プリゴンの更新処理	
//  戻り値　：
//=============================================================================
void CBuildMenu_Another::Update(void)
{
	CManager *manager = GetManager();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CBuildMenu *m_BuildMenu = BuildManager->GetBuildMenu();

	if (m_bUse == true)
	{
		switch (m_type)
		{
		case BUILD_MENU_ANOTHER_00:
			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_type = BUILD_MENU_ANOTHER_START;
			}
			break;
		case BUILD_MENU_ANOTHER_START:
			//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[0]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[1]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[2]->Unlock();

			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_bUse = false;
				m_type = BUILD_MENU_ANOTHER_00;
				m_BuildMenu->m_type = m_BuildMenu->BUILD_MENU_ANOTHER;
			}

			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_type = BUILD_MENU_ANOTHER_END;
			}

			break;

		case BUILD_MENU_ANOTHER_END:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[1]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[0]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[2]->Unlock();

			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_type = BUILD_MENU_ANOTHER_START;
			}

			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_type = BUILD_MENU_ANOTHER_PRESENT;
			}
			break;


		case BUILD_MENU_ANOTHER_PRESENT:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[2]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[0]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build_Another[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build_Another[1]->Unlock();

			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_type = BUILD_MENU_ANOTHER_END;
			}
			break;

		default:
			break;

		}
	}
}

CBuildMenu_Another* CBuildMenu_Another::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CBuildMenu_Another *m_BuildMenu_Another;
	m_BuildMenu_Another = new CBuildMenu_Another;
	m_BuildMenu_Another->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_BuildMenu_Another;
}
