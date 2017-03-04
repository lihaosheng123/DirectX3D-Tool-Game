/********************************************************************************
* タイトル　01
* ファイル名　CField.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/06/20
* CField描画
********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "sceneX.h"
#include "CField.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define NULL_VETX		( 2 )							//  縮退ポリゴンの頂点数

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
float g_HeightMap[MESH_VTXH * MESH_VTXV];
//------------------------------------------------------------------------------
//	関数名:	CField::CField
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CField::CField()
{
	m_pTexture		= NULL;		//  テクスチャポリゴンへのポインタ
	m_pVtxBuffer		= NULL;		//  頂点バッファへのポインタ
	m_IdxBuff		= NULL;		//  インデックスバッファへのポインター
	m_nVtxNum		= 0;		//  マップエディタの選択した頂点番号
	for(int i = 0; i< (MESH_VTXH * MESH_VTXV);i++)
	{
		m_billboardNum[i] = NULL;
	}
	m_scl.x = 1.0f;
	m_scl.y = 1.0f;
	m_scl.z = 1.0f;
	m_Cut = false;
}

//------------------------------------------------------------------------------
//	関数名:	CField::~CField
//	引数:	なし
//	戻り値:	
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CField::~CField()
{
}

//------------------------------------------------------------------------------
//	関数名:	CField *CField::Create
//	引数:	D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE
//	戻り値:	meshField
//	説明:	フィールドの生成
//------------------------------------------------------------------------------
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{

	CField *meshField;//  メッシュクラス格納ワーク
	//インスタンス(instance)生成
	meshField = new CField;
	
	//  メッシュフィールドの初期化
	meshField->Init(pos, rot,height ,width,TEXTURE_FILE);

	return meshField;
}

//------------------------------------------------------------------------------
//	関数名:	void CField::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
HRESULT CField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float height ,float width,LPCSTR TEXTURE_FILE)
{

	//  デバイスのゲッター

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CSceneInput *m_Input = manager -> GetInput();

	CRenderer *renderer = manager -> GetRenderer();

	CEffect *m_Effect = game ->GetEffect();
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	int nVtx;		//  総頂点数を格納ワーク
	int nIdx;		//  インデックス数を格納ワーク
	int nMidVtxV;		//  上下頂点以外の縦中央頂点数を格納ワーク
	int nPrimitive;		//  プリミティブ数を格納ワーク
	int vtxH = MESH_VTXH;
	int vtxV = MESH_VTXV;
	nVtx		= vtxH * vtxV;	//  総頂点数を格納ワーク
	nMidVtxV	= vtxV - 2;										//  上下頂点以外の縦頂点数を格納ワーク
	nIdx	= nVtx + nMidVtxV * ( vtxH + NULL_VETX );		//  インデックス数を格納ワーク
	nPrimitive	= nIdx - 2;										//  プリミティブ数を格納ワーク

	m_VtxPos = new D3DXVECTOR3[vtxH * vtxV];		//  頂点座標を格納ワーク
	m_Nor	= new D3DXVECTOR3[vtxH * vtxV];					//  法線を格納ワーク
	m_NorType	= new NORMAL_TYPE[vtxH * vtxV];					//  法線タイプを格納ワーク
	m_nBlockVtxNo	= new int[(vtxH - 1) * (vtxV - 1)];				//  ブロック左上頂点を格納ワーク

	//  メッシュ情報の初期化
	m_Mesh.nVtxH		= vtxH;			//  横の頂点数
	m_Mesh.nVtxV		= vtxV;			//  縦の頂点数
	m_Mesh.nVtx			= nVtx;		//　総頂点数
	m_Mesh.nBlockH		= vtxH - 1;			//　横のブロック数
	m_Mesh.nBlockV		= vtxV - 1;		//　縦のブロック数
	m_Mesh.nBlock		= (vtxH - 1) * (vtxV - 1);		//　総頂点数
	m_Mesh.nIdx			= nIdx;			//  インデックス数
	m_Mesh.nPrimitive	= nPrimitive;		//  プリミティブ数

	//  頂点座標計算関係の初期化
	m_nHalfVtxV			= vtxV / 2;	//  縦の頂点数の半分
	m_fTexAdjust		= 0.0f;			//  テクスチャY座標ずらす係数
	m_nIdxEven			= 0;		//  インデックスバッファ頂点が偶数の数(退化三角形頂点以外)
	m_nNullVtx			= 0;		//  縮退ポリゴン頂点の数
	m_nMultiple			= 2;		//  インデックスバッファ用係数
	
	//  位置、回転、拡大縮小、幅、高さ、法線の更新チェックの初期化
	m_Position	= pos;		//  位置
	m_Rotation	= rot;		//  回転
	m_width	= width;		//  幅
	m_height	= height;		//  高さ
	m_bUseNor	= true;		//  法線の更新が必要かどうか
	m_Moveuse = true;
	target_rand = 0;

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile
	(device,
		TEXTURE_FILE,																//  テクスチャファイル位置
		&m_pTexture														//  テクスチャバッファへのポインタ
	);

	for (int nCnt = 0; nCnt < m_Mesh.nVtx; nCnt++)
	{
		m_NorType[nCnt]	= NONE;		//  法線タイプの初期化
	}

	//乱数
	srand((unsigned) time(NULL));
	target_rand = rand()%(m_Mesh.nVtx)+0;
	for(int i = 0;i <(MESH_VTXH * MESH_VTXV);i++)
	{
		m_billboardNum[i] = (rand()%4+0);
	//	g_HeightMap[i] =(float)(rand()%10+0);

	}

	//  頂点情報の作成
	MakeVertex();

	//  法線情報の作成
	MakeNormal();

	//  ブロック頂点番号情報の作成
	MakeBlockVtx();

	//  頂点の設定
	SetVertex(device);

	//  インデックス情報の作成
	MakeIndex(device);



	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CField::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CField::Uninit(void)
{
	//  テクスチャバッファの開放
	RELEASE(m_pTexture);

	//  頂点バッファの開放
	RELEASE(m_pVtxBuffer);

	//  インデックスバッファを開放
	RELEASE(m_IdxBuff);
}

//------------------------------------------------------------------------------
//	関数名:	void CField::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CField::Update(void)
{

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager:: GetMode();
	CCamera *m_Camera = game->GetCCamera();
	CSceneInput *m_Input = manager -> GetInput();

	CRenderer *renderer = manager -> GetRenderer();

	CScore *m_Score = game ->GetScore();

	CEffect *m_Effect = game ->GetEffect();

	CSceneMouse *m_Mouse = manager -> GetMouse();

	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();

	if (m_nVtxNum < 0)
	{
		m_nVtxNum = 0;
	}
	else if (m_nVtxNum>m_Mesh.nVtx - 1)
	{
		m_nVtxNum = m_Mesh.nVtx - 1;
	}

	 // フィールド頂点Ｙ座標の調整
	//if (m_Input->GetKeyboardPress(DIK_O))
	//{
	//	m_VtxPos[m_nVtxNum].y += 0.5f;
	//	m_bUseNor = true;
	//}
	//else if (m_Input->GetKeyboardPress(DIK_P))
	//{
	//	m_VtxPos[m_nVtxNum].y -= 0.5f;
	//	m_bUseNor = true;
	//}

	if (m_bUseNor == true)
	{//  法線を更新する場合
		//  法線情報の作成
		MakeNormal();

		//  頂点バッファ情報作成
		SetVertex(device);

		m_bUseNor = false;
	}

}

//------------------------------------------------------------------------------
//	関数名:	void CField::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理`
//------------------------------------------------------------------------------
void CField::Draw(void)
{
	//  デバイスのゲッター
	CManager *manager = GetManager();

	CSceneInput *m_Input = manager -> GetInput();

	CRenderer *renderer = manager -> GetRenderer();



	LPDIRECT3DDEVICE9 device = renderer -> GetDevice();
	//  ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Matrix.World);

	//  スケールを反映
	D3DXMatrixScaling(
		&m_Matrix.Scl,
		m_scl.x,
		m_scl.y,
		m_scl.z
	);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Scl
	);

	//  回転を反映
	D3DXMatrixRotationYawPitchRoll(
		&m_Matrix.Rot,
		m_Rotation.y,
		m_Rotation.x,
		m_Rotation.z
	);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Rot
	);

	//  位置を反映
	D3DXMatrixTranslation(
		&m_Matrix.Trans,
		m_Position.x,
		m_Position.y,
		m_Position.z
	);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Trans
	);

	//  ワールドマトリックスを設定
	device->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  頂点バッファをデータストリームにバインドする
	device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//  インデックスバッファをデータストリームにバインドする
	device->SetIndices(m_IdxBuff);

	//  頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// レンダーステートの設定（zテスト）
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//z値の更新

//	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//  テクスチャの設定
	device->SetTexture(0, m_pTexture);
	//device->SetRenderState( D3DRS_LIGHTING, FALSE );

	// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
	device->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));			//sizeof( VERTEX_2D )はデータの間隔
	// ブレンド加算処理
	//device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定

	//  描画
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.nVtx,		//  総頂点数
		0,
		m_Mesh.nPrimitive	//  プリミティブ数
	);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// デフォルトに戻す。
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);			// デフォルトに戻す。
																	// ライト点灯
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CField::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
void CField::MakeVertex(void)
{
	//  フィールド中心を原点座標にする処理
	if (m_Mesh.nVtxH % 2 == 0)
	{//  頂点数が偶数なら
		m_fXAdjust = 0.5f;		//  中心座標を調整の係数が0.5を設定
	}
	else
	{//  頂点数が奇数なら
		m_fXAdjust = 0.0f;		//  中心座標を調整の係数が0.0を設定
	}

	//  フィールド中心を原点座標にする処理
	if (m_Mesh.nVtxV % 2 == 0)
	{//  頂点数が偶数なら
		m_fZAdjust = 0.5f;		//  中心座標を調整の係数が0.5を設定
	}
	else
	{//  頂点数が奇数なら
		m_fZAdjust = 0.0f;		//  中心座標を調整の係数が0.0を設定
	}

	for (int nCntMeshFieldVtx = 0; nCntMeshFieldVtx < m_Mesh.nVtx; nCntMeshFieldVtx++)
	{//  フィールドの座標計算
		int nCntFieldSur = nCntMeshFieldVtx % m_Mesh.nVtxH;

		//  頂点座標の保存
		m_VtxPos[nCntMeshFieldVtx].x = (nCntFieldSur - m_Mesh.nVtxH / 2 + m_fXAdjust) * m_width;
		m_VtxPos[nCntMeshFieldVtx].y = 0.0f;
		for(int i = 0;i<(MESH_VTXH * MESH_VTXV);i++)
		{
		m_VtxPos[i].y = g_HeightMap[i];
		}
		m_VtxPos[nCntMeshFieldVtx].z = (m_nHalfVtxV - m_fZAdjust) * m_height;

		if (nCntFieldSur == m_Mesh.nVtxH - 1)
		{//  今は毎行最後の頂点の場合
			m_nHalfVtxV--;			//  次の行へ
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CField::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	インデックス情報の作成
//------------------------------------------------------------------------------
HRESULT CField::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	//インデックスバッファを確保
	if (FAILED(pDevice->CreateIndexBuffer
		(
		sizeof(WORD) * m_Mesh.nIdx,		//  インデックスデータ用に確保するバッファサイズ(ワード単位)
		D3DUSAGE_WRITEONLY,					//  インデックスバッファの使用法
		D3DFMT_INDEX16,						//  使用するインデックスフォーマット
		D3DPOOL_MANAGED,					//  リソースのバッファを保持するメモリクラスを指定
		&m_IdxBuff,						//  インデックスバッファインターフェースへのポインタ
		NULL								//  NULLに設定
		)))
	{
		return E_FAIL;
	}

	//  インデックスバッファの中身を埋める
	WORD *pIdx;

	//  インデックスデータの範囲をロックし、インデックスバッファへのポインタを取得
	m_IdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdx = 0; nCntIdx < m_Mesh.nIdx; nCntIdx++)
	{//  頂点番号を取得(N型描画用)
		if (nCntIdx == m_Mesh.nVtxH * m_nMultiple + m_nNullVtx)
		{//  縮退ポリゴン頂点番号を設定(毎行2個)
			if (nCntIdx % 2 == 0)
			{//  1個目
				pIdx[nCntIdx] = pIdx[nCntIdx - 1];
				m_nNullVtx++;		//  縮退ポリゴン頂点数が1を加算する
			}
			else
			{//  2個目
				pIdx[nCntIdx] = m_Mesh.nVtxH + m_nIdxEven;
				m_nMultiple += 2;	//  次の行の縮退ポリゴン頂点番号の計算用係数を設定
				m_nNullVtx++;		//  縮退ポリゴン頂点数が1を加算する
			}
		}

		else if (nCntIdx % 2 == 0)
		{//  頂点番号が偶数なら
			pIdx[nCntIdx] = m_Mesh.nVtxH + m_nIdxEven;
			m_nIdxEven++;
		}

		else
		{//  頂点番号が奇数なら
			pIdx[nCntIdx] = nCntIdx - m_nIdxEven - m_nNullVtx;
		}
	}

	//  インデックスデータをアンロックする
	m_IdxBuff->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CField::MakeNormal
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	法線情報の作成
//------------------------------------------------------------------------------
void CField::MakeNormal(void)
{
	D3DXVECTOR3	Vector[6], Normal[6];
	int nNumLeftTop, nNumRightTop, nNumLeftDown, nNumRightDown;

	nNumLeftTop		= 0;
	nNumRightTop	= m_Mesh.nVtxH - 1;
	nNumLeftDown	= m_Mesh.nVtx - m_Mesh.nVtxH;
	nNumRightDown	= m_Mesh.nVtx - 1;

	m_NorType[nNumLeftTop]		= LEFT_TOP;
	m_NorType[nNumRightTop]	= RIGHT_TOP;
	m_NorType[nNumLeftDown]	= LEFT_DOWN;
	m_NorType[nNumRightDown]	= RIGHT_DOWN;

	if (m_Mesh.nVtxH > 2)
	{//  横頂点数２以上の場合
		//  法線タイプを上辺タイプに設定
		for (int nCnt = 1; nCnt < nNumRightTop; nCnt++)
		{
			m_NorType[nCnt] = TOP_SIDE;
		}

		//  法線タイプを下辺タイプに設定
		for (int nCnt = nNumLeftDown + 1; nCnt < nNumRightDown; nCnt++)
		{
			m_NorType[nCnt] = DOWN_SIDE;
		}
		
		if (m_Mesh.nVtxV > 2)
		{//  横と縦頂点数２以上の場合
			//  法線タイプ未設定のを中央タイプに設定
			for (int nCnt = 0; nCnt < m_Mesh.nVtx; nCnt++)
			{
				if (m_NorType[nCnt] == NONE)
				{
					m_NorType[nCnt] = MIDDLE;
				}
			}
		}
	}

	if (m_Mesh.nVtxV > 2)
	{//  縦頂点数２以上の場合
		//  法線タイプを左辺タイプに設定
		for (int nCnt = m_Mesh.nVtxH; nCnt < nNumLeftDown; nCnt += m_Mesh.nVtxH)
		{
			m_NorType[nCnt] = LEFT_SIDE;
		}

		//  法線タイプを右辺タイプに設定
		for (int nCnt = m_Mesh.nVtxH * 2 - 1; nCnt < nNumRightDown; nCnt += m_Mesh.nVtxH)
		{
			m_NorType[nCnt] = RIGHT_SIDE;
		}
	}

	//  法線を求める
	for (int nCnt = 0; nCnt < m_Mesh.nVtx; nCnt++)
	{
		switch (m_NorType[nCnt])
		{
		case LEFT_TOP:
			Vector[0] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt + m_Mesh.nVtxH + 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];

			//  ２面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1]));
			break;

		case RIGHT_TOP:
			Vector[0] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];

			//  １面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &Normal[0]);
			break;

		case LEFT_DOWN:
			Vector[0] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];

			//  １面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &Normal[0]);
			break;

		case RIGHT_DOWN:
			Vector[0] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt - m_Mesh.nVtxH - 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];

			//  ２面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1]));
			break;

		case TOP_SIDE:
			Vector[0] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt + m_Mesh.nVtxH + 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[3] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1] + Normal[2]));
			break;

		case DOWN_SIDE:
			Vector[0] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt - m_Mesh.nVtxH - 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[3] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case LEFT_SIDE:
			Vector[0] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt + m_Mesh.nVtxH + 1] - m_VtxPos[nCnt];
			Vector[3] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case RIGHT_SIDE:
			Vector[0] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt - m_Mesh.nVtxH - 1] - m_VtxPos[nCnt];
			Vector[3] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[nCnt], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case MIDDLE:
			Vector[0] = m_VtxPos[nCnt - m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[1] = m_VtxPos[nCnt + 1] - m_VtxPos[nCnt];
			Vector[2] = m_VtxPos[nCnt + m_Mesh.nVtxH + 1] - m_VtxPos[nCnt];
			Vector[3] = m_VtxPos[nCnt + m_Mesh.nVtxH] - m_VtxPos[nCnt];
			Vector[4] = m_VtxPos[nCnt - 1] - m_VtxPos[nCnt];
			Vector[5] = m_VtxPos[nCnt - m_Mesh.nVtxH - 1] - m_VtxPos[nCnt];

			//  ６面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);
			D3DXVec3Cross(&Normal[3], &Vector[3], &Vector[4]);
			D3DXVec3Cross(&Normal[4], &Vector[4], &Vector[5]);
			D3DXVec3Cross(&Normal[5], &Vector[5], &Vector[0]);

			//  法線を求める
			D3DXVec3Normalize(
				&m_Nor[nCnt],
				&(Normal[0] + Normal[1] + Normal[2] + Normal[3] + Normal[4] + Normal[5])
			);
			break;
		default:
			break;
		}

		//  正規化
		D3DXVec3Normalize(&m_Nor[nCnt], &m_Nor[nCnt]);
	}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CField::SetVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点情報の作成
//------------------------------------------------------------------------------
HRESULT CField::SetVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファを確保
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_Mesh.nVtx,		//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						//  頂点バッファの使用法　
		FVF_VERTEX_3D,							//  使用する頂点フォーマット
		D3DPOOL_MANAGED,						//  リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuffer,							//  頂点バッファインターフェースへのポインタ
		NULL									//  NULLに設定
		)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshFieldVtx = 0; nCntMeshFieldVtx < m_Mesh.nVtx; nCntMeshFieldVtx++)
	{
		int nCntFieldSur = nCntMeshFieldVtx % m_Mesh.nVtxH;
		//  頂点座標の設定
		pVtx[nCntMeshFieldVtx].pos = m_VtxPos[nCntMeshFieldVtx];

		//  法線の設定
		pVtx[nCntMeshFieldVtx].nor = m_Nor[nCntMeshFieldVtx];

		//  頂点カラーの設定
		pVtx[nCntMeshFieldVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//  テクスチャ座標の設定
		pVtx[nCntMeshFieldVtx].tex = D3DXVECTOR2((float)nCntFieldSur, m_fTexAdjust);

		if (nCntFieldSur == m_Mesh.nVtxH - 1)
		{//  今は毎行最後の頂点の場合
			m_fTexAdjust++;		//  テクスチャY座標を設定
		}
	}

	//  頂点データをアンロックする
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CField::MakeBlockVtx
//	引数:	なし
//	戻り値:	なし
//	説明:	ブロック頂点情報の作成
//------------------------------------------------------------------------------
void CField::MakeBlockVtx(void)
{
	//  ブロック頂点計算補正用係数
	int nAdjust = 0;

	for (int nCnt = 0; nCnt < m_Mesh.nBlock; nCnt++)
	{
		switch (m_Mesh.nBlockH)
		{
		case 1://  横ブロック１の場合
			m_nBlockVtxNo[nCnt] = nCnt + nAdjust;
			nAdjust++;
			break;
		default://  他の場合
			if (nCnt != 0 && nCnt % m_Mesh.nBlockH == 0)
			{
				nAdjust++;
			}
			m_nBlockVtxNo[nCnt] = nCnt + nAdjust;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CField::CheckBlock
//	引数:	D3DXVECTOR3 pos
//	戻り値:	なし
//	説明:	対象のいるブロックのチェック
//?????????????
//------------------------------------------------------------------------------
//int CField::CheckBlock(D3DXVECTOR3 pos)
//{	
//
//	//  現在対象のいるブロック = フィールド中心ブロック + 対象の座標 / フィールドの長さ
//	fBlockH = m_Mesh.nBlockH * 0.5f + pos.x / MESH_VTXH;
//	fBlockV = m_Mesh.nBlockV * 0.5f - pos.z / MESH_VTXV;
//
//	nBlockH = (int)fBlockH;
//	nBlockV = (int)fBlockV;
//
//	//  プレイヤー移動したブロック数をint型に変換する（０から１未満の場合、足す１）
//	if (fmod(fBlockH, 1.0f) > 0)
//	{
//		nBlockH++;
//	}
//	else if (fmod(fBlockH, 1.0f) < 0)
//	{
//		nBlockH--;
//	}
//
//	if (fmod(fBlockV, 1.0f) > 0)
//	{
//		nBlockV++;
//	}
//	else if (fmod(fBlockV, 1.0f) < 0)
//	{
//		nBlockV--;
//	}
//
//	//  対象のいるブロックを計算
//	nInBlockNum = (nBlockV - 1) * m_Mesh.nBlockH + nBlockH - 1;
//
//	return nInBlockNum;
//}

//------------------------------------------------------------------------------
//	関数名:	float CField::GetHeight
//	引数:	D3DXVECTOR3 pos, bool bMove
//	戻り値:	なし
//	説明:	対象とプリミティブの交差点を求める（高さ）
//			bMoveがtrueだと、実行する
//?????????
//------------------------------------------------------------------------------
float CField::GetHeight(D3DXVECTOR3 pos, bool bMove)
{
	D3DXVECTOR3	VectorVtx[6], VectorObject[6], VectorResult[6];
	D3DXVECTOR3	Vector[4], Normal[2];
	int			nNum[4];
	//int			nInBlockNum;
	float		fHeight;

	//  プレイヤーのいるブロックチェック	
//m_nGunInBlockNum = nInBlockNum = CheckBlock(pos);


	for(int i = 0;i<(m_Mesh.nVtx-(m_Mesh.nVtxH+1));i++ )
	{
	//  ブロック頂点番号を格納する
	nNum[0] = i;
	nNum[1] = nNum[0] + 1;
	nNum[2] = nNum[0] + m_Mesh.nVtxH;
	nNum[3] = nNum[0] + m_Mesh.nVtxH + 1;

	//nNum[0] = m_nBlockVtxNo[nInBlockNum];
	//nNum[1] = nNum[0] + 1;
	//nNum[2] = nNum[0] + m_Mesh.nVtxH;
	//nNum[3] = nNum[0] + m_Mesh.nVtxH + 1;
	//  プリミティブのベクトルを計算
	VectorVtx[0] = m_VtxPos[nNum[0]] - m_VtxPos[nNum[2]];
	VectorVtx[1] = m_VtxPos[nNum[3]] - m_VtxPos[nNum[0]];
	VectorVtx[2] = m_VtxPos[nNum[2]] - m_VtxPos[nNum[3]];

	VectorVtx[3] = m_VtxPos[nNum[1]] - m_VtxPos[nNum[0]];
	VectorVtx[4] = m_VtxPos[nNum[3]] - m_VtxPos[nNum[1]];
	VectorVtx[5] = m_VtxPos[nNum[0]] - m_VtxPos[nNum[3]];

	//  対象のベクトルを計算
	VectorObject[0] = pos - m_VtxPos[nNum[2]];
	VectorObject[1] = pos - m_VtxPos[nNum[0]];
	VectorObject[2] = pos - m_VtxPos[nNum[3]];

	VectorObject[3] = pos - m_VtxPos[nNum[0]];
	VectorObject[4] = pos - m_VtxPos[nNum[1]];
	VectorObject[5] = pos - m_VtxPos[nNum[3]];

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		//  ベクトルＹ座標を０に設定
		VectorVtx[nCnt].y=
		VectorObject[nCnt].y= 0.0f;

		//  対象がプリミティブ各辺の左右どちらかにいるの計算（外積）
		D3DXVec3Cross(&VectorResult[nCnt], &VectorObject[nCnt], &VectorVtx[nCnt]);
	}

	//  左右プリミティブ２辺のベクトルを計算
	Vector[0] = m_VtxPos[nNum[0]] - m_VtxPos[nNum[2]];
	Vector[1] = m_VtxPos[nNum[3]] - m_VtxPos[nNum[2]];
	Vector[2] = m_VtxPos[nNum[3]] - m_VtxPos[nNum[1]];
	Vector[3] = m_VtxPos[nNum[0]] - m_VtxPos[nNum[1]];

	//  プリミティブ法線を求める(時計回り)
	D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
	D3DXVec3Cross(&Normal[1], &Vector[2], &Vector[3]);

	//  プリミティブ法線の正規化
	D3DXVec3Normalize(&Normal[0], &Normal[0]);
	D3DXVec3Normalize(&Normal[1], &Normal[1]);

	//  左右プリミティブどちらにいるチェック
	if (VectorResult[0].y <= 0)
	{//  左プリミティブにいる場合
		if (VectorResult[1].y <= 0)
		{
			if (VectorResult[2].y <= 0)
			{
				//  高さを求める
				fHeight = m_VtxPos[nNum[2]].y - ((Normal[0].x * (pos.x - m_VtxPos[nNum[2]].x)) + Normal[0].z * (pos.z - m_VtxPos[nNum[2]].z)) / Normal[0].y;
			}
		}
	}

	if (VectorResult[3].y <= 0)
	{//  右プリミティブにいる場合
		if (VectorResult[4].y <= 0)
		{
			if (VectorResult[5].y <= 0)
			{
				//  高さを求める
				fHeight = m_VtxPos[nNum[1]].y - ((Normal[1].x * (pos.x - m_VtxPos[nNum[1]].x)) + Normal[1].z * (pos.z - m_VtxPos[nNum[1]].z)) / Normal[1].y;
			}
		}
	}
	}
	
	return fHeight;
}

//------------------------------------------------------------------------------
//	関数名:	D3DXVECTOR3	*CField::GetNormal
//	引数:	なし
//	戻り値:	m_Nor
//	説明:	法線情報を取得
//------------------------------------------------------------------------------
D3DXVECTOR3	*CField::GetNormal(void)
{
	return m_Nor;
}

//------------------------------------------------------------------------------
//	関数名:	int *CField::GetGunInBlock
//	引数:	なし
//	戻り値:	m_nGunInBlockNo
//	説明:	プレイヤーのいるブロックを取得
//------------------------------------------------------------------------------
int *CField::GetGunInBlock(void)
{
	return &m_nGunInBlockNum;
}