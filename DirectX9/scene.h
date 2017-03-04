/********************************************************************************
* タイトル　01
* ファイル名　scene.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*************************************
// Matrixクラス
//*************************************
class CMatrix
{
public:
	D3DXMATRIX World;// ワールドマトリックス
	D3DXMATRIX Scl;
	D3DXMATRIX Rot;
	D3DXMATRIX Trans;
	D3DXMATRIX View;

	CMatrix()
	{
		D3DXMatrixIdentity(&World);
		D3DXMatrixIdentity(&Scl);
		D3DXMatrixIdentity(&Rot);
		D3DXMatrixIdentity(&Trans);
		D3DXMatrixIdentity(&View);
	}
};
class CScene 
{
//friend class CDebugProc;
	/*継承*/
protected:
	static CScene *m_Top;	//先頭		//静的メンバ変数
	static CScene *m_Cur;	//現在		//静的メンバ変数

	CScene *m_Prev;	//前のポインタ
	CScene *m_Next;	//次のポインタ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer ;	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture ;
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;        // スケール値
	float m_height;		//高さ
	float m_width;		//幅さ
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	CMatrix m_Matrix;
public:
	CScene();				// コンストラクタ
	~CScene();				// デストラクタ
	//仮想関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE) = 0;		// 初期化処理
	virtual void Uninit(void) = 0;		// 終了処理
	virtual void Draw(void) = 0;		//描画処理
	virtual void Update(void) = 0;		//更新処理
	static void UpdateAll(void);
	static void DrawAll(void);
	static void UninitAll(void);
	void Release(void);
	D3DXVECTOR3* Get3DPosition(void);
};
#endif	