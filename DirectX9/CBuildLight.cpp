/********************************************************************************
* タイトル　01
* ファイル名　CBuildLight
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/01/09
* BuildLight
********************************************************************************/

#include "CBuildLight.h"

//=============================================================================
// クラスコンストラクタ
//=============================================================================
CBuildLight::CBuildLight()
{
}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CBuildLight::~CBuildLight()
{

}
//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT CBuildLight::Init(D3DXVECTOR3 pos)
{
	CManager *manager = GetManager();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	for (int i = 0; i < BUILD_LIGHT_NUM; i++)
	{
		m_Light[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_Light[0].vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//m_Light[1].vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	//m_Light[2].vecDir = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	//m_Light[3].vecDir = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	m_Light[0].m_Range = 100.0f;
	m_Changge = 1;
	m_Position = pos;
	return S_OK;
}
void CBuildLight::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CRenderer *renderer = manager->GetRenderer();

	CBuildCamera *m_BuildCamera = BuildManager->GetBuildCamera();
	CBuildMenu_Wall *m_BuildMenu_Wall = BuildManager->GetBuildMenu_Wall();
	CEnemy_001 *m_Enemy_001 = BuildManager->GetEnemy_001(0);
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	//m_Position.x = (int)(m_BuildCamera->m_3DPos.x) - (int)(m_BuildCamera->m_3DPos.x) % 50;
	//m_Position.z = (int)(m_BuildCamera->m_3DPos.z) - (int)(m_BuildCamera->m_3DPos.z) % 50;
	//m_Position.y = 0 + m_Changge;
	//for (int nCntLight = 0; nCntLight < BUILD_LIGHT_NUM; nCntLight++)
	//{
	//	ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

	//	//POINT光源
	//	m_aLight[nCntLight].Type = D3DLIGHT_POINT;

	//	//色
	//	m_aLight[nCntLight].Diffuse = m_Light[nCntLight].diffuse;

	//	//位置
	//	m_aLight[nCntLight].Position = m_Position;

	//	//範囲
	//	m_aLight[nCntLight].Range = m_Light[0].m_Range;

	//	//光の方向
	//	//vecDir[nCntLight] = m_Light[nCntLight].vecDir;

	//	//正規化
	//	D3DXVec3Normalize((D3DXVECTOR3 *)&m_aLight[nCntLight].Direction, &vecDir[nCntLight]);

	//	//ライトの設定
	//	device->SetLight(nCntLight, &m_aLight[nCntLight]);

	//	//ライトを有効する
	//	//device->LightEnable(nCntLight, TRUE);
	//}
}
CBuildLight* CBuildLight::Create(D3DXVECTOR3 pos)
{
	CBuildLight *m_BuildLight;
	m_BuildLight = new CBuildLight;
	m_BuildLight->Init(pos);
	return m_BuildLight;
}