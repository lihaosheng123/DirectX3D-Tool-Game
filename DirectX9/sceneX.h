/********************************************************************************
* タイトル　01
* ファイル名　sceneX.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/26
* Xポリゴン描画
********************************************************************************/
#ifndef _SCENEX_H_
#define _SCENEX_H_

//マクロ定義



class CSceneX : public CScene
{
friend class CDebugProc;
public:
	CSceneX();
	~CSceneX();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理

protected:
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 m_scl;        // スケール値
	D3DXVECTOR3 m_Max;        // 頂点座標の最大値
	D3DXVECTOR3 m_Min;        // 頂点座標の最小値
	D3DXVECTOR3 m_Size;       // MaxとMinの絶対値を足して２で割ったもの。また衝突判定で使うモデルの半径。x:幅 y:高さ z:奥行き。
	float m_Collisoin;        // 衝突判定で使う長さ。sizeのxとzで、大きかった方を衝突判定に使う。
	D3DXVECTOR3 m_Velocity;		//重力

};

#endif