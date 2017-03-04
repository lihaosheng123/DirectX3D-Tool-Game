/********************************************************************************
* タイトル　01
* ファイル名　CHpScore.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/02/13
* ライフCHPSCOREポリゴン描画
********************************************************************************/
#ifndef _CHPSCORE_H_
#define _CHPSCORE_H_
#define	MAX_HPSCORE		(2)
#define	TEXTURE_HPSCORE_FILE		"data\\TEXTURE\\score.png"	// 読み込むテクスチャファイル名


class CHpScore :public CScene
{
	friend class CNumber;
	friend class CPortal;
	friend class CPlayer;
public:
	CHpScore();
	~CHpScore();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void AddScore(int value);
	static CHpScore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:
	int m_nScore;		//スコアの数
	float m_width_change;
};
#endif