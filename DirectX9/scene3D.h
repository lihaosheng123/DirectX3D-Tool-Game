/********************************************************************************
* タイトル　01
* ファイル名　scene3D.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
* 3Dポリゴン描画
********************************************************************************/
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//  マトリックス構造体
typedef struct
{
	D3DXMATRIX	World;			//ワールドマトリックス
	D3DXMATRIX	Scl;			//スケールマトリックス
	D3DXMATRIX	Rot;			//回転マトリックス
	D3DXMATRIX	Trans;			//位置マトリックス
}MATRIX;

//  メッシュフィールドクラス
class CScene3D : public CScene
{
protected:
	MATRIX	m_Matrix;			//  マトリクス情報
	D3DXVECTOR3		m_scl;				//  拡大縮小
public:
	CScene3D();
	~CScene3D();
	void		Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float fWidth, float fHeight, int vtxH, int vtxV, LPCSTR TEXTURE_FILE);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);
};

#endif