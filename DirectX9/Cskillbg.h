/********************************************************************************
* タイトル　01
* ファイル名　Cskillbg.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
* TITLEの画面描画
********************************************************************************/
#ifndef _CSKILLBG_H_
#define _CSKILLBG_H_



class Cskillbg : public CScene
{
	friend class CUnique_skill;
	friend class CPlayer;
public:
	Cskillbg();
	~Cskillbg();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static Cskillbg* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数

private:

};
#endif