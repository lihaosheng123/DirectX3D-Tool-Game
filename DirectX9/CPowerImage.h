/********************************************************************************
* タイトル　01
* ファイル名　CPowerImage.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
* Powerの画面描画
********************************************************************************/
#ifndef _CPOWERIMAGE_H_
#define _CPOWERIMAGE_H_

#define	TEXTURE_POWERIMAGE_FILE		"data\\TEXTURE\\PowerImage.png"	// 読み込むテクスチャファイル名

class CPowerImage : public CScene
{
	friend class CEnemy_Bullet_Down;
	friend class CEnemy_Bullet_Up;
	friend class CEnemy_Bullet_Left;
	friend class CEnemy_Bullet_Right;
public:
	CPowerImage();
	~CPowerImage();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CPowerImage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
};
#endif