/********************************************************************************
* タイトル　01
* ファイル名　scene.cpp
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/04/18
*
********************************************************************************/
#include "main.h"
#include <stdio.h> 
#include "renderer.h"

#include "scene.h"


//静的メンバ変数
CScene *CScene::m_Top = NULL;
CScene *CScene::m_Cur = NULL;
//=============================================================================
// 生成
//=============================================================================
CScene ::CScene (void)
{
	//リストに登録
	if(m_Top == NULL)
	{
		// 自分を代入
		m_Top = this;
		m_Cur = this;
		//使ってない状態NULL
		m_Prev = NULL;
		m_Next = NULL;
	}
	else
	{
		m_Cur->m_Next = this;
		m_Prev = m_Cur;
		m_Cur = this;
		m_Next = NULL;
	}
}

//=============================================================================
// 破棄
//=============================================================================
CScene ::~CScene (void)
{

}
//=============================================================================
// 全てのSceneの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	//リストに登録されている全てのオブジェクトのdrawを呼び出す
	CScene *scene = m_Top;
	CScene *save;
	while(scene!=NULL)
	{
		save = scene->m_Next;	//ポインタ保存
		scene->Update();
		scene = save;		//	ポインタ入れ替える
	}

}
//=============================================================================
// 全てのSceneの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *scene = m_Top;
	while(scene!=NULL)
	{
		scene->Draw();
		scene = scene->m_Next;
	}

}
//=============================================================================
// 全てのSceneの破棄処理
//=============================================================================
void CScene::UninitAll(void)
{
	CScene *scene = m_Top;
	CScene *next;
	while(scene!=NULL)
	{
		next = scene->m_Next;
		scene->Uninit();	
		delete scene;
		scene = next;
	}
	m_Top =NULL;
}
void CScene::Release(void)
{
	if( this == m_Top)
	{
		m_Top = m_Next;
	}
	else
	{
		m_Prev->m_Next = m_Next;
	}
	if(this == m_Cur)
	{
		m_Cur = m_Prev;
	}
	else
	{
		m_Next->m_Prev = m_Prev;
	}
	delete this;
}
D3DXVECTOR3* CScene::Get3DPosition(void)
{
	return &m_Position;
}
