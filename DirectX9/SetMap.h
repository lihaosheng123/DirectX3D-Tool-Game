/********************************************************************************
* タイトル　SetMap.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/11/27
* ゲームのマップ管理
********************************************************************************/


#ifndef _SETMAP_H_
#define _SETMAP_H_

/*******************************************************************************
インクルード宣言
*******************************************************************************/
#include <stdio.h>

/*******************************************************************************
マクロ定義
*******************************************************************************/

/*******************************************************************************
クラス宣言
*******************************************************************************/
class CGameEnemy_001;
class CGameEnemy_002;
class CGameEnemy_001_data;
class CGameEnemy_002_data;

class CGameWall_001;
class CGameWall_002;
class CGameWall_001_data;
class CGameWall_002_data;
class CGameCeiling_data;
class CGameCeiling;
class CGameDoor_data;
class CGameDoor;
class CGamePoint;
class SetMap
{
	friend class CDebugProc;
	friend class CBullet;
	friend class CGameWall_001;
	friend class CGameEnemy_001;
	friend class CGameEnemy_002;
	friend class CEnemy_Bullet;
	friend class CGameCeiling;
public:

	// コンストラクタ・デストラクタ
	SetMap();
	~SetMap();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理

private:
	int i;
};
#endif