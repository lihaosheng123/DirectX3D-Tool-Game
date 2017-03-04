/********************************************************************************
* タイトル　CBuildMap.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップ管理、読み込み、ファイル作成
********************************************************************************/


#ifndef _CBUILDMAP_H_
#define _CBUILDMAP_H_

/*******************************************************************************
インクルード宣言
*******************************************************************************/
#include <stdio.h>
#include "CLoadMap.h"
/*******************************************************************************
マクロ定義
*******************************************************************************/

//前方宣言
class CWall_001;
class CWall_002;
class CEnemy_001;
class CEnemy_002;
class CBuildLight;
class CTrail;
class CCeiling;
class CDoor;
class CPoint;
class CColumnar;
class CStart;
class CEnd;
class CRobot;
/*******************************************************************************
クラス宣言
*******************************************************************************/
class CBuildMap
{
	//フレンドクラス
	friend class CDebugProc;
	friend class CBullet;
	friend class CTitle;
public:
	// コンストラクタ・デストラクタ
	CBuildMap();
	~CBuildMap();


	// 関数
	void Init(void);
	void Uninit(void);
	void Update(HINSTANCE hInstance, HWND hWnd);
	void Draw(void);
private:
	//描画の時表現用
	CWall_001 *p_Wall_001[1];
	CWall_002 *p_Wall_002[1];
	CEnemy_001 *p_Enemy_001[1];
	CEnemy_002 *p_Enemy_002[1];

	CBuildLight *p_Light[1];
	CTrail *p_Trail[1];

	CCeiling *p_Ceiling[1];
	CDoor *p_Door[1];
	CPoint *p_Point[1];
	CColumnar *p_Columnar[1];
	CStart *p_Start[1];
	CEnd *p_End[1];
	CRobot *p_Robot[1];

	//データの読み込み用(位置)
	int PosX;
	int PosY;
	int PosZ;
	//データの読み込み用(軌跡)
	int m_Trail_PosX;
	int m_Trail_PosY;
	int m_Trail_PosZ;
	//データの読み込み用(向き)
	float RotX;
	float RotY;
	float RotZ;

	//for文用
	int i;
	int cnt;

	//ファイルポインタ
	FILE *pFile;
	//ファイルの行データ
	char aStr[MAX_BUFFER];
	//格納する配列
	char aData[MAX_BUFFER];	

};
#endif