///********************************************************************************
//* タイトル　01
//* ファイル名　CPoint.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
//* Point描画
//********************************************************************************/
#ifndef	_CPOINT_H_
#define	_CPOINT_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_POINT "data\\MODEL\\PROP\\POINT\\point.x"
class CPoint :public CScene
{
	friend class CBuildMenu;
	friend class CBuildMap;
	friend class CBuildLight;
	friend class CTrail;
	friend class CColumnar;
public:
	enum POINT_TYPE
	{
		POINT_NORMAL = 0,			// 通常
		POINT_BUILDING_TRUE,
		POINT_BUILDING_FALSE,
		POINT_MAX
	};
public:
	CPoint();
	~CPoint();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	POINT_TYPE m_type;
};
#endif