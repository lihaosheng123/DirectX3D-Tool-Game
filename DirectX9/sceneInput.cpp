/********************************************************************************
* タイトル　GM 01
* ファイル名　sceneInput.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/05
* input入力全処理
********************************************************************************/
/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneInput.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CSceneInput::CSceneInput()
{
	m_pInput = NULL;					//IDirectInput8インターフェースへのポインタ
	m_pDevKeyboard	 = NULL;					//IDirectInputDevice8インターフェースへのポインタ(キーボード)
	for(int cntInput = 0;cntInput < NUM_KEY_MAX ;cntInput++)
	{
		m_KeyState[ cntInput ] = 0;				//キーボードの状態を受け取るワーク
		m_KeyStateTrigger[ cntInput ] = 0;		//キーボードの状態を受け取るワーク
		m_KeyStateRelease[ cntInput ] = 0;		//キーボードの状態を受け取るワーク
		m_KeyStateRepeat[ cntInput ] = 0;		//キーボードの状態を受け取るワーク
		m_KeyStateRepeatCnt[ cntInput ] = 0;		//キーボードのリピートカウンタ
		KeyStateOld[ cntInput ] = 0;
	}

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CSceneInput::~CSceneInput()
{

}
//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT CSceneInput ::Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	if( m_pInput == NULL )
	{
		//DirectInputオブジェクトの作成
		if( FAILED(
			DirectInput8Create
			(
				hInstance,
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				( void** )&m_pInput,
				NULL
			) ) )
		{
			MessageBox( hWnd, "DirectInput8オブジェクトの作成(キーボード用)できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}
	}

	if( FAILED( m_pInput -> CreateDevice( GUID_SysKeyboard, &m_pDevKeyboard, NULL ) ) )
	{//デバイスオブジェクトを作成
		MessageBox( hWnd, "キーボードがありません！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	if( m_pDevKeyboard != NULL )
	{
		if( FAILED( m_pDevKeyboard -> SetDataFormat( &c_dfDIKeyboard ) ) )											//データフォーマットの設定
		{//データフォーマットを設定
			MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//協調モードを設定（フォアグラウンド＆非排他モード）
		if( FAILED( m_pDevKeyboard -> SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )	//協調モードの設定
		{
			MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//入力制御開始
		m_pDevKeyboard -> Acquire();
	}
	
	return S_OK;
}
//================================================================================================================================================================================================
// Uninit関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CSceneInput ::Uninit( void )
{
	RELEASE(m_pDevKeyboard);
	RELEASE(m_pInput);
}
//================================================================================================================================================================================================
// Update関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CSceneInput ::Update( void )
{
	if( m_pDevKeyboard != NULL )
	{

		//前回のデータを保存
		memcpy( KeyStateOld, m_KeyState, NUM_KEY_MAX );

		if( SUCCEEDED( m_pDevKeyboard -> GetDeviceState( sizeof( m_KeyState ),m_KeyState ) ) )
		{//デバイスからデータを取得
			for( int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++ )
			{
				m_KeyStateTrigger[ nCntKey ] = ( KeyStateOld[nCntKey] ^ m_KeyState[ nCntKey ] ) & m_KeyState[ nCntKey ];
				m_KeyStateRelease[ nCntKey ] = ( KeyStateOld[nCntKey] ^ m_KeyState[ nCntKey ] ) & ~m_KeyState[ nCntKey ];
				m_KeyStateRepeat[ nCntKey ]  = m_KeyStateTrigger[nCntKey];

				if( m_KeyState[ nCntKey ] )
				{
					m_KeyStateRepeatCnt[ nCntKey ]++;
					if( m_KeyStateRepeatCnt[ nCntKey ] >= WAIT_COUNT_REPEAT )
					{
						m_KeyStateRepeat[ nCntKey ] = m_KeyState[ nCntKey ];
					}
				}
				else
				{
					m_KeyStateRepeatCnt[ nCntKey ] = 0;
					m_KeyStateRepeat[ nCntKey ] = 0;
				}
			}
		}
		else
		{
			//キーボードへのアクセス権を取得
			m_pDevKeyboard -> Acquire();
		}
	}
}
//================================================================================================================================================================================================
// Draw関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CSceneInput ::Draw( void )
{

}
/*------------------------------------------------------------------------------
|	インターフェースへのポインタを取得
------------------------------------------------------------------------------*/
LPDIRECTINPUT8 CSceneInput ::GetpInput( void )
{
	return m_pInput;
}
/*------------------------------------------------------------------------------
|	キーボードのプレス状態を取得
------------------------------------------------------------------------------*/
bool CSceneInput ::GetKeyboardPress( int nKey )
{
	return ( m_KeyState[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのトリガー状態を取得
------------------------------------------------------------------------------*/
bool CSceneInput ::GetKeyboardTrigger( int nKey )
{
	return ( m_KeyStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのリリース状態を取得
------------------------------------------------------------------------------*/
bool CSceneInput ::GetKeyboardRelease( int nKey )
{
	return ( m_KeyStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのリピート状態を取得
------------------------------------------------------------------------------*/
bool CSceneInput ::GetKeyboardRepeat( int nKey )
{
	return ( m_KeyStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

