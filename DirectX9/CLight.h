/********************************************************************************
* タイトル　01
* ファイル名　sceneX.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
* Xポリゴン描画
********************************************************************************/
#ifndef _CLIGHT_H_
#define _CLIGHT_H_
#include "main.h"
#include "manager.h"


//構造体
typedef struct
{
	D3DXCOLOR	diffuse;
	D3DXVECTOR3	vecDir;
}LIGHT;

//マクロ定義

#define LIGHT_NUM 4

class CLight 
{
public:
	CLight();
	~CLight();
	HRESULT Init(void);		// 初期化処理
private:

	D3DLIGHT9	m_aLight[ LIGHT_NUM ];		//ライト情報
	LIGHT		m_Light[ LIGHT_NUM ];		//光の方向と光の強さの構造体
};

#endif