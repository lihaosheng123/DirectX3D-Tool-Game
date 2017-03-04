/********************************************************************************
* タイトル　01
* ファイル名　CTalkRobotImage.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/07/11
* 会話
********************************************************************************/
#ifndef _CTALKROBOTIMAGE_H_
#define _CTALKROBOTIMAGE_H_

#define	TEXTURE_TALKROBOTIMAGE_FILE		"data\\TEXTURE\\talk.png"	// 読み込むテクスチャファイル名

class CTalkRobotImage : public CScene
{
public:
	CTalkRobotImage();
	~CTalkRobotImage();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CTalkRobotImage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
	bool m_bUse;
};
#endif