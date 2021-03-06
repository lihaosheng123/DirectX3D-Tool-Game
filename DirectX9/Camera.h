/********************************************************************************
* タイトル　01
* ファイル名　Camera.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/28
* Camera描画
********************************************************************************/
#ifndef	_CAMERA_H_
#define	_CAMERA_H_

#include "main.h"
#include "manager.h"

/*******************************************************************************
* マクロ定義	
*******************************************************************************/
#define ANGLE_CAMERA (45.0f)		//ラジアン
#define ASPECT_CAMERA (SCREEN_WIDTH/SCREEN_HEIGHT)		//アスペクト比
#define NEAR_Z (10.0f)		//NearZ値
#define FAR_Z (10000.0f)		//FarZ値
#define CAMERA_MOVE (10.0f)		//+カメラの移動量
class CCamera 
{
friend class CField;
friend class  CSceneMouse;
friend class CDebugProc;
friend class CGun;
friend class CBall;
friend class CWall;
friend class CPlayer;
friend class CBullet;
friend class CScore;
friend class COrbit;
friend class CMap;
friend class CTarget;
friend class CEnemyTarget;
friend class CCamera;
friend class CEnemy_Bullet;
public:
	D3DXVECTOR3 m_posV;		//視点
	D3DXVECTOR3 m_posR;		//注視点
	D3DXVECTOR3 m_OldPosV;
	D3DXVECTOR3 m_vecU;		//上方面ベクトル
	D3DXMATRIX m_mtxProjection;		//プロジェクションストリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	D3DXVECTOR3 rot;		//向き
	float m_fDistance;		//距離
	bool m_bRotate;	//trueなら視点を中心、falseなら注視点を中心
	D3DXVECTOR3 m_RotCheck;		//check向き
	D3DXVECTOR3 m_3DPos;
	CEffect *m_Effect;
	D3DXVECTOR3 m_Velocity;
	D3DXVECTOR3 m_Vektor;
	D3DXVECTOR3 m_regulator;
	D3DXVECTOR3 m_GunPos;
public:
	CCamera();
	~CCamera();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void) ;		//描画処理
	void Update(void);		//更新処理

	
};
#endif