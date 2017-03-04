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
#include "score.h"
#include "number.h"
//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CHpScore::CHpScore()
{
	m_pTexture = NULL;
	m_pVtxBuffer = NULL;	//頂点パッファへのポインタ

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CHpScore::~CHpScore()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CHpScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	m_Position = D3DXVECTOR3(pos.x, pos.y, pos.z);	// 頂点座標
	m_Rotation = D3DXVECTOR3(rot.x, rot.y, rot.z);	// 回転

	m_height = height;
	m_width = width;
	m_nScore = 50;
	m_width_change = 10.0f;		//幅の間隔
								// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		TEXTURE_FILE,		// ファイルの名前
		&m_pTexture);	// 読み込むメモリー

						//オブジェクトの頂点バッファを生成
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HPSCORE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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

		for (int nCntScene = 0; nCntScene < MAX_HPSCORE; nCntScene++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2 + (nCntScene * (m_width + m_width_change)), m_Position.y - m_height / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2 + (nCntScene * (m_width + m_width_change)), m_Position.y - m_height / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2 + (nCntScene * (m_width + m_width_change)), m_Position.y + m_height / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2 + (nCntScene * (m_width + m_width_change)), m_Position.y + m_height / 2, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	}

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CHpScore::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
//=============================================================================
//  関数名　：Draw
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void CHpScore::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	// 頂点色フォーマット
	device->SetFVF(FVF_VERTEX_2D);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//テクスチャの設定
	device->SetTexture(0, m_pTexture);
		
	// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
	device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));			//sizeof( VERTEX_2D )はデータの間隔
																			// 頂点バッファをデータストリームにバインドする
	device->SetStreamSource(
		0,
		m_pVtxBuffer,
		0,
		sizeof(VERTEX_2D)
	);
	for (int i = 0; i < MAX_HPSCORE; i++)
	{
		// フェードの描画設定内容
		device->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			(0 + 4 * i),		// 最初の頂点のインデックス
			2			// 描画するプリミティブ数
		);
	}
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																	// 通常ブレンド
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
}
//=============================================================================
//  関数名　：Update
//  機能概要：プリゴンの更新処理	
//  戻り値　：
//=============================================================================
void CHpScore::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CNumber *m_Num = game->GetNum();
	CSceneInput *m_Input = manager->GetInput();

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScene = 0; nCntScene < MAX_HPSCORE; nCntScene++, pVtx += 4)
	{

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * m_Num->m_Number[nCntScene], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * m_Num->m_Number[nCntScene] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * m_Num->m_Number[nCntScene], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * m_Num->m_Number[nCntScene] + 0.1f, 1.0f);
	}

	// 頂点データをアンロックする
	m_pVtxBuffer->Unlock();
	//if(m_Input->GetKeyboardTrigger(DIK_F2))
	//{
	//	AddHpScore(1);
	//}

}

CHpScore* CHpScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CHpScore *score;
	score = new CHpScore;
	score->Init(pos, rot, height, width, TEXTURE_FILE);
	return score;
}
void CHpScore::AddScore(int value)
{
	m_nScore += value;
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}
	if (m_nScore >= 50)
	{
		m_nScore = 50;
	}
}