/********************************************************************************
* タイトル　01
* ファイル名　CModel.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/08/23
* ``Xポリゴン描画
********************************************************************************/
#ifndef _CMODEL_H_
#define _CMODEL_H_

//マクロ定義



class CModel 
{
friend class CPlayer;
friend class CEnemy;
friend class CDebugProc;
public:
	CModel();
	~CModel();
	HRESULT Init(LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static CModel* Create(LPCSTR TEXTURE_FILE);//生成関数
private:

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	CModel *m_Parent;
	D3DXVECTOR3 m_scl;        // スケール値
	D3DXMATRIX GetWorldMatrix(void);
	void SetParent( CModel *Parent );
	void SetPosition( D3DXVECTOR3 Position );
	void SetRotation( D3DXVECTOR3 Rotation );
	D3DXMATRIX parentMatrix;
	LPDIRECT3DTEXTURE9 m_pTexture;

};
#endif