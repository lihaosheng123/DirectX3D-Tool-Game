/********************************************************************************
* タイトル　GAME
* ファイル名　CGame.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
*
********************************************************************************/
#ifndef _CGAME_H_
#define _CGAME_H_

#include "main.h"
#include "scene.h"
#include "Mode.h"
#include "CTitle.h"
#include "CGame.h"
#include "CResult.h"
#include "sceneInput.h"
#include "sceneMouse.h"
#include "scene2D.h"
#include "Cskillbg.h"
#include "CResultbg.h"
#include "score.h"
#include "CHpScore.h"
#include "number.h"
#include "CTimeScore.h"
#include "CTime.h"


#include "scene3D.h"
#include "CField.h"
#include "CEnemy_Effect.h"

#include "CGameWall_001.h"
#include "CGameWall_002.h"
#include "CBulletHoles.h"
#include "skybox.h"
#include "CModel.h"
#include "sceneBillboard.h"
#include "CSmoke.h"
#include "CExplosion.h"
#include "bullet.h"
#include "CEnemey_Bullet_Up.h"
#include "CEnemy_Bullet_Down.h"
#include "CEnemy_Bullet_Left.h"
#include "CEnemy_Bullet_Right.h"


#include "CTransferEffect.h"
#include "Unique_skill.h"


#include "debugProc.h"

#include "Camera.h"
#include "CLoadMap.h"

#include "sceneX.h"
#include "CRevolverModel.h"
#include "CGameEnemy_001.h"
#include "CGameEnemy_002.h"
#include "cylinder.h"
#include "CPlayer.h"
#include "portal.h"
#include "CLight.h"
#include "renderer.h"
#include "sound.h"

#include "CGameEnemy_001_data.h"
#include "CGameEnemy_002_data.h"
#include "CGameWall_001_data.h"
#include "CGameWall_002_data.h"
#include "CGameCeiling_data.h"
#include "CGameDoor_data.h"
#include "CGameCeiling.h"
#include "CGameDoor.h"
#include "CDoorEffect.h"
#include "CColumnar.h"
#include "CGamePoint_data.h"
#include "CGamePoint.h"
#include "CGlass.h"
#include "CSpark.h"
#include "SetMap.h"
#include "CHpImage.h"
#include "CPowerImage.h"
#include "CPowerPoly.h"
#include "CPowerMax.h"
#include "CGameRobot.h"
#include "CTalkRobotImage.h"
#include "CTextbubble.h"
//マクロ定義

/* 前方宣言 */
class CRenderer;
class CScene;
class CSceneInput;
class CCamera;
class CLight;
class CSceneX;
class CSceneBillboard;
class CSceneMouse;
class CSkydome;
class CNumber;
class CBullet;
class CField;
class CGun;
class CScore;
class CSkybox;
class CSound;
class CBall;
class CBullet;
class CEffect;
class CFox;
class CPlayer;
class CBubble;
class CEnemy;
class CPortal;
class CTimeScore;
class CTarget;
class CWall;
class COrbit;
class cylinder;
class CUnique_skill;
class Cskillbg;
class CMap;
class CModelEnemy;
class CEnemyTarget;
class CTestModel;
class CSmoke;
class CExplosion;
class CLoadMap;
class CGameWall_001;
class CGameWall_002;
class CGameEnemy_001;
class CGameEnemy_002;

class CGameEnemy_001_data;
class CGameEnemy_002_data;
class CGameWall_001_data;
class CGameWall_002_data;
class CExplosion;
class CEnemy_Bullet_Up;
class CEnemy_Bullet_Down;
class CEnemy_Bullet_Left;
class CEnemy_Bullet_Right;
class CEnemy_Effect;
class CGameCeiling_data;
class CGameDoor_data;
class CGameCeiling;
class CGameelevator;
class CGameDoor;
class CDoor_Effect;
class CColumnar;
class CGamePoint_data;
class CGamePoint;
class CGlass;
class CSpark;
class SetMap;
class CRevolverModel;
class CHpScore;
class CHpImage;
class CPowerImage;
class CPowerPoly;
class CPowerMax;
class CGameRobot;
class CTalkRobotImage;
class CTextbubble;
class CGame : public CMode
{
private:
	CLoadMap *m_LoadMap;
	SetMap *m_SetMap;
	CCamera *m_Camera;
	CLight *m_Light;
	CScene3D *m_3D;
	CSceneX *m_SceneX;
	CSceneMouse *m_Mouse;
	CField *m_Field;
	CSkybox *m_sky;
	CScore *m_score;
	CNumber *m_Number;
	CTime *m_Time;
	CSound *m_Sound;
	CHpImage *m_HpImage;
	CEffect *m_Effect;

