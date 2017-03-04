/********************************************************************************
* タイトル　01
* ファイル名　CBuildImage.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
*天井板の隱す/表現の操作画像
********************************************************************************/
#ifndef _CBUILDIMAGE_H_
#define _CBUILDIMAGE_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
#define	TEXTURE_BUILDIMAGE_FILE		"data\\TEXTURE\\BUILD\\BuildImage.png"	// 読み込むテクスチャファイル名

class CBuildImage : public CScene
{
public:
	CBuildImage();
	~CBuildImage();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CBuildImage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

};
#endif