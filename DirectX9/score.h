/********************************************************************************
* タイトル　01
* ファイル名　score.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/21
* SCOREポリゴン描画
********************************************************************************/
#ifndef _SCORE_H_
#define _SCORE_H_
#define	MAX_SCORE		(2)
#define	TEXTURE_SCORE_FILE		"data\\TEXTURE\\score.png"	// 読み込むテクスチャファイル名


class CScore : public CScene2D
{
friend class CNumber;
friend class CPortal;
public:
	CScore();
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void AddScore(int value);
	static CScore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数

private:
	int m_nScore;		//スコアの数
	float m_width_change;
};
#endif