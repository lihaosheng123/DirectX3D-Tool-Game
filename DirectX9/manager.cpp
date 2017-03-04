/********************************************************************************
* タイトル　01
* ファイル名　manager.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/09
*
********************************************************************************/

#include "manager.h"

CMode* CManager::m_Mode;

CManager::MODE CManager::m_OldMode;
CManager::MODE CManager::m_NewMode;

int CManager::m_FadeMode;
int CManager::m_FadeCount;
int CManager::m_ModeDelay;
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager( void )
{
	m_Build = false;
	m_MouseDraw = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//  関数名　：Init
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT CManager ::Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	m_Renderer = new CRenderer;
	m_Renderer->Init(hInstance,hWnd,bWindow);

	m_Input = new CSceneInput;
	m_Input->Init(hInstance,hWnd,bWindow);

	m_Fade = new CFade();
	m_Fade->Init();
	
	m_FadeMode = 0;
	m_FadeCount = 34;


	m_Mode = new CTitle();
	m_Mode->Init();

	m_Mouse = new CSceneMouse;
	m_Mouse->Init(hInstance,hWnd);

	m_OldMode = MODE_TITLE;
	m_NewMode = MODE_TITLE;

	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：D3D終了処理
//  戻り値　：void
//=============================================================================
void CManager :: Uninit (void)
{


	m_Input->Uninit();
	delete m_Input;

	m_Mouse->Uninit();
	delete m_Mouse;

	m_Fade->Uninit();
	delete m_Fade;


	if( m_Mode )
	{
		//メモリー解放
		m_Mode->Uninit();
		delete m_Mode;
		m_Mode = NULL;
	}


	if( m_Renderer )
	{
		m_Renderer->Uninit();
		delete m_Renderer;
		m_Renderer = NULL;
	}



}
//=============================================================================
//  関数名　：Draw
//  機能概要：D3D画面描画用
//  戻り値　：void
//=============================================================================
void CManager:: Draw (void)
{
	/* 描画開始 関数 */
	m_Renderer->Begin();
	m_Mode->Draw();
	if (m_FadeMode != 0)
	{
		m_Fade->Draw();
	}
	if (m_MouseDraw == true)
	{
		m_Mouse->Draw();
	}
	/* 描画終了 関数 */
	m_Renderer->End();


}
//=============================================================================
//  関数名　：Update
//  機能概要：D3D画面描画用
//  戻り値　：void
//=============================================================================
void CManager:: Update (void)

{
	CManager *manager = GetManager();

	CRenderer *renderer = manager -> GetRenderer();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	CSceneInput *m_Input = manager -> GetInput();
	//if(m_Input->GetKeyboardPress( DIK_F1 ))
	//{
	//	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//線だかあるの場合
	//}
	//else 
	//{
	//	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}
	m_Input->Update();
	m_Mode->Update();
	m_Renderer->Update();
	m_Mouse->Update();
	m_Fade->Update();


	if( m_FadeMode == 1)
	{
		m_FadeCount++;

		if( m_FadeCount > 34 )
		{
			m_FadeCount = 34;
			//メモリー解放
			m_Mode->Uninit();
		
 			switch( m_NewMode )
			{
				case MODE_TITLE:
					m_Mode = new CTitle();
					break;

				case MODE_GAME:
					m_Mode = new CGame();
					break;

				case MODE_BUILD:
					m_Mode = new CBuildManager();
					break;

				case MODE_RESULT:
					m_Mode = new CResult();
					break;
			}

			m_Mode->Init();

			m_OldMode = m_NewMode;


			m_FadeMode = -1;
		}
	}
	else if( m_FadeMode == -1 )
	{
		m_FadeCount--;

		if( m_FadeCount < 0 )
		{
			m_FadeCount = 0;
				
			m_FadeMode = 0;
		}
	}


}
void CManager::SetMode(MODE Mode)
{

	m_NewMode = Mode;


	m_FadeMode = 1;
	m_FadeCount = 0;
}
CMode* CManager::GetMode(void)
{
	 return m_Mode; 
}
//戻り値　：CRenderer*
CRenderer* CManager::GetRenderer ( void )
{
	return m_Renderer;
}
CSceneInput* CManager::GetInput ( void )
{
	return m_Input;
}
CSceneMouse* CManager::GetMouse ( void )
{
	return m_Mouse;
}
