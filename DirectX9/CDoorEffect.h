///********************************************************************************
//* タイトル　01
//* ファイル名　CDoorEffect.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2017/01/20
//*doorのeffect描画
//********************************************************************************/
#ifndef	_CDOOREFFECT_H_
#define	_CDOOREFFECT_H_
//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

#include "scene.h"

class CDoor_Effect :public CScene
{
	friend class CPlayer;
	friend class CDebugProc;
	friend class CExplosion;
	friend class CGameDoor;
public:
	CDoor_Effect();
	~CDoor_Effect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CDoor_Effect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);
private:
	D3DXVECTOR3 m_scl;		//スケール値
	bool m_bUse;
	int m_Life;

	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	float m_height;		//高さ
	float m_width;		//幅さ
	CMatrix m_Matrix;
	int alpha;
};
#endif