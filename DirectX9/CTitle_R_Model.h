///********************************************************************************
//* タイトル　01
//* ファイル名　CTitle_R_Model.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/02/10
//* R_Model描画
//********************************************************************************/
#ifndef	_CTITLE_R_MODEL_H_
#define	_CTITLE_R_MODEL_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_R "data\\MODEL\\title_r.x"
class CTitle_R_Model :public CScene
{
	friend class CTitleRobot;
public:
	CTitle_R_Model();
	~CTitle_R_Model();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitle_R_Model* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	int m_time;
	bool m_Rot;
	bool m_flag;
};
#endif
