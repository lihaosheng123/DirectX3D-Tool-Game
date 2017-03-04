/********************************************************************************
* タイトル　01
* ファイル名　CField.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/20
* field描画
********************************************************************************/
#ifndef _CFIELD_H_
#define _CFIELD_H_
//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------

class CScene3D;
//------------------------------------------------------------------------------
//	マクロ定義	
//------------------------------------------------------------------------------
#define MESHFIELD_TEXTURE_FILE00	"./data/TEXTURE/field.jpg"	//地面テクスチャファイル位置

#define MESH_VTXH		(100)		//幅
#define MESH_VTXV		(100)		//長さ


//  シーンタイプ
typedef enum
{
	NONE = 0,
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_DOWN,
	RIGHT_DOWN,
	TOP_SIDE,
	DOWN_SIDE,
	LEFT_SIDE,
	RIGHT_SIDE,
	MIDDLE
}NORMAL_TYPE;

//  メッシュ構造体
typedef struct
{
	int			nVtxV;			//  横の頂点数
	int			nVtxH;			//  縦の頂点数
	int			nVtx;			//  総頂点数
	int			nIdx;			//  インデックス数
	int			nPrimitive;	//  ポリゴン数
	int			nBlockV;
	int			nBlockH;
	int			nBlock;			//  ブロック数
}MESH;

//  メッシュフィールドクラス
class CField : public CScene3D
{
friend class CDebugProc;
friend class CBall;
friend class CGun;
friend class CManager;
friend class CEffect;
friend class  CSceneMouse;
private:
	MESH	m_Mesh;				//  メッシュ情報
	LPDIRECT3DINDEXBUFFER9	m_IdxBuff;				//  インデックスバッファへのポインター
	int	m_nHalfVtxV;			//  縦の頂点数の半分
	int	m_nIdxEven;			//  インデックスバッファ頂点が偶数の数(退化三角形頂点以外)
	int	m_nNullVtx;			//  縮退ポリゴン頂点数
	int	m_nMultiple;			//  インデックスバッファ用係数
	float	m_fXAdjust;			//  Z座標位置を補正
	float	m_fZAdjust;			//  Z座標位置を補正
	float	m_fTexAdjust;			//  テクスチャY座標位置を補正
	
	D3DXVECTOR3	*m_VtxPos;				//  頂点座標
	NORMAL_TYPE	*m_NorType;			//  法線のタイプ
	D3DXVECTOR3	*m_Nor;					//  法線
	int	m_nVtxNum;				//	頂点番号
	bool	m_bUseNor;				//  法線の更新が必要かどうか

	int	*m_nBlockVtxNo;		//  ブロック頂点番号
	int	m_nGunInBlockNum;	//  プレイヤーのいるブロック番号

	int		nBlockH;		//  横ブロック頂点番号を格納ワーク
	int		nBlockV;		//  縦ブロック頂点番号を格納ワーク
	float	fBlockH;		//  横ブロック頂点番号を格納ワーク（float型）
	float	fBlockV;		//  縦ブロック頂点番号を格納ワーク（float型）
	int		nInBlockNum;	//  対象のいるブロック番号

	int m_billboardNum[MESH_VTXH * MESH_VTXV];
	int target_rand;

	bool m_Moveuse;
	bool m_Cut;
public:
	CField();
	~CField();
	HRESULT		Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);
	void		MakeVertex(void);
	void		MakeNormal(void);
	void		MakeBlockVtx(void);
	HRESULT		MakeIndex(LPDIRECT3DDEVICE9 pDevice);
	HRESULT		SetVertex(LPDIRECT3DDEVICE9 pDevice);
	D3DXVECTOR3	*GetNormal(void);
	int			*GetGunInBlock(void);
	int			CheckBlock(D3DXVECTOR3 pos);
	float		GetHeight(D3DXVECTOR3 pos, bool bMove);
	static CField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE);
};

#endif