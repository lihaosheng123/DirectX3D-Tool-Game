/********************************************************************************
* タイトル　01
* ファイル名　number.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/23
* NUMBER処理
********************************************************************************/
#ifndef _NUMBER_H_
#define _NUMBER_H_
#define	MAX_DIGIT		(5)

class CNumber
{
friend class CScore;
friend class CTimeScore;
friend class CHpScore;
public:
	CNumber();
	~CNumber();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
private:
	int m_Number [MAX_DIGIT];
};
#endif