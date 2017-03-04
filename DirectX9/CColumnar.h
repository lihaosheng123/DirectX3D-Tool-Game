/********************************************************************************
* タイトル　01
* ファイル名　CColumnar.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/14
* skydome描画
********************************************************************************/
#ifndef	_CCOLUMNAR_H_
#define	_CCOLUMNAR_H_

class CColumnar :public CScene
{
	friend class CBuildMap;
	friend class CGamePoint;
	friend class CBullet;
	friend class CDebugProc;
public:
	CColumnar();
	~CColumnar();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CColumnar* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
	D3DXVECTOR3 m_scl;		//スケール値
	bool m_bUse;
	int m_Life;
	CMatrix m_Matrix;
	bool m_bMove;
	int Point_num;
};

#endif
