/********************************************************************************
* タイトル　GM 01
* ファイル名　sceneMouse.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/23
* マウス入力全処理
********************************************************************************/
/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "dinput.h"
#include "sceneInput.h"
#include "sceneMouse.h"
#include "scene2D.h"

#define	TEXTURE_MOUSE_FILE		"data\\TEXTURE\\mouse.png"	// 読み込むテクスチャファイル名

#define	NUM_PATTERN			(32)						// アニメーションのパターン数

#define	TEXTURE_PATTERN_X		(8.0f)	// テクスチャ内の１パターンのx
#define	TEXTURE_PATTERN_Y		(4.0f)					// テクスチャ内の１パターンのy

#define	TEXTURE_SIZE_X		(1.0f / TEXTURE_PATTERN_X)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y		(1.0f / TEXTURE_PATTERN_Y)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN	(3)						// アニメーションの切り替え間隔
//=============================================================================
// クラスコンストラクタ
//=============================================================================
CSceneMouse::CSceneMouse()
{
	m_pTexture = NULL;
	m_pVtxBuffer  = NULL;	//頂点パッファへのポインタ
	m_MouseInput = NULL;					//IDirectInput8インターフェースへのポインタ
	g_pDevMouse = NULL;					//IDirectInputDevice8インターフェースへのポインタ(マウス)
	for(int cntMouse = 0;cntMouse < NUM_KEY_MAX ;cntMouse++)
	{
		g_MouseStateTrigger[ cntMouse ] = 0 ;		//マウスの状態を受け取るワーク
		g_MouseStateRelease[ cntMouse ] = 0 ;		//マウスの状態を受け取るワーク
		g_MouseStateRepeat[ cntMouse ] = 0 ;		//マウスの状態を受け取るワーク
		g_MouseStateRepeatCnt[ cntMouse ] = 0 ;	//マウスのリピートカウンタ
	}
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CSceneMouse::~CSceneMouse()
{

}

/*------------------------------------------------------------------------------
|	マウスの初期化処理
------------------------------------------------------------------------------*/
HRESULT CSceneMouse::Init( HINSTANCE hInstance, HWND hWnd )
{
	if( m_MouseInput == NULL )
	{
		//DirectInputオブジェクトの作成
		if( FAILED(
			DirectInput8Create
			(
				hInstance,
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				( void** )&m_MouseInput,
				NULL
			) ) )
		{
			MessageBox( hWnd, "DirectInput8オブジェクトの作成(マウス用)できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}
	}


	if( FAILED( m_MouseInput -> CreateDevice( GUID_SysMouse, &g_pDevMouse, NULL ) ) )
	{//デバイスオブジェクトを作成
		MessageBox( hWnd, "マウスがありません！", "警告！", MB_ICONWARNING );
		return E_FAIL;	
	}

	if( g_pDevMouse != NULL )
	{
		if( FAILED( g_pDevMouse -> SetDataFormat( &c_dfDIMouse ) ) )												//データフォーマットの設定
		{//データフォーマットを設定
			MessageBox( hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//協調モードを設定（フォアグラウンド＆非排他モード）
		if( FAILED( g_pDevMouse -> SetCooperativeLevel( hWnd, ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) ) )		//協調モードの設定
		{
			MessageBox( hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//軸モードを設定（相対値モードに設定）
		DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof( diprop );
		diprop.diph.dwHeaderSize	= sizeof( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_REL;	//相対値モードで設定（絶対モードはDIPROPAXISMODE_ABS）

		if( FAILED( g_pDevMouse -> SetProperty( DIPROP_AXISMODE, &diprop.diph ) ) )
		{
			MessageBox( hWnd, "軸モードの設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}
		
		//マウス構造体の初期化
		SetRect( &g_Mouse.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );		//マウスカーソルの動く範囲
		g_Mouse.x = SCREEN_CENTER_X;											//マウスカーソルのＸ座標を初期化
		g_Mouse.y = SCREEN_CENTER_Y;											//マウスカーソルのＹ座標を初期化
		g_Mouse	.moveAdd = 3;													//マウスカーソルの移動量を設定
		g_MouseState.lX = 0;
		g_MouseState.lY = 0;
		g_MouseState.lZ = 0;
		nCount = 0;			// カウンタ
		nPattern = 0;		// パターンNo.	
		//入力制御開始	
		g_pDevMouse -> Acquire();

	}
	/*マウスの描画開始*/

	m_Position =  D3DXVECTOR3(0.0f,0.0f,0.0f);	// 頂点座標
	m_Rotation=  D3DXVECTOR3(0.0f,0.0f,0.0f);	// 回転
	m_height = 40.0f;		//高さ
	m_width = 40.0f;		//幅さ
	nCount = 0;			// カウンタ
	nPattern = 0;		// パターンNo.
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
								TEXTURE_MOUSE_FILE,		// ファイルの名前
								&m_pTexture);	// 読み込むメモリー

	 //オブジェクトの頂点バッファを生成
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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

		for(int nCntScene = 0; nCntScene < 1; nCntScene++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3( m_Position.x - m_width/2, m_Position.y - m_height/2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( m_Position.x + m_width/2, m_Position.y - m_height/2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3( m_Position.x - m_width/2, m_Position.y + m_height/2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( m_Position.x + m_width/2, m_Position.y + m_height/2, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X, TEXTURE_SIZE_Y);
		}

		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	}
	return S_OK;
}

/*------------------------------------------------------------------------------
|	マウスの終了処理
------------------------------------------------------------------------------*/
void CSceneMouse::Uninit( void )
{
	RELEASE(m_pTexture);
	RELEASE(m_pVtxBuffer);
	RELEASE(g_pDevMouse);
}
/*------------------------------------------------------------------------------
|	マウスの描画処理
------------------------------------------------------------------------------*/
void CSceneMouse::Draw( void )
{

	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();


	// 頂点バッファをデータストリームにバインド
	device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	device->SetTexture(0, m_pTexture);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	// ブレンド加算処理
	device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定

	// ポリゴンの描画
	device->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
							 0 ,								// 描画する最初の頂点
							2 );										// 描画するプリミティブ数
	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	// レンダーステートの設定をデフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。

	// 通常ブレンド
	device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

}
/*------------------------------------------------------------------------------
|	マウスの更新処理
------------------------------------------------------------------------------*/
void CSceneMouse::Update( void )
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CField *meshField = game -> GetField();
	CCamera *m_Camera = game->GetCCamera();
	CSceneInput *m_Input = manager->GetInput();

	if (g_pDevMouse != NULL)
	{
		BYTE MouseStateOld[NUM_KEY_MAX];

		//前回のデータを保存
		memcpy(MouseStateOld, g_MouseState.rgbButtons, NUM_KEY_MAX);

		if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_MouseState)))
		{//デバイスからデータを取得
				//マウスの移動を更新
		//	g_Mouse.x += (g_MouseState.lX * g_Mouse.moveAdd);
		//	g_Mouse.y += (g_MouseState.lY * g_Mouse.moveAdd);

			//画面外チェック
			if (g_Mouse.x < g_Mouse.moveRect.left)
			{
				g_Mouse.x = g_Mouse.moveRect.left;
			}
			if (g_Mouse.x > g_Mouse.moveRect.right)
			{
				g_Mouse.x = g_Mouse.moveRect.right;
			}
			if (g_Mouse.y < g_Mouse.moveRect.top)
			{
				g_Mouse.y = g_Mouse.moveRect.top;
			}
			if (g_Mouse.y > g_Mouse.moveRect.bottom)
			{
				g_Mouse.y = g_Mouse.moveRect.bottom;
			}

			for (int nCntMouse = 0; nCntMouse < NUM_KEY_MAX; nCntMouse++)
			{//デバイスからデータを取得
				g_MouseStateTrigger[nCntMouse] = (MouseStateOld[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & g_MouseState.rgbButtons[nCntMouse];
				g_MouseStateRelease[nCntMouse] = (MouseStateOld[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & ~g_MouseState.rgbButtons[nCntMouse];
				g_MouseStateRepeat[nCntMouse] = g_MouseStateTrigger[nCntMouse];

				if (g_MouseState.rgbButtons[nCntMouse])
				{
					g_MouseStateRepeatCnt[nCntMouse]++;
					if (g_MouseStateRepeatCnt[nCntMouse] >= WAIT_COUNT_REPEAT)
					{
						g_MouseStateRepeat[nCntMouse] = g_MouseState.rgbButtons[nCntMouse];
					}
				}
				else
				{
					g_MouseStateRepeatCnt[nCntMouse] = 0;
					g_MouseStateRepeat[nCntMouse] = 0;
				}
			}
		}
		else
		{
			//マウスへのアクセス権を取得
			g_pDevMouse->Acquire();
		}
	}
	SetMouse(g_Mouse.x,g_Mouse.y);
	
}

/*------------------------------------------------------------------------------
|	マウスのプレス状態を取得
------------------------------------------------------------------------------*/
bool CSceneMouse::GetMousePress( int nKey )
{
	return ( g_MouseState.rgbButtons[ nKey ] & 0x80) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのトリガー状態を取得
------------------------------------------------------------------------------*/
bool CSceneMouse::GetMouseTrigger( int nKey )
{
	return ( g_MouseStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのリリース状態を取得
------------------------------------------------------------------------------*/
bool CSceneMouse::GetMouseRelease( int nKey )
{
	return ( g_MouseStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのリピート状態を取得
------------------------------------------------------------------------------*/
bool CSceneMouse::GetMouseRepeat( int nKey )
{
	return ( g_MouseStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスを取得
------------------------------------------------------------------------------*/
MSTATE *CSceneMouse::GetMouseState( void )
{
	return &g_Mouse;
}
void CSceneMouse::SetMouse(int x,int y)
{
	m_Position.x = (float)x;
	m_Position.y = (float)y;

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	nCount++;
	if((nCount % INTERVAL_PATTERN) == 0)
		{// アニメーション切り替え
			nPattern++;
			if(nPattern >= NUM_PATTERN )
			{// アニメーションパターンが終了
				nCount = 0;
				nPattern = 0;
			}
	pVtx[0].tex = D3DXVECTOR2(nPattern * TEXTURE_SIZE_X, nPattern * TEXTURE_SIZE_Y);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * TEXTURE_SIZE_X, nPattern * TEXTURE_SIZE_Y);
	pVtx[2].tex = D3DXVECTOR2(nPattern * TEXTURE_SIZE_X,(nPattern + 1) * TEXTURE_SIZE_Y);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * TEXTURE_SIZE_X, (nPattern + 1) * TEXTURE_SIZE_Y);
		}
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3( m_Position.x - m_width/2, m_Position.y - m_height/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3( m_Position.x + m_width/2, m_Position.y - m_height/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3( m_Position.x - m_width/2, m_Position.y + m_height/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( m_Position.x + m_width/2, m_Position.y + m_height/2, 0.0f);

	// 頂点データをアンロックする
	m_pVtxBuffer->Unlock();
}

//
// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CSceneMouse::CalcScreenToWorld(D3DXVECTOR3* pout,
											int Sx,  // スクリーンX座標
											int Sy,  // スクリーンY座標
											float fZ,  // 射影空間でのZ値（0～1）
											int Screen_w,
											int Screen_h,
											D3DXMATRIX* View,
											D3DXMATRIX* Prj
)
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse( &InvView, NULL, View );
	D3DXMatrixInverse( &InvPrj, NULL, Prj );
	D3DXMatrixIdentity( &VP );
	VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
	VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
	D3DXMatrixInverse( &InvViewport, NULL, &VP );

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,(float)fZ), &tmp );

	return pout;
}

// XZ平面とスクリーン座標の交点算出関数
D3DXVECTOR3* CSceneMouse::CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj)
{
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
	CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
	ray = farpos - nearpos;
	D3DXVec3Normalize( &ray, &ray );

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if( ray.y <= 0 )
	{
	// 床交点
	float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
	float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
	*pout = nearpos + (LP0/Lray)*ray;
	}
	else 
	{
		*pout = farpos;
	}

	return pout;
}
