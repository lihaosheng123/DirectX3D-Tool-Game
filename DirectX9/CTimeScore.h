/********************************************************************************
* タイトル　01
* ファイル名　CTimeScore.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/21
* SCOREポリゴン描画-----------------------------------------------------------------------------------------------------------------------------------------------------
********************************************************************************/
#ifndef _CTIMESCORE_H_
#define _CTIMESCORE_H_
#define	MAX_TIMESCORE		(2)
#define	TEXTURE_TIMESCORE_FILE		"data\\TEXTURE\\timescore.png"	// 読み込むテクスチャファイル名

class CTimeScore : public CScene2D
{
friend class CTime;

friend class CNumber;
public:
	CTimeScore();
	~CTimeScore();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	void AddScore(int value);
	static CTimeScore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);//生成関数
private:
	int m_nScore;		//スコアの数
	float m_width_change;
	int nTimebg [2];
};
#endif