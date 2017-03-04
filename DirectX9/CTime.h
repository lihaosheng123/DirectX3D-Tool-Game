//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/07/11
// CTime.h
//* Fox描画
//********************************************************************************/
#ifndef	_CTIME_H_
#define	_CTIME_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義

class CTime
{
friend class CTimeScore;
public:
	CTime();
	~CTime();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
private:
	int m_time;
	int m_frame;
};
#endif
