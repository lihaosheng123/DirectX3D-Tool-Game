/********************************************************************************
* タイトル　01
* ファイル名　Mode.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
*
********************************************************************************/
#ifndef _MODE_H_
#define _MODE_H_

class CMode

{
	private:

	public:
		//純粹仮想関数
		virtual void Init(void) = 0;
		virtual void Uninit(void) = 0;
		virtual void Update(void) = 0;
		virtual void Draw(void) = 0;

};


#endif