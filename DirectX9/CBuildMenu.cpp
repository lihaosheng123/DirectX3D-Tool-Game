/********************************************************************************
* ファイル名　CBuildMenu.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/17
//*Build画面のmenu
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "CBuildMenu.h"

//グローバル変数

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CBuildMenu::CBuildMenu()
{
	for (int i = 0; i < MENU_NUM; i++)
	{
		m_pTexture_Build[i] = NULL;
		m_pVtxBuffer_Build[i] = NULL;	//頂点パッファへのポインタ
	}

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CBuildMenu::~CBuildMenu()
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CBuildMenu::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
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
		"data\\TEXTURE\\wall_Build.png",		// ファイルの名前
		&m_pTexture_Build[0]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\enemy_Build.png",		// ファイルの名前
		&m_pTexture_Build[1]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\light_Build.png",		// ファイルの名前
		&m_pTexture_Build[2]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\ceiling_Build.png",		// ファイルの名前
		&m_pTexture_Build[3]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\Prop_Build.png",		// ファイルの名前
		&m_pTexture_Build[4]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\another.png",		// ファイルの名前
		&m_pTexture_Build[5]);	// 読み込むメモリー

								// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\gamestart.png",		// ファイルの名前
		&m_pTexture_Build[6]);	// 読み込むメモリー

								// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
		"data\\TEXTURE\\backtitle.png",		// ファイルの名前
		&m_pTexture_Build[7]);	// 読み込むメモリー

	for (int i = 0; i < MENU_NUM; i++)
	{
		//オブジェクトの頂点バッファを生成
		if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法
			FVF_VERTEX_2D,							// 使用する頂点フォーマット
			D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
			&m_pVtxBuffer_Build[i],						// 頂点バッファインターフェースへのポインタ
			NULL)))									// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[i]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y - m_height / 2 + i*80.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y - m_height / 2 + i*80.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y + m_height / 2 + i*80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y + m_height / 2 + i*80.0f, 0.0f);

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
		m_pVtxBuffer_Build[i]->Unlock();
	}
	//状態の初期化
	m_type = BUILD_MENU_WALL;

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void CBuildMenu::Uninit(void)
{
	//削除
	for (int i = 0; i < MENU_NUM; i++)
	{
		RELEASE(m_pTexture_Build[i]);
		RELEASE(m_pVtxBuffer_Build[i]);
	}
}
//=============================================================================
//  関数名　：Draw
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void CBuildMenu::Draw(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	for (int i = 0; i < MENU_NUM; i++)
	{
		// 頂点色フォーマット
		device->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		device->SetTexture(0, m_pTexture_Build[i]);

		// 頂点バッファをデータストリームにバインドする
		device->SetStreamSource(
			0,
			m_pVtxBuffer_Build[i],
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
//=============================================================================
//  関数名　：Update
//  機能概要：プリゴンの更新処理	
//  戻り値　：
//=============================================================================
void CBuildMenu::Update(void)
{
	CManager *manager = GetManager();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CBuildMenu_Enemy *m_BuildMenu_Enemy = BuildManager->GetBuildMenu_Enemy();

	CEnemy_001 *m_Enemy_001 = BuildManager->GetEnemy_001(0);
	CRenderer *renderer = manager->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	CBuildMenu_Prop *m_BuildMenu_Prop = BuildManager->GetBuildMenu_Prop();
	CBuildMenu_Another *m_BuildMenu_Another = BuildManager->GetBuildMenu_Another();

	
	if (m_BuildMenu_Wall->m_bUse == false && m_BuildMenu_Enemy->m_bUse == false && m_BuildMenu_Prop->m_bUse == false && m_BuildMenu_Another->m_bUse == false)
	{
		switch (m_type)
		{
		case BUILD_MENU_WALL:
			//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			////////////////////////////////////////////////////////////////////////////////
					// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_ENEMY;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_BuildMenu_Wall->m_bUse = true;
			}
			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_BuildMenu_Wall->m_bUse = false;
			}
			m_BuildMenu_Enemy->m_bUse = false;
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;

		case BUILD_MENU_ENEMY:

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_WALL;
			}
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_LIGHT;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_BuildMenu_Enemy->m_bUse = true;
			}
			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_BuildMenu_Enemy->m_bUse = false;
			}
			m_BuildMenu_Wall->m_bUse = false;
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;
			//電球
		case BUILD_MENU_LIGHT:
			//ライトを有効する
			device->LightEnable(0, TRUE);
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_ENEMY;
			}

			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_CEILING;
			}
			//ライトオン
			device->LightEnable(0, TRUE);
			break;

			//天井板
		case BUILD_MENU_CEILING:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_LIGHT;
			}
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_PROP;
			}
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;

			//小道具
		case BUILD_MENU_PROP:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_CEILING;
			}
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_ANOTHER;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_BuildMenu_Prop->m_bUse = true;
			}
			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_BuildMenu_Prop->m_bUse = false;
			}
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;

			//他の設定
		case BUILD_MENU_ANOTHER:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();

			///////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_PROP;
			}
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_GAMESTART;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RIGHT))
			{
				m_BuildMenu_Another->m_bUse = true;
			}
			if (m_Input->GetKeyboardTrigger(DIK_LEFT))
			{
				m_BuildMenu_Another->m_bUse = false;
			}
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;

			//ゲーム開始
		case BUILD_MENU_GAMESTART:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			///////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_ANOTHER;
			}
			if (m_Input->GetKeyboardTrigger(DIK_DOWN))
			{
				m_type = BUILD_MENU_BACKTITLE;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RETURN))
			{
				CManager::SetMode(CManager::MODE_GAME);
			}
			//ライトオフ
			device->LightEnable(0, FALSE);
			break;

			//back to title
		case BUILD_MENU_BACKTITLE:
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[2]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[2]->Unlock();

			////////////////////////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[7]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[7]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[0]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[0]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[1]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[1]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[3]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[3]->Unlock();

			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[4]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[4]->Unlock();
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[5]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[5]->Unlock();

			///////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_pVtxBuffer_Build[6]->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// 頂点データをアンロックする
			m_pVtxBuffer_Build[6]->Unlock();

			///////////////////////////////////////////////////////////////
			//キーボード処理
			if (m_Input->GetKeyboardTrigger(DIK_UP))
			{
				m_type = BUILD_MENU_GAMESTART;
			}
			if (m_Input->GetKeyboardTrigger(DIK_RETURN))
			{
				CManager::SetMode(CManager::MODE_TITLE);
			}
			//ライトオン
			device->LightEnable(0, FALSE);
			break;
		default:
			break;
		}
	}

}

CBuildMenu* CBuildMenu::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CBuildMenu *m_BuildMenu;
	m_BuildMenu = new CBuildMenu;
	m_BuildMenu->Init(pos, rot, height, width, TEXTURE_FILE);
	return m_BuildMenu;
}
