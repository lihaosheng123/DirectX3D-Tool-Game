///********************************************************************************
//* タイトル　01
//* ファイル名　CGameRobot.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* GameRobot描画
//********************************************************************************/
#ifndef	_CGAMEROBOT_H_
#define	_CGAMEROBOT_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_GAMEROBOT "data\\MODEL\\robot.x"

class CGameRobot :public CScene
{
	friend class CBuildMenu;
	friend class CBuildMap;
	friend class CBuildLight;
	friend class CTrail;
	friend class CTextbubble;
public:
	CGameRobot();
	~CGameRobot();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CGameRobot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	float  Length(D3DXVECTOR3 *Vector);
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	bool m_bUse;
};
#endif
