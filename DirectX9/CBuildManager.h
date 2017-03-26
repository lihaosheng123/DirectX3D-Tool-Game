/********************************************************************************
* タイトル　CBUILDMANAGER
* ファイル名　CBuildManager.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/19
*Buildのマネジャー
********************************************************************************/
#ifndef _CBUILDMANAGER_H_
#define _CBUILDMANAGER_H_
//main用(重要)
#include "main.h"
#include "scene.h"
#include "Mode.h"
#include "CBuildMap.h"
#include "CAnimModel.h"
#include "CLoadMap.h"
#include "CBuildCamera.h"
#include "CBuildLoadMap.h"
#include "debugProc.h"
#include "sceneInput.h"
#include "sceneMouse.h"
#include "BuildSetMap.h"
#include "renderer.h"
//2DMenuの描画
#include "CBuildMenu.h"
#include "CBuildMenu_Wall.h"
#include "CBuildMenu_Enemy.h"
#include "CBuildMenu_Another.h"
#include "CBuildMenu_Prop.h"
//2D描画
#include "CBuildImage.h"
//3D描画
#include "CField.h"
#include "CWall_001.h"
#include "CWall_002.h"
#include "CCeiling.h"
#include "CTrail.h"
#include "Caxis.h"
#include "skybox.h"
#include "CColumnar.h"
#include "CEnd.h"
//3Dモデル
#include "CModel.h"
#include "CPlayer.h"
#include "CEnemy_001.h"
#include "CEnemy_002.h"
#include "CDoor.h"
#include "CStart.h"
#include "CPoint.h"
#include "CRobot.h"
//他
#include "CBuildLight.h"
/* 前方宣言開始 */
//main用(重要)
class CScene;
class CMode;
class CBuildMap;
class CLoadMap;
class CBuildCamera;
class CBuildLoadMap;
class CDebugProc;
class CSceneInput;
class CSceneMouse;
class CBuildSetMap;
class CRenderer;
//2DMenuの描画
class CBuildMenu;
class CBuildMenu_Wall;
class CBuildMenu_Enemy;
class CBuildMenu_Another;
class CBuildMenu_Prop;
//2D描画
class CBuildImage;
//3D描画
class CField;
class CWall_001;
class CWall_002;
class CCeiling;
class CTrail;
class Caxis;
class CSkybox;
class CColumnar;
class CEnd;
//3Dモデル
class CModel;
class CPlauer;
class CEnemy_001;
class CEnemy_002;
class CDoor;
class CStart;
class CPoint;
class CRobot;
//他
class CBuildLight;
class CAllocateHierarchy;
class CAnimModel;
/* 前方宣言終わる*/
/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildManager : public CMode
{
private:
	//main用(重要)
	CBuildCamera *m_BuildCamera;
	CSceneMouse *m_Mouse;
	CRenderer *m_Renderer;
	CBuildMap *m_BuildMap;
	CBuildLoadMap *m_BuildLoadMap;
	BuildSetMap *m_BuildSetMap;
	//2DMenuの描画
	CBuildMenu *m_BuildMenu;
	CBuildMenu_Wall *m_BuildMenu_Wall;
	CBuildMenu_Enemy *m_BuildMenu_Enemy;
	CBuildMenu_Prop *m_BuildMenu_Prop;
	CBuildMenu_Another *m_BuildMenu_Another;
	//2D描画
	CBuildImage *m_BuildImage;
	//3D描画
	CField *m_Field;
	CSkybox *m_sky;
	CWall_001 *m_Wall_001[1];
	CWall_002 *m_Wall_002[1];
	CGameWall_001 *m_GameWall_001;
	CGameWall_002 *m_GameWall_002;
	CTrail *m_Trail;
	CGameCeiling *m_GameCeiling;
	Caxis *m_axis;
	CCeiling *m_Ceiling[1];
	CColumnar *m_Columnar;
	CEnd *m_End;
	//3Dモデル
	CPlayer *m_Player;
	CEnemy_001 *m_Enemy_001[1];
	CEnemy_002 *m_Enemy_002[1];	
	CGameEnemy_001 *m_GameEnemy_001;
	CGameEnemy_002 *m_GameEnemy_002;
	CDoor *m_Door;
	CGameDoor *m_GameDoor;
	CPoint *m_Point;
	CGamePoint *m_GamePoint;
	CStart *m_Start;
	CRobot *m_Robot;
	//他
	CBuildLight *m_Light;
	CDebugProc *m_Debug;
	CAnimModel *m_AnimModel;
public:
	CBuildManager();
	~CBuildManager();
	virtual void Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Draw(void);		//描画処理
	virtual void Update(void);		//更新処理


	CBuildCamera* GetBuildCamera(void);
	CWall_001* GetBuildWall_001(int Index);
	CWall_002* GetBuildWall_002(int Index);
	CEnemy_001* GetEnemy_001(int Index);
	CEnemy_002* GetEnemy_002(int Index);
	CBuildMap* GetBuildMap(void);
	CBuildMenu* GetBuildMenu(void);
	CBuildMenu_Wall* GetBuildMenu_Wall(void);
	CBuildMenu_Enemy* GetBuildMenu_Enemy(void);
	CBuildLight* GetBuildLight(void);
	CTrail* GetBuildTrail(void);
	CBuildLoadMap* GetBuildLoadMap(void);
	CGameWall_001* GetGameWall_001(void);
	CGameWall_002* GetGameWall_002(void);
	CGameEnemy_001* GetGameEnemy_001(void);
	CGameEnemy_002* GetGameEnemy_002(void);
	CCeiling* GetCeiling(int Index);
	CGameCeiling* GetGameCeiling(void);
	CDoor* GetDoor(void);
	CBuildMenu_Prop* GetBuildMenu_Prop(void);
	CBuildMenu_Another* GetBuildMenu_Another(void);
	CPoint* GetPoint(void);
	CGameDoor* GetGameDoor(void);
	CGamePoint* GetGamePoint(void);
	CStart* GetStart(void);
	CEnd* GetEnd(void);
	CRobot* GetRobot(void);


	HINSTANCE hInstance;
	HWND hWnd;
};
#endif