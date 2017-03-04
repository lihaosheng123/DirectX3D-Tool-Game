/********************************************************************************
* タイトル　01
* ファイル名　sceneInput.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/05
* input入力全処理
********************************************************************************/
#ifndef _SCENEINPUT_H_
#define _SCENEINPUT_H_
/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
#define	NUM_KEY_MAX			( 256 )		//キーの最大数
#define	WAIT_COUNT_REPEAT	( 20 )		//リピート開始までの待ち時間

class CSceneInput  
{
public:
	CSceneInput();
	~CSceneInput();
	HRESULT Init (HINSTANCE hInstance,HWND hWnd,BOOL bWindow);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		//更新処理
	void Draw(void);
	LPDIRECTINPUT8 GetpInput( void );
	bool	GetKeyboardPress( int key );
	bool	GetKeyboardTrigger( int key );
	bool	GetKeyboardRelease( int key );
	bool	GetKeyboardRepeat( int key );
private:
	LPDIRECTINPUT8 m_pInput;					//IDirectInput8インターフェースへのポインタ
	BYTE					m_KeyState[ NUM_KEY_MAX ];				//キーボードの状態を受け取るワーク
	BYTE					m_KeyStateTrigger[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
	BYTE					m_KeyStateRelease[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
	BYTE					m_KeyStateRepeat[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
	int						m_KeyStateRepeatCnt[ NUM_KEY_MAX ];		//キーボードのリピートカウンタ
	BYTE					KeyStateOld[ NUM_KEY_MAX ];
	LPDIRECTINPUTDEVICE8	m_pDevKeyboard	;					//IDirectInputDevice8インターフェースへのポインタ(キーボード)
};
#endif
