//********************************************************************************
//* タイトル　01
//* ファイル名　Caxis.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/12
//*座標系描画
//********************************************************************************/
#ifndef	_CAXIS_H_
#define	_CAXIS_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#define	TEXTURE_AXIS_FILE		"data\\TEXTURE\\BUILD\\axis.png"	// 読み込むテクスチャファイル名

class Caxis :public CScene
{
public:
	Caxis();
	~Caxis();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static Caxis* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
private:

};
#endif