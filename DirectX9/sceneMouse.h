/********************************************************************************
* タイトル　01
* ファイル名　sceneMouse.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/23
*マウス処理
********************************************************************************/
#ifndef _SCENEMOUSE_H_
#define _SCENEMOUSE_H_


/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/

class CScene2D;
class CSceneInput;
/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
//マウスボタンの列挙型
typedef enum
{
	DIM_LEFT		= 0,		//マウス左ボタン
	DIM_RIGHT,					//マウス右ボタン
	DIM_CENTER,					//マウス中ボタン
	DIM_MAX
}MOUSE_BUTTONS;

//マウスポインタ情報の構造体
typedef struct
{
	RECT		moveRect;	//画面上で動ける範囲
	int			x;			//X座標
	int			y;			//Y座標
	int			moveAdd;	//移動量
}MSTATE;

class CSceneMouse 
{
friend class CField;
friend class CCamera;
friend class CBuildCamera;
friend class CDebugProc;
friend class CBall;
friend class CGun;
public:
	CSceneMouse();
	~CSceneMouse();
	HRESULT Init (HINSTANCE hInstance,HWND hWnd);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	MSTATE *GetMouseState( void );
	bool GetMousePress( int nKey );
	bool GetMouseTrigger( int nKey );
	bool GetMouseRelease( int key );
	bool GetMouseRepeat( int nKey );
	void SetMouse(int x,int y);
	D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout,int Sx,int Sy,float fZ,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);
	D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);
private:
	LPDIRECTINPUT8 m_MouseInput;					//IDirectInput8インターフェースへのポインタ
	MSTATE					g_Mouse;								//マウスのワーク
	DIMOUSESTATE			g_MouseState;							//マウス情報
	LPDIRECTINPUTDEVICE8	g_pDevMouse	;					//IDirectInputDevice8インターフェースへのポインタ(マウス)
	BYTE					g_MouseStateTrigger[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
	BYTE					g_MouseStateRelease[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
	BYTE					g_MouseStateRepeat[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
	int						g_MouseStateRepeatCnt[ NUM_KEY_MAX ];	//マウスのリピートカウンタ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer ;	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture ;
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	int nCount;			// カウンタ
	int nPattern;		// パターンNo

};
#endif