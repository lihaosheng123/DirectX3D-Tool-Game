///********************************************************************************
//* タイトル　01
//* ファイル名　scenebillboard.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/04/28
//* billboard描画
//********************************************************************************/
#ifndef	_SCENEBILLBOARD_H_
#define	_SCENEBILLBOARD_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define MAX_BILLBOARD ( 1 )                     // BILLBOARDの数
#define	TEXTURE_BILLBOARD_FILE01		"data\\TEXTURE\\billboard01.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_BILLBOARD_FILE02		"data\\TEXTURE\\billboard02.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_BILLBOARD_FILE03		"data\\TEXTURE\\billboard03.png"	// 読み込むテクスチャファイル名
class CSceneBillboard :public CScene
{
public:
	CSceneBillboard();
	~CSceneBillboard();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CSceneBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数
private:
	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
};
#endif