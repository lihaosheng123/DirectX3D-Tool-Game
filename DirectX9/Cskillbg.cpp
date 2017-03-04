/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　scene2D.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/25
2Dポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "Cskillbg.h"

//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
Cskillbg::Cskillbg()
{
	m_pTexture = NULL;
	m_pVtxBuffer = NULL;	//頂点パッファへのポインタ
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
Cskillbg::~Cskillbg()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT Cskillbg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


		m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// 頂点座標
		m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// 回転

		m_height = height;
		m_width = width;


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
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y - m_height / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y - m_height / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y + m_height / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y + m_height / 2, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 50);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 50);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 50);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 30);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void Cskillbg::Uninit(void)
{

	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
	
}
//=============================================================================
//  関数名　：Draw
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void Cskillbg::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

		// 頂点色フォーマット
		device->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		device->SetTexture(0, NULL);
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

		// レンダーステートの設定をデフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
	
}
//=============================================================================
//  関数名　：Update
//  機能概要：プリゴンの更新処理	
//  戻り値　：
//=============================================================================
void Cskillbg::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CUnique_skill *m_Unique_skill = game->GetUnique_skill();
	if (m_Unique_skill->m_frame >240)
	{
		Uninit();
		Release();
	}

}

Cskillbg* Cskillbg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	Cskillbg *m_skillbg;
	m_skillbg = new Cskillbg;
	m_skillbg->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_skillbg;
}
