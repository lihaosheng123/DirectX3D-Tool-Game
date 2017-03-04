/********************************************************************************
* タイトル　01
* ファイル名 main.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_
//インクルードファイル
#define  DIRECTINPUT_VERSION ( 0x0800 )
#include <windows.h>
#include "resource.h"
#include "d3dx9.h"	//描画処理に必要
#include "dinput.h"		//入力処理に必要
#include "xaudio2.h"		// XAudio2関連のヘッダー
#include "manager.h"
//#pragmaディレィディブ追加（ライブラリのリンク）
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//上記の拡張うイブウリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンボ―ネント使用に必要
#pragma comment(lib,"winmm.lib")
#pragma comment ( lib, "dinput8.lib" )		//入力処理に必要
#pragma warning ( disable: 4996 )			//
//マクロ定義
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define SCREEN_CENTER_X	( SCREEN_WIDTH / 2 )		//ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	( SCREEN_HEIGHT / 2 )		//ウインドウの中心Ｙ座標
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//テクスチャ座標
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//頂点座標(3d) | 法線 | 頂点カラー | テクスチャ座標


//マクロ開放
#define RELEASE( d )	if( d != NULL )					\
						{								\
							( d ) -> Release();			\
							d = NULL;					\
						}
class CManager;
class CGmae;
class CRenderer;		//前方宣言
CManager *GetManager ( void );
#endif