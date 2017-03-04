///********************************************************************************
//* タイトル　01
//* ファイル名　CEnd.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/06/16
//*End描画
//********************************************************************************/
#ifndef	_CEND_H_
#define	_CEND_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/

class CEnd :public CScene
{
	friend class CBullet;
	friend class CMap;
	friend class CDebugProc;
	friend class CBuildMap;
	friend class CLoadMap;
	friend class CBuildMenu;
public:
	enum END_TYPE
	{
		END_NORMAL = 0,			// 通常
		END_BUILDING_TRUE,
		END_BUILDING_FALSE,
		END_MAX
	};
public:
	CEnd();
	~CEnd();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CEnd* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);

private:

	D3DXVECTOR3 m_scl;		//スケール値
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_NumCheck;
	int m_Changge;
	bool m_use;
	END_TYPE m_type;

};
#endif