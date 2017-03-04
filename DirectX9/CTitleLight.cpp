/********************************************************************************
* タイトル　OPENGL 01
* ファイル名　sceneX.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/25
Xポリゴンの描画用
********************************************************************************/

#include "CTitleLight.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CTitleLight::CTitleLight()
{
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CTitleLight::~CTitleLight()
{

}
//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT CTitleLight::Init(void)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXVECTOR3 vecDir[TITLE_LIGHT_NUM];

	m_Light[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light[1].diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	m_Light[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light[3].diffuse = D3DXCOLOR(0.4f, 0.8f, 0.8f, 1.0f);

	m_Light[0].vecDir = D3DXVECTOR3(0.0f, -1.0f, -2.0f);
	m_Light[1].vecDir = D3DXVECTOR3(0.0f, -1.0f, 2.0f);
	m_Light[2].vecDir = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_Light[3].vecDir = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	for (int nCntLight = 0; nCntLight < TITLE_LIGHT_NUM; nCntLight++)
	{
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		//平行光源
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//拡散光
		m_aLight[nCntLight].Diffuse = m_Light[nCntLight].diffuse;

		//光の方向
		vecDir[nCntLight] = m_Light[nCntLight].vecDir;

		//正規化
		D3DXVec3Normalize((D3DXVECTOR3 *)&m_aLight[nCntLight].Direction, &vecDir[nCntLight]);

		//ライトの設定
		device->SetLight(nCntLight, &m_aLight[nCntLight]);

		//ライトを有効する
		device->LightEnable(nCntLight, TRUE);

		device->SetRenderState(D3DRS_LIGHTING,TRUE);
	}
	return S_OK;
}