/********************************************************************************
* タイトル　01
* ファイル名　CPowerMax.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
* Powerの画面描画
********************************************************************************/
#ifndef _CPOWERMAX_H_
#define _CPOWERMAX_H_

#define	TEXTURE_POWERMAX_FILE		"data\\TEXTURE\\PowerMax.png"	// 読み込むテクスチャファイル名

class CPowerMax : public CScene
{
public:
	CPowerMax();
	~CPowerMax();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CPowerMax* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

	bool m_bUse;
};
#endif
