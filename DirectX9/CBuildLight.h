/********************************************************************************
* タイトル　01
* ファイル名　CBuildLight
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/01/09
* BuildLight
********************************************************************************/
#ifndef _CBUILDLIGHT_H_
#define _CBUILDLIGHT_H_
#include "main.h"
#include "manager.h"


//構造体
typedef struct
{
	D3DXCOLOR	diffuse;
	D3DXVECTOR3	vecDir;
	float m_Range;
}BUILDLIGHT;

//マクロ定義
#define BUILD_LIGHT_NUM 1

class CBuildLight
{
	friend class CBuildMap;
public:
	CBuildLight();
	~CBuildLight();
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化処理
	void Update(void);
	static CBuildLight* Create(D3DXVECTOR3 pos);//生成関数
private:

	D3DLIGHT9	m_aLight[BUILD_LIGHT_NUM];		//ライト情報
	BUILDLIGHT		m_Light[BUILD_LIGHT_NUM];		//光の方向と光の強さの構造体

	D3DXVECTOR3 vecDir[BUILD_LIGHT_NUM];
	D3DXVECTOR3	m_Position;
	int m_Changge;
};

#endif