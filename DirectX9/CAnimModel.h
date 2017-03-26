#pragma once

/********************************************************************************
* タイトル　CAnimModel.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2017/03/18
* モデルのマンション管理
********************************************************************************/
#ifndef _CANIMMODEL_H_
#define _CANIMMODEL_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "scene.h"

//-----------------------------------------------------------------------------
// Name: struct D3DXFRAME_DERIVED
// Desc: DXDXFRAMEから継承
//-----------------------------------------------------------------------------
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};


//-----------------------------------------------------------------------------
// Name: struct D3DXMESHCONTAINER_DERIVED
// Desc: D3DXMESHCONTAINERから継承
//-----------------------------------------------------------------------------
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;            //テクスチャ
	LPD3DXMESH           pOrigMesh;              //メッシュの情報
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD                NumAttributeGroups;    // マテリアル数
	DWORD                NumInfl;               //每个顶点最多受多少骨骼的影响
	LPD3DXBUFFER         pBoneCombinationBuf;   //骨骼结合表
	D3DXMATRIX**         ppBoneMatrixPtrs;      //存放骨骼的组合マトリックス
	D3DXMATRIX*          pBoneOffsetMatrices;   //存放骨骼的初始マトリックス
	DWORD                NumPaletteEntries;     //骨骼数量上限
	bool                 UseSoftwareVP;         //标识是否使用软件顶点处理
};


//-----------------------------------------------------------------------------
// Name: class CAllocateHierarchy
// Desc: 来自微软官方DirectX SDK Samples中的骨骼动画类，这个类用来从.X文件加载框架层次和网格模型数据
// 核心点:      #define STDMETHOD(method) virtual HRESULT STDMETHODCALLTYPE method 
//-----------------------------------------------------------------------------
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR              Name,
	CONST D3DXMESHDATA*       pMeshData,
	CONST D3DXMATERIAL*       pMaterials,
	CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD                     NumMaterials,
	CONST DWORD *             pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);


};



class CAnimModel
{
public:
	CAnimModel();
	~CAnimModel();
	//-----------------------------------------------------------------------------
	// Desc: 来自微软官方DirectX SDK Samples中的骨骼动画全局函数
	//-----------------------------------------------------------------------------
	void Init(void);
	void DrawFrame(LPD3DXFRAME pFrame);
	void Draw(void);
	void DrawMeshContainer(IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void Update(void);
	void Uninit(void);
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	//頂点パッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_Position;	// 頂点座標
	D3DXVECTOR3 m_Rotation;	// 回転
	D3DXVECTOR3 m_scl;        // スケール値
	float m_height;		//高さ
	float m_width;		//幅さ
	LPD3DXBUFFER m_BuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH m_Mesh;                  // メッシュの情報
	DWORD m_nNumMat;                     // マテリアル数
	CMatrix m_Matrix;

	//四个和骨骼动画相关的全局变量  
	LPD3DXFRAME                 g_pFrameRoot = NULL;
	D3DXMATRIX*                 g_pBoneMatrices = NULL;
	CAllocateHierarchy*         g_pAllocateHier = NULL;
	LPD3DXANIMATIONCONTROLLER   g_pAnimController = NULL;
};
#endif 