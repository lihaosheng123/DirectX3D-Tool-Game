/********************************************************************************
* タイトル　01
* ファイル名　CBuildCamera.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/20
* ツールモードで、カメラの作成
********************************************************************************/
#include "main.h"
#include "CBuildManager.h"
#include "CBuildCamera.h"
#include "sceneInput.h"
#include "sceneMouse.h"
//=============================================================================
// クラスコンストラクタ
//=============================================================================//
CBuildCamera::CBuildCamera()
{

}
//=============================================================================
// クラスデストラクタ
//=============================================================================
CBuildCamera::~CBuildCamera()
{

}
//================================================================================================================================================================================================
// Init関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void CBuildCamera::Init(void)
{
	CManager *manager = GetManager();

	CGame *game = (CGame*)CManager::GetMode();

	CRenderer *renderer = manager->GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 視点（自分）
	m_posV = D3DXVECTOR3(0.0f, 800.1f, 0.1f);	// 0, 100~200, -100~-300

												// 注視点（見てる先）
	m_posR = D3DXVECTOR3(0.0f, 500.5f, 200.0f);

	// 上方向ベクトル（カメラ頭頂部）
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ほぼ変えない。

											// 向き（角度）
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// posVとposRの対角線の長さ
	m_fDistance = sqrtf(((m_posR.x - m_posV.x) * (m_posR.z - m_posV.z)) + ((m_posR.z - m_posV.z) * (m_posR.z - m_posV.z)));
	m_bRotate = true;

}
void CBuildCamera::Uninit(void)
{

}
void CBuildCamera::Update(void)
{
	CManager *manager = GetManager();
	CSceneInput *m_Input = manager->GetInput();

	CSceneMouse *m_Mouse = manager->GetMouse();


	CRenderer *renderer = manager->GetRenderer();


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
	D3DXMatrixLookAtLH(&m_mtxView,&m_posV,&m_posR,&m_vecU);

	// ビューマトリックスの設定
	device->SetTransform(D3DTS_VIEW, &m_mtxView);

	//カメラの回転糸数
	rot.y += m_Mouse->g_MouseState.lX *0.010f;

	//カメラと3Dマウスの位置糸数
	m_posR.y -= m_Mouse->g_MouseState.lY * 0.525f;

	//回転最大最小のチェック
	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	//視点の座標からposR(注視点)を求める。
	m_posR.x = m_posV.x;
	//視点の座標からposR(注視点)を求める。(100)
	m_posR.z = m_posV.z - 100.0f;

	//カメラの前移動
	if (m_Input->GetKeyboardPress(DIK_W) == true)
	{
		m_posV.x += sinf(rot.y) * BUILDCAMERA_MOVE;
		m_posV.z += cosf(rot.y) * BUILDCAMERA_MOVE;
		m_posR.x = m_posV.x - sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z - cosf(rot.y) * m_fDistance;
	}

	//カメラの后移動
	if (m_Input->GetKeyboardPress(DIK_S) == true)
	{
		m_posV.x += sinf(D3DX_PI*-1.0f + rot.y) * BUILDCAMERA_MOVE;
		m_posV.z += cosf(D3DX_PI*-1.0f + rot.y) * BUILDCAMERA_MOVE;
		m_posR.x = m_posV.x - sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z - cosf(rot.y) * m_fDistance;
	}

	//カメラの左移動
	if (m_Input->GetKeyboardPress(DIK_A) == true)
	{
		m_posV.x += sinf(D3DX_PI*-0.5f + rot.y) * BUILDCAMERA_MOVE;
		m_posV.z += cosf(D3DX_PI*-0.5f + rot.y) * BUILDCAMERA_MOVE;
		m_posR.x = m_posV.x - sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z - cosf(rot.y) * m_fDistance;
	}

	//カメラの右移動
	if (m_Input->GetKeyboardPress(DIK_D) == true)
	{
		m_posV.x += sinf(D3DX_PI*+0.5f + rot.y) * BUILDCAMERA_MOVE;
		m_posV.z += cosf(D3DX_PI*+0.5f + rot.y) * BUILDCAMERA_MOVE;
		m_posR.x = m_posV.x - sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z - cosf(rot.y) * m_fDistance;
	}

	//上がり
	if (m_Input->GetKeyboardPress(DIK_T))
	{
		m_posV.y += 5.0f;
	}

	//下がり
	if (m_Input->GetKeyboardPress(DIK_B))
	{
		m_posV.y -= 5.0f;
	}

	//視点中心のモード
	if (m_bRotate == true)
	{
		m_posV.x = m_posR.x - m_fDistance * sinf(rot.y);
		m_posV.z = m_posR.z - m_fDistance * cosf(rot.y);
		m_bRotate = false;
	}

	//注視点中心のモード
	else
	{
		m_posR.x = m_posV.x + m_fDistance * sinf(rot.y);
		m_posR.z = m_posV.z + m_fDistance * cosf(rot.y);
	}

	//マウス3D化の関数
	m_Mouse->CalcScreenToXZ(&m_3DPos, (int)m_Mouse->g_Mouse.x, (int)m_Mouse->g_Mouse.y, SCREEN_WIDTH, SCREEN_HEIGHT, &m_mtxView, &m_mtxProjection);
	
}
void CBuildCamera::Draw(void)
{

}
