/********************************************************************************
* タイトル　01
* ファイル名　CPlayer.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/20
* X Player描画
********************************************************************************/
#ifndef _CPLAYER_H_
#define _CPLAYER_H_

//マクロ定義
#define MODEL_INERTIA_MOVE (0.025f);
#define MODEL_MOVE (5.0f);
class CField;
class CFox;
class CModel;
class CRevolverModel;
struct KEY		//１パーツ、１フレーム
{
	float PositionX;
	float PositionY;
	float PositionZ;
	float RotationX;
	float RotationY;
	float RotationZ;
};

struct KEY_INFO_REVOLVER		//10パーツ、１フレーム
{
	int Frame;
	KEY m_Revolver_Key[6];
};

struct KEY_INFO_MACHINEGUN		//10パーツ、１フレーム
{
	int Frame;
	KEY m_MachineGuns_key[1];
};



enum MOTIONTYPE
{
	MOTIONTYPE_NEUTRAL,
	MOTIONTYPE_RUN,
	MOTIONTYPE_ATTACK,
	MOTIONTYPE_SIXATTACK,
	MOTIONTYPE_MAX
};

class CPlayer : public CScene
{
friend class CGun;
friend class CSkybox;
friend class CDebugProc;
friend class CCamera;
friend class CBuildCamera;
friend class CBall;
friend class CEffect;
friend class CField;
friend class CUnique_skill;
friend class CBullet;
friend class CGameEnemy_001;
friend class CGameEnemy_002;
friend class CGameWall_001;
friend class CGameWall_002;
friend class CEnemy_Bullet_Up;
friend class CEnemy_Bullet_Down;
friend class CEnemy_Bullet_Left;
friend class CEnemy_Bullet_Right;
friend class CGameelevator;
friend class CColumnar;
friend class CGamePoint;
friend class CGameDoor;
friend class CDoor_Effect;
friend class CHpImage;
friend class CPowerPoly;
friend class CPowerMax;
friend class CGameRobot;
public:
	enum GUN_TYPE
	{
		GUN_NORMAL = 0,			// 通常
		GUN_REVOLVER,
		GUN_MACHINEGUNS,
		GUN_MAX
	};
public:
	CPlayer();
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数
	float Length( D3DXVECTOR3 *Vector );
	void Normalize( D3DXVECTOR3 *Vector, D3DXVECTOR3 *Vector1 );
	void SetMotion(MOTIONTYPE MotionType);
	void UpdateMotion( void );
private:
	D3DXVECTOR3 m_MouseaPos;
	D3DXVECTOR3 m_OldPos;
	D3DXVECTOR3 m_gunpoint;
	D3DXVECTOR3 m_errate;
	MOTIONTYPE m_MotionType;
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	KEY_INFO_REVOLVER *m_KeyInfo_Revolver;
	KEY_INFO_MACHINEGUN *m_KeyInfo_Machinegun;
	int m_NumKey;
	int m_Key;
	int m_Frame;
	MOTIONTYPE m_stopMotion;
	bool m_Numjia;
	CRevolverModel *m_RevolverModel[6];
	CModel *m_MachineModel[1];
	int m_frame;
	bool m_Repeating;
	int m_Power;
	GUN_TYPE m_type;
	int cnt;
	int m_HP;
	bool m_Dead;
	int m_time_Power;
	int m_Hp_Time;
};
#endif