	CDebugProc *m_Debug;
	CPlayer *m_Player;
	CRenderer *m_Renderer;
	CBullet *m_Bullet;
	CEnemy *m_Enemy;
	CExplosion *m_Explosion;
	CPortal *m_Portal;
	CTimeScore *m_TimeScore;
	CTransferEffect *m_TransferEffect;
	CBulletHoles *m_BulletHoles;
	COrbit *m_Orbit;
	cylinder *m_Cylinder;
	CUnique_skill *m_Unique_skill;
	Cskillbg *m_Cskillbg;
	CTarget *m_Target[1];
	CEnemyTarget *m_EnemyTarget[1];
	CSmoke *m_Smoke;
	CGameEnemy_001 *m_GameEnemy_001;
	CGameEnemy_002 *m_GameEnemy_002;
	CGameWall_001 *m_GameWall_001;
	CGameWall_002 *m_GameWall_002;
	CGameEnemy_001_data *m_GameEnemy_001_data;
	CEnemy_Effect *m_Enemy_Effect;
	CDoor_Effect *m_Door_Effect[100];
	CEnemy_Bullet_Up *m_Enemy_Bullet_Up;
	CEnemy_Bullet_Down *m_Enemy_Bullet_Down;
	CEnemy_Bullet_Left *m_Enemy_Bullet_Left;
	CEnemy_Bullet_Right *m_Enemy_Bullet_Right;
	CGameCeiling *m_GameCeiling;
	CGameDoor *m_GameDoor;
	CColumnar *m_Columnar[100];
	CGamePoint *m_GamePoint;
	CGlass *m_Glass;
	CSpark *m_Spark;
	CHpScore *m_HpScore;
	CPowerImage *m_PowerImage;
	CPowerPoly *m_PowerPoly;
	CPowerMax *m_PowerMax;
	CGameRobot *m_GameRobot;
	CTalkRobotImage *m_TalkRobotImage;
	CTextbubble *m_Textbubble;
public:
	CGame();
	~CGame();
	virtual void Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Draw(void);		//描画処理
	virtual void Update(void);		//更新処理

	CField* GetField(void);

	CCamera* GetCCamera(void);
	CScore* GetScore(void);
	CHpScore* GetHpScore(void);
	CNumber* GetNum(void);
	CTime* GetTime(void);
	CEffect* GetEffect(void);

	CPlayer* GetPlayer(void);
	CBullet* GetBullet(void);
	CExplosion* GetExplosion(void);
	CGlass* GetGlass(void);
	CTransferEffect* GetTransferEffect(void);

	CGameWall_001* GetGameWall_001(void);
	CGameWall_002* GetGameWall_002(void);
	CGameEnemy_001* GetGameEnemy_001(void);
	CGameEnemy_002* GetGameEnemy_002(void);
	CGameCeiling* GetGameCeiling(void);
	CGameDoor* GetGameDoor(void);
	CBulletHoles* GetBulletHoles(void);
	CEnemy* GetEnemy(void);
	COrbit* GetOrbit(void);
	CUnique_skill* GetUnique_skill(void);
	Cskillbg* Getskillbg(void);


	CSmoke* GetSmoke(void);
	CLoadMap* GetLoadMap(void);

	CGameEnemy_001_data* GetGameEnemy_001_data(void);
	CEnemy_Bullet_Up* GetEnemy_Bullet_Up(void);
	CEnemy_Bullet_Down* GetEnemy_Bullet_Down(void);
	CEnemy_Bullet_Left* GetEnemy_Bullet_Left(void);
	CEnemy_Bullet_Right* GetEnemy_Bullet_Right(void);
	CEnemy_Effect* GetEnemy_Effect(void);
	CDoor_Effect* GetDoor_Effect(int Index);
	CColumnar* GetColumnar(int Index);
	CGamePoint* GetGamePoint(void);
	CSpark* GetSpark(void);
	CHpImage* GetHpImage(void);
	CGameRobot* GetGameRobot(void);
	CTalkRobotImage* GetTalkRobotImage(void);
	HINSTANCE hInstance;
	HWND hWnd;
};

#endif