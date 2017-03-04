///********************************************************************************
//* タイトル　01
//* ファイル名　cylinder.h
//* 作成者 AT13B284 42 李昊盛
//* 作成日 2016/11/15
//* テスト用ステンシルシャドウ描画
//********************************************************************************/
#ifndef	_cylinder_H_
#define	_cylinder_H_

//*******************************************************************************
//* マクロ定義
//*******************************************************************************/
//マクロ定義
#define MODEL_CYLINDER_TEXTURE "data\\MODEL\\cylinder.x"
class cylinder : public CSceneX
{
public:
	cylinder();
	~cylinder();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理
	static cylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float height, float width, LPCSTR TEXTURE_FILE);//生成関数
private:
};
#endif
