/********************************************************************************
* タイトル　TITLE
* ファイル名　CTitle.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
TITLEのモード処理
********************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "sceneInput.h"
#include "CTitle.h"
//------------------------------------------------------------------------------
//	関数名:	CTitle::CTitle
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	CManager *manager = GetManager();
	manager->m_MouseDraw = false;
}

//------------------------------------------------------------------------------
//	関数名:	CTitle::~CTitle
//	引数:	なし
//	戻り値:	CTitle
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CTitle::Init(void)
{
	m_Light = new CTitleLight;
	m_Light->Init();

	m_Camera = new CTitleCamera;
	m_Camera->Init();
	m_TitleSkyBox = CTitleSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, "NULL");
	m_Field = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, MESHFIELD_TEXTURE_FILE00);
	m_TitleModel = CTitleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_TITLE);
	m_Title_R_Model = CTitle_R_Model::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_R);
	m_TitleRobot = CTitleRobot::Create(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, MODEL_TITLE_MODEL);
	m_TitleMenu = CTitleMenu::Create(D3DXVECTOR3(100.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 150.0f, "NULL");
	m_TitleMark = CTitleMark::Create(D3DXVECTOR3(100.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 170.0f, TEXTURE_TITLEMARK);
	m_TitleImage = CTitleImage::Create(D3DXVECTOR3(SCREEN_CENTER_X, 170.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT / 5, SCREEN_WIDTH / 1.5, TEXTURE_TITLEIMAGE_FILE);

}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CTitle::Uninit(void)
{
	m_Camera->Uninit();
	delete m_Camera;

	delete m_Light;
	CScene::UninitAll();
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理

//------------------------------------------------------------------------------
void CTitle::Update(void)
{
	CManager *manager = GetManager();
	CSceneInput *m_Input = manager -> GetInput();
	CTitle *Title = (CTitle*)CManager::GetMode();
	CBuildManager *BuildManager = (CBuildManager*)CManager::GetMode();
	CBuildMap *m_BuildMap = BuildManager->GetBuildMap();
	CTitleMark *m_TitleMark = Title->GetTitleMark();
	m_Camera->Update();

	CScene::UpdateAll();


	if (m_TitleMark->m_type == m_TitleMark->TITLE_MENU_BUILD && m_Input->GetKeyboardTrigger(DIK_RETURN))
	{
		CManager::SetMode(CManager::MODE_BUILD);
	}


	if (m_TitleMark->m_type == m_TitleMark->TITLE_MENU_START && m_Input->GetKeyboardTrigger(DIK_RETURN))
	{
		CManager::SetMode(CManager::MODE_GAME);
	}
	if (m_TitleMark->m_type == m_TitleMark->TITLE_MENU_END && m_Input->GetKeyboardTrigger(DIK_RETURN))
	{
		exit(0);
	}

}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CTitle::Draw(void)
{
	CScene::DrawAll();

}

CTitleMark* CTitle::GetTitleMark(void)
{
	return m_TitleMark;
}
CTitleMenu* CTitle::GetTitleMenu(void)
{
	return m_TitleMenu;
}
CTitle_R_Model* CTitle::GetTitle_R_Model(void)
{
	return m_Title_R_Model;
}