/********************************************************************************
* タイトル　01
* ファイル名　renderer.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float PI = 3.141592653589159f;

typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//構造体定義

typedef struct
{
	D3DXVECTOR3	pos;	//頂点座標
	D3DXVECTOR3	nor;	//法線ベクトル( 面の向き )
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ座標
	float			tu;
	float			tv;
}VERTEX_3D;

//*************************************
// D3Dクラス
//*************************************
class CRenderer 
{
public:
	CRenderer();				// コンストラクタ
	~CRenderer();				// デストラクタ
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Begin (void);
	void End (void);
	void Update(void);		//更新処理
	void DrawFPS( void );
	LPDIRECT3DDEVICE9 GetDevice(void);
private:
	LPDIRECT3D9 m_pD3D ;		//Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice ;	//Direct3Dデバイスへのポインタ
	LPD3DXFONT m_pFont ;		//フォントへのポインタ
	//CRenderer *m_Renderer;
};
extern int g_nCountFPS;		//FPSカウンタ
#endif