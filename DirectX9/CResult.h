/********************************************************************************
* タイトル　RESULT
* ファイル名　CResult.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
*
********************************************************************************/
#ifndef _CRESULT_H_
#define _CRESULT_H_

//前方宣言
class CResultbg;
class CRenderer;
class CResult : public CMode
{

public:
	CResult();
	~CResult();
	virtual void Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Draw(void);		//描画処理
	virtual void Update(void);		//更新処理

private:
	CResultbg *m_Resultbg;
	CRenderer *m_Renderer;
};

#endif