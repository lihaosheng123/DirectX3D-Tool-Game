///********************************************************************************
//* タイトル　01
//* ファイル名　CTitleModel.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/02/10
//* TitleModel描画
//********************************************************************************/
#ifndef	_CTITLEENEMY_H_
#define	_CTITLEENEMY_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_TITLE "data\\MODEL\\title.x"
class CTitleModel :public CScene
{

public:
	CTitleModel();
	~CTitleModel();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTitleModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
};
#endif
