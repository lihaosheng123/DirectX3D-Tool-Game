/********************************************************************************
* タイトル　01
* ファイル名　renderer.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#include "renderer.h"

CRenderer *renderer;
//グローバル変数
//=============================================================================
// D3D生成
//=============================================================================
CRenderer::CRenderer(void)
{
	m_pD3D = NULL;		//Direct3Dオブジェクトへのポインタ
	m_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
	m_pFont = NULL;		//フォントへのポインタ
}

//=============================================================================
// D3D破棄
//=============================================================================
CRenderer::~CRenderer(void)
{

}
//=============================================================================
//  関数名　：Init
//  機能概要：D3Dの必要コード
//  戻り値　：HRESULT
//=============================================================================
HRESULT CRenderer:: Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3Dオブジェクトの完成
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))	//ディスプレイモード（画面解像度）
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//size
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//size
	d3dpp.BackBufferFormat = d3ddm.Format;	//バークバッファ形式
	d3dpp.BackBufferCount = 1;	//バークバッファ数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;	//テッグスバッファとステンシルバファの生成
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	16ビットで使用(ステンシルバッファ使用しない)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //ステンシルバッファ使用 // 24ビットZバッファ8ビットステンシルバッファ作成
	d3dpp.Windowed = bWindow;
//	d3dpp.Windowed = false;		//全画面
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

  //  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  ////d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  //  d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	if(FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,	//描画
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	//頂点処理
		&d3dpp,
		&m_pD3DDevice)))	//Direce 3Dデバイスの生成	

	{
		if(FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))	//Direce 3Dデバイスの生成
		{
			if(FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))	//Direce 3Dデバイスの生成
			{
				return E_FAIL;
			}
		}
	}

	/* レンダーステート 設定 */
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用

	m_pD3DDevice -> SetRenderState( D3DRS_BLENDOP, D3DBLEND_ZERO );          // カリング設定
	m_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );          // アルファ設定
	m_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );     // ソースブレンド設定
	m_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ); // ディストブレンド設定

	/* サンプラーステート 設定 */
	m_pD3DDevice -> SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	m_pD3DDevice -> SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	m_pD3DDevice -> SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice -> SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// テクスチャーステージパラメータのの設定
	m_pD3DDevice ->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice ->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice ->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	//デバッグ情報表示用フォントを設定
#ifdef _DEBUG

	//初期化処理
	D3DXCreateFont(m_pD3DDevice,18,0,0,0,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Terminal",
			&m_pFont);

#endif


	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：D3D終了処理
//  戻り値　：void
//=============================================================================
void CRenderer:: Uninit (void)
{
	RELEASE(m_pD3D);
	RELEASE(m_pD3DDevice);
	//デバッグ情報表示用フォントを設定
#ifdef _DEBUG
	RELEASE(m_pFont);
#endif

}
//=============================================================================
//  関数名　：Begin
//  機能概要：D3D画面描画用
//  戻り値　：void
//=============================================================================
void CRenderer:: Begin (void)
{
	/*ステンシルバッファ使用しないの場合*/
	//m_pD3DDevice->Clear(0,NULL,
	//(D3DCLEAR_TARGET|
	//D3DCLEAR_ZBUFFER),
	//D3DCOLOR_RGBA(135, 206, 235,255),	//R,G,B,透明度
	//1.0f,0);	//画面のクリア


	/*ステンシルバッファ使用するの場合*/
	m_pD3DDevice->Clear(0,NULL,
	(D3DCLEAR_TARGET|		//バックバッファ
	D3DCLEAR_ZBUFFER|		//zバッファ
	D3DCLEAR_STENCIL),//ステンシルバッファ
	D3DCOLOR_RGBA(255, 255, 255, 255),	//R,G,B,透明度
	1.0f,0);	//画面のクリア

	m_pD3DDevice->BeginScene();	//描画開始

}
//=============================================================================
//  関数名　：End
//  機能概要：D3D画面描画用
//  戻り値　：void
//=============================================================================
void CRenderer:: End (void)
{
	m_pD3DDevice->EndScene();	//描画終了
	m_pD3DDevice->Present(NULL,NULL,NULL,NULL);	//バックバッファをディスプレイに表示
}

//=============================================================================
//  関数名　：Update
//  機能概要：D3D更新処理
//  戻り値　：void
//=============================================================================
void CRenderer:: Update(void)
{

}
//=============================================================================
//  関数名　：LPDIRECT3DDEVICE9 GetDevice(void)
//  機能概要：他のcpp使うためにの戻り値
//  戻り値　：LPDIRECT3DDEVICE9
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
/*******************************************************************************
* 関数名: DrawFPS
*******************************************************************************/
void CRenderer::DrawFPS( void )
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[ 256 ];

	wsprintf( &aStr[ 0 ], "FPS:%d\n", g_nCountFPS );

	//テキスト描画
	m_pFont -> DrawText( NULL, &aStr[ 0 ], -1, &rect, DT_RIGHT,  D3DCOLOR_RGBA( 255, 255, 255, 255 ) );
}