/********************************************************************************
* タイトル　01
* ファイル名　CHpImage.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
* Hpの画面描画
********************************************************************************/
#ifndef _CHPIMAGE_H_
#define _CHPIMAGE_H_

#define	TEXTURE_HPIMAGE_FILE		"data\\TEXTURE\\HpImage.png"	// 読み込むテクスチャファイル名

class CHpImage : public CScene
{
	friend class CEnemy_Bullet_Down;
	friend class CEnemy_Bullet_Up;
	friend class CEnemy_Bullet_Left;
	friend class CEnemy_Bullet_Right;
public:
	CHpImage();
	~CHpImage();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CHpImage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	int m_r;
	int m_b;
	bool m_Alpha;
};
#endif