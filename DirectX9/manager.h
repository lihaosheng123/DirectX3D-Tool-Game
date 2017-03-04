/********************************************************************************
* タイトル　01
* ファイル名　manger.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/05/09
*
********************************************************************************/
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "Mode.h"
#include "fade.h"

#include "sceneInput.h"
#include "sceneMouse.h"

#include "CTitle.h"
#include "CBuildManager.h"
#include "CGame.h"
#include "CResult.h"

#include "sound.h"
#include "renderer.h"
/* 前方宣言 */
class CRenderer;
class CScene;
class CSceneInput;
class CMode;
class CTitle;
class CGame;
class CBuildManager;
class CResult;
class CBubble;

//マクロ開放
#define RELEASE( d )	if( d != NULL )					\
						{								\
							( d ) -> Release();			\
							d = NULL;					\
						}
/* レンダラクラス 設定 */
class CManager
{
	friend class CBuildMap;
	friend class CTitle;
	friend class CBuildLoadMap;
	friend class CLevelLight;
	friend class CLevelModel;
	friend class CLoadMap;
	friend class CBuildManager;
	friend class CGameEnemy_001;
	friend class CGameEnemy_002;
	friend class CGameWall_001;
	friend class CGameWall_002;
	friend class CGame;
	friend class CGameCeiling;
	friend class CGameDoor;
	friend class CGamePoint;
	friend class CFade;
	friend class CGame002;
	public:
	
		enum MODE
		{
			MODE_TITLE,
			MODE_GAME,
			MODE_BUILD,
			MODE_RESULT
		};

	private:
	static CMode *m_Mode;

	static MODE m_OldMode;
	static MODE m_NewMode;

	static int m_FadeMode;
	static int m_FadeCount;
	static int m_ModeDelay;

	CRenderer *m_Renderer;
	CSceneInput *m_Input;
	CSceneMouse *m_Mouse;
	CFade *m_Fade;
	bool m_Build;
	bool m_MouseDraw;
	public:
		CManager();	// コンストラクタ
		~CManager();	// デストラクタ
		/* メイン 関連 */
		HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);		// 初期化処理
		void Uninit(void);		// 終了処理
		void Draw(void);		//描画処理
		void Update(void);		//更新処理
		static CMode* GetMode(void);
		static void SetMode( MODE Mode);
		/*ゲットデバイス */
		CRenderer* GetRenderer ( void );
		CSceneInput* GetInput ( void );
		CSceneMouse* GetMouse ( void );
		//CGame *GetGame ( void );

};
#endif