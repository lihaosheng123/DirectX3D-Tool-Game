///********************************************************************************
//* タイトル　01
//* ファイル名　CEnemy_Bullet_Down.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/20
//*敵のbullet描画
//********************************************************************************/
#ifndef	_CENEMY_BULLET_DOWN_H_
#define	_CENEMY_BULLET_DOWN_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define	TEXTURE_ENEMY_BULLET_DOWN_FILE		"data\\TEXTURE\\bullet.png"	// 読み込むテクスチャファイル名
#define ENEMY_BULLET_DOWN_MAX (256)
#define ENEMY_BULLET_DOWN_SPEED (10.0f);
#include "scene.h"
typedef struct
{
	D3DXVECTOR3 m_scl;		//スケール値
	bool m_bUse;
	int m_Life;
	bool m_OneCheck;

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	CMatrix m_Matrix;
	D3DXVECTOR3 m_Vektor;
}ENEMY_BULLET_DOWN;
class CEnemy_Bullet_Down :public CScene
{
	friend class CPlayer;
	friend class CDebugProc;
	friend class CExplosion;
	friend class CGameEnemy_001;
public:
	CEnemy_Bullet_Down();
	~CEnemy_Bullet_Down();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CEnemy_Bullet_Down* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
	float Length(D3DXVECTOR3 *Vector);
	void SetBullet_Down(D3DXVECTOR3 pos);
	ENEMY_BULLET_DOWN* GetEnemy_Bullet_Down(void);
private:
	ENEMY_BULLET_DOWN m_Enemy_Bullet_Down[ENEMY_BULLET_DOWN_MAX];
	int m_Num;
	int frame;
	int cnt;
};
#endif