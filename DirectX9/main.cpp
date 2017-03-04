/********************************************************************************
* タイトル　01
* ファイル名　main.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#include "main.h"

CManager *g_Manager;


//グローバル変数
int g_nCountFPS;		//FPSカウンタ
//関数宣言
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
void Update (void);
void Draw (void);
void Uninit (void);
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
//宣言
int nID;

/********************************************************************
WinMain関数　Windows プログラムは WinMain から開始
*	表示ウィンドウの属性設定とWindowsへの登録
*	初期設定
*	メッセージループ
*********************************************************************/
int WINAPI WinMain ( HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR LPCmdLine,int nCmdShow )
{
	HWND hWnd;//ワインドウハンドル
	MSG msg;//メッセージ
	g_Manager = new CManager;
	//CManager::Init(hInstance,hWnd,bWindow);	//インスタンス生成,(new)しない
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//メリスを取得
		CS_CLASSDC,//ウインドウスト
		WndProc,//ウインドロフロシジのアドレス
		0,
		0,
		hInstance,//インスタンスハンドラレ
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"DX9",//名前
		NULL
	};

	//wcex.lpszMenuName= MAKEINTRESOURCE(1);

	RegisterClassEx(&wcex);
	hWnd = CreateWindowEx(0,
		"DX9",
		"DirectX",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);


	if(FAILED(g_Manager->Init(hInstance,hWnd,TRUE)))	//初期化処理(失敗したら)
	{
		return -1;
	}

	Init(hInstance,hWnd,TRUE);

	ShowWindow( hWnd, nCmdShow ) ;
	UpdateWindow( hWnd ) ;
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	timeBeginPeriod (1);
	dwFrameCount =
	dwCurrentTime = 0;
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	//メッセージループ
	while(1)
	{
		if(PeekMessage( &msg, NULL, 0, 0 ,PM_REMOVE)!= 0)
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );//メッセージの翻訳//キーボード利用を可能にする
				DispatchMessage( &msg ) ;// 制御をWindowsに戻す
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime -dwFPSLastTime)>=500)		//FPS
			{
				g_nCountFPS =
					(dwFrameCount *1000)
					/(dwCurrentTime - dwFPSLastTime );
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if((dwCurrentTime -dwExecLastTime)>=(1000/60))
			{
				dwExecLastTime = dwCurrentTime;
			Update();	//更新処理
			Draw();	//描画処理
			dwFrameCount ++;
			}
		}	

	}
	Uninit();	//終了処理
	UnregisterClass("box",wcex.hInstance);//名前
	timeEndPeriod(1);
	return(int)msg.wParam;
}

//=============================================================================
//  関数名　：Init
//  機能概要：全プログラム初期化処理
//  戻り値　：S_OK
//=============================================================================
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	//g_Manager -> Init( hInstance, hWnd, TRUE );
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：全プログラム終了処理
//  戻り値　：
//=============================================================================
void Uninit (void)
{
	g_Manager -> Uninit();
	delete g_Manager;
}
////=============================================================================
////  関数名　：Draw
////  機能概要：メッセージ画面描画
////  戻り値　：
////=============================================================================
void Draw (void)
{
	g_Manager -> Draw();
}
//=============================================================================
//  関数名　：Update
//  機能概要：プログラム更新処理
//  戻り値　：
//=============================================================================
void Update(void)
{
	g_Manager -> Update();
}
//=============================================================================
//		ウィンドウプロシージャ関数（WindowProcedure）
//		(Windowsメッセージ処理を行う)
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_DESTROY://"WM_QUIT"メッセージを返す//閉じるボタンをクリックした時
		PostQuitMessage(0);// WM_QUITメッセージを発行
		break;
	case WM_KEYDOWN://キーが押された
		switch(wParam)
		{
		case VK_ESCAPE://ESCキー
		nID=MessageBox(hWnd,"ESCしますか","ESC",MB_YESNO);

		if(nID==IDYES)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			DestroyWindow(hWnd);
		}
		break;
		}

	case VK_MENU:
	case 'F':
	case WM_COMMAND:
		{
			int menuID = LOWORD(wParam);
			switch(menuID)
			{
			case ID_MODE_PLAYERMODE:

				break;
				//壁
			case ID_BULIDMODE_40007:
				break;
				//敵
			case ID_BULIDMODE_40006:
				break;

			}
			break;

		}
	default:	//上記以外のメッセージはWindowsへ処理を任せる
	break;

	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
CManager *GetManager ( void )
{
	return g_Manager;
}
