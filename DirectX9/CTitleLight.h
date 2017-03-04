/********************************************************************************
* タイトル　01
* ファイル名　CTitleLight.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
* Light描画
********************************************************************************/
#ifndef _CTITLELIGHT_H_
#define _CTITLELIGHT_H_
#include "main.h"
#include "manager.h"


//構造体
typedef struct
{
	D3DXCOLOR	diffuse;
	D3DXVECTOR3	vecDir;
}TITLELIGHT;

//マクロ定義

#define TITLE_LIGHT_NUM 4

class CTitleLight
{
public:
	CTitleLight();
	~CTitleLight();
	HRESULT Init(void);		// 初期化処理
private:

	D3DLIGHT9	m_aLight[TITLE_LIGHT_NUM];		//ライト情報
	TITLELIGHT		m_Light[TITLE_LIGHT_NUM];		//光の方向と光の強さの構造体
};

#endif
