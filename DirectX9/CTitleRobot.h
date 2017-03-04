///********************************************************************************
//* タイトル　01
//* ファイル名　CTitleRobot.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* TitleRobot描画
//********************************************************************************/
#ifndef	_CTITLEROBOT_H_
#define	_CTITLEROBOT_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_TITLE_MODEL "data\\MODEL\\ENEMY\\enemy_001.x"
#define ENEMY_MOVE 2.0f;
#define ENEMY_001_INERTIA_MOVE (0.025f)		//慣性調整係数
class CTitleRobot :public CScene
{

public:
	CTitleRobot();
	~CTitleRobot();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitleRobot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	bool m_bMove;
	bool m_flag;
	int m_wait;
	bool m_rot;
	bool m_Backrot;
	int m_Time;
	bool m_newMove;
};
#endif