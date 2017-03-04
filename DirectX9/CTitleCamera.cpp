/********************************************************************************
* タイトル　01
* ファイル名　TitleCamera.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/28
* TitleCamera
********************************************************************************/
#include "CTitleCamera.h"
//=============================================================================
// クラスコンストラクタ
//=============================================================================//
CTitleCamera::CTitleCamera()
{

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CTitleCamera::~CTitleCamera()
{

}
//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CTitleCamera::Init(void)
{
	CManager *manager = GetManager();

	CGame *game = (CGame*)CManager::GetMode();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


	// 視点（自分）
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);	// 0, 100~200, -100~-300

												// 注視点（見てる先）
	m_posR = D3DXVECTOR3(0.0f, 50.5f, 400.0f);

	// 上方向ベクトル（カメラ頭頂部）
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ほぼ変えない。

											// 向き（角度）
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	// m_posVとm_posRの対角線の長さ
	// posVとposRの対角線の長さ
	m_fDistance = sqrtf(((m_posR.x - m_posV.x) * (m_posR.z - m_posV.z)) + ((m_posR.z - m_posV.z) * (m_posR.z - m_posV.z)));
	//	m_fDistance =450.0f;
	m_bRotate = true;

}
void CTitleCamera::Uninit(void)
{

}
void CTitleCamera::Update(void)
{
	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CSceneInput *m_Input = manager->GetInput();

	CSceneMouse *m_Mouse = manager->GetMouse();

	CScore *m_Score = game->GetScore();

	CRenderer *renderer = manager->GetRenderer();

	CPlayer *m_Model = game->GetPlayer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		(D3DX_PI / 4),						// 視野角（カメラのレンズのように、広角or望遠）
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		// アスペクト比(16:9)
		NEAR_Z,									// NearZ値（カメラに映す範囲の、最前の距離）
		FAR_Z);								// Far値  （カメラに映す範囲の、最奥の距離）

											// プロジェクションマトリックスの設定
	device->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	device->SetTransform(D3DTS_VIEW, &m_mtxView);

	//向き角度のチェック
	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	//rot.y -= D3DX_PI * 0.0005f;
	m_bRotate = true;			//旋回中心を注視点に設定


	//視点中心
	if (m_bRotate == true)
	{
		m_posV.x = m_posR.x - m_fDistance * sinf(rot.y);
		m_posV.z = m_posR.z - m_fDistance * cosf(rot.y);
		m_bRotate = false;
	}

	//注視点中心
	else
	{
		m_posR.x = m_posV.x + m_fDistance * sinf(rot.y);
		m_posR.z = m_posV.z + m_fDistance * cosf(rot.y);
	}

}
void CTitleCamera::Draw(void)
{

}
