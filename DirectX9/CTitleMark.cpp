/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　CTitleMark.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/08/23
りんごXポリゴンの描画用
********************************************************************************/
#include "main.h"
#include "Camera.h"
#include "sceneX.h"
#include "manager.h"
#include "scene.h"
#include "CTitleMark.h"
#include "sceneMouse.h"
#include "score.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CTitleMark::CTitleMark()
{
	m_pTexture = NULL;			// Direct3Dテクスチャのポインタ
	m_pVtxBuffer = NULL;		// Direct3Dバッファへのポインタ
	m_bUse = true;
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CTitleMark::~CTitleMark()
{

}
CTitleMark* CTitleMark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CTitleMark *sceneTitleMark;
	sceneTitleMark = new CTitleMark;

	sceneTitleMark->Init(pos, rot, height, width, TEXTURE_FILE);

	return sceneTitleMark;
}
//=============================================================================
//  関数名　：Init
//  機能概要：3Dの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CTitleMark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


	m_Position = pos;	// 頂点座標
	m_Rotation = rot;	// 回転

	m_height = height;
	m_width = width;


	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;

						//頂点バッファの生成
	m_type = TITLE_MENU_START;
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 1 * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL
	)))
	{
		return E_FAIL;
	}
	col.r = 1.0f;
	col.g = 1.0f;
	col.b = 1.0f;
	col.a = 1.0f;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(device, TEXTURE_FILE, &m_pTexture);

	//フィールド頂点バッファの初期化
	VERTEX_2D *pVtx;

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
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);


	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	/* 頂点情報 カギ締め */
	m_pVtxBuffer->Unlock();
	num = 1.0f;
	m_colMove = false;
	return S_OK;
}
//=============================================================================
//  関数名　：Draw
//  機能概要：3Dの描画処理
//  戻り値　：
//=============================================================================
void CTitleMark::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	if (m_bUse == true)
	{
		// 頂点バッファをデータストリームにバインド
		device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		device->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		device->SetTexture(0, m_pTexture);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		// ブレンド加算処理
		//device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		//device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定
		// ポリゴンの描画
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
			0,								// 描画する最初の頂点
			2);										// 描画するプリミティブ数
		//device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		// レンダーステートの設定をデフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。

																		// 通常ブレンド
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
	}
}
//=============================================================================
//  関数名　：Update
//  機能概要：3Dの更新処理
//  戻り値　：
//=============================================================================
void CTitleMark::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();
	CTitle *Title = (CTitle*)CManager::GetMode();
	CTitleMenu *m_TitleMenu = Title->GetTitleMenu();
	if (m_bUse == true)
	{
		switch (m_type)
		{
		case TITLE_MENU_START:
			if (m_Input->GetKeyboardTrigger(DIK_S))
			{
				m_type = TITLE_MENU_BUILD;
			}
			break;


		case TITLE_MENU_BUILD:
			if (m_Input->GetKeyboardTrigger(DIK_W))
			{
				m_type = TITLE_MENU_START;
			}

			if (m_Input->GetKeyboardTrigger(DIK_S))
			{
				m_type = TITLE_MENU_END;
			}
			break;

		case TITLE_MENU_END:
			if (m_Input->GetKeyboardTrigger(DIK_W))
			{
				m_type = TITLE_MENU_BUILD;
			}
			break;

		default:
			break;

		}
		//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		switch (m_type)
		{
		case TITLE_MENU_START:
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y - m_height / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y - m_height / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y + m_height / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y + m_height / 2, 0.0f);
			break;

		case TITLE_MENU_BUILD:
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y - m_height / 2 + 80.0f , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y - m_height / 2 + 80.0f , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y + m_height / 2 + 80.0f , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y + m_height / 2 + 80.0f , 0.0f);
			break;

		case TITLE_MENU_END:
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y - m_height / 2 + 80.0f * 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y - m_height / 2 + 80.0f * 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_Position.x - m_width / 2, m_Position.y + m_height / 2 + 80.0f * 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_width / 2, m_Position.y + m_height / 2 + 80.0f * 2, 0.0f);
			break;

		default:
			break;
		}
		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
		}
		if (col.r <= 0.0f)
		{
			col.r = 0.0f;
		}
		if (col.g <= 0.0f)
		{
			col.g = 0.0f;
		}
		if (col.b <= 0.0f)
		{
			col.b = 0.0f;
		}
		//
		if (num <= 0.0f)
		{
			m_colMove = false;
		}
		else if (num >= 255.0f)
		{
			m_colMove = true;
		}

		if (m_colMove == false)
		{
			num +=1.0f;
		}
		else if (m_colMove == true)
		{
			num -=1.0f;
		}
		col.r = float(num / 255.0f);
		col.g = float(num / 255.0f);
		col.b = float(num / 255.0f);
		col.a = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
		pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
		pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
		pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	}

}
//=============================================================================
//  関数名　：Uninit
//  機能概要：CTitleMarkの終了処理
//  戻り値　：
//=============================================================================
void CTitleMark::Uninit(void)
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
}
