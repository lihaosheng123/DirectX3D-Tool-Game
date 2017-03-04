///********************************************************************************
//* タイトル　01
//* ファイル名　CDoor.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Enemy_001描画
//********************************************************************************/
#ifndef	_CDOOR_H_
#define	_CDOOR_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_DOOR "data\\MODEL\\PROP\\DOOR\\door.x"
class CDoor :public CScene
{
	friend class CBuildMap;
public:
	enum DOOR_TYPE
	{
		DOOR_NORMAL = 0,			// 通常
		DOOR_BUILDING_FRONT,
		DOOR_BUILDING_BACK,
		DOOR_BUILDING_LEFT,
		DOOR_BUILDING_RIGHT,
		DOOR_BUILDING_FALSE,
		DOOR_MAX
	};
public:
	CDoor();
	~CDoor();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CDoor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	DOOR_TYPE m_type;
};
#endif