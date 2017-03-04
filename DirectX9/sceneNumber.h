/********************************************************************************
* タイトル　01
* ファイル名　sceneNumber.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/15
* Number描画
********************************************************************************/
#ifndef _SCENENUMBER_H_
#define _SCENENUMBER_H_
#define	TEXTURE_NUM_FILE		"data\\TEXTURE\\test.png"	// 読み込むテクスチャファイル名

class CNumber : public CScene
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数
	CNumber* SetPotion(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);
protected:

};
#endif