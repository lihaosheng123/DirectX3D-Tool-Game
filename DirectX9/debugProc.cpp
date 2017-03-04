#include "main.h"
#include <math.h>
#include "manager.h"
#include "renderer.h"

#include < stdio.h >
#include < varargs.h >
#include < stdarg.h >

#include "sceneInput.h"
#include "debugProc.h"

#include "Camera.h"
#include "scene.h"
#include "sceneX.h"

/******************************************************************************
	マクロ定義
******************************************************************************/

/******************************************************************************
	プロトタイプ宣言
******************************************************************************/

/*******************************************************************************
/* グローバル変数
********************************************************************************/

RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//=============================================================================
// コンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{
	m_DebugFont = NULL;		//フォントのポインタ

	for( int nCntFont = 0; nCntFont < FONT_MAX; nCntFont++ )
	{
		m_StrDebug[ nCntFont ] = 0;// デバックの文字列の最大数
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{

}

/******************************************************************************
== 関数名 ： HRESULT CDebugProc::Init (void)
== 戻り値 ： HRESULT型
== 引数   ： void
== 内容   ： デバッグ情報の初期化処理
******************************************************************************/
HRESULT CDebugProc::Init ( void )
{
	

	/* renderer.cppから変数の値を貰う */
	CManager *manager = GetManager();
	CRenderer *renderer = manager -> GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice();

	/* 設定 */
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	/* デバイスとフォント用のフォント オブジェクトを作成 */
	D3DXCreateFont(
					pDevice,
					24,
					10,
					0,
					0,
					FALSE,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",
					&m_DebugFont
					);

	memset(
			m_StrDebug,			// ターゲットへのポインター
			0,					// 設定する文字
			sizeof m_StrDebug	// 文字数
			);

	return S_OK;
}

/******************************************************************************
== 関数名 ： void CDebugProc::Draw ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： デバッグ情報の描画処理
******************************************************************************/
void CDebugProc::Draw ( void )
{	
	m_DebugFont -> DrawText(
						 NULL,				// デバイスコンテキストのハンドル
						 &m_StrDebug[ 0 ],	// 描画するテキスト
						 -1,				// テキストの長さ
						 &rect,			// テキストを描画する長方形領域
						 DT_LEFT,			// テキストを左揃えにします
						 DEBUG_COLOR		// 色、背景色で描画
						 );

	memset(
			m_StrDebug,			// ターゲットへのポインター
			0,					// 設定する文字
			sizeof m_StrDebug	// 文字数
			);
}


/******************************************************************************
== 関数名 ： void CDebugProc::Print (  )
== 戻り値 ： void型
== 引数   ： (char *fmt,	...)
== 内容   ： 可変個引数リストにアクセス
******************************************************************************/
void CDebugProc::Print (char *fmt,	...)
{
	/* ローカル変数 */
	int font;

	/* 文字数チェック */
	font = strlen( m_StrDebug );

	va_list list;
	va_start( list, fmt );//引数リストへのポインタを指定します
	vsprintf( &m_StrDebug[ font ], fmt, list);
	va_end( list );
}


/******************************************************************************
== 関数名 ： void CDebugProc::Uninit (void)
== 戻り値 ： void型
== 引数   ： void
== 内容   ： デバッグ情報終了処理
******************************************************************************/
void CDebugProc::Uninit ( void )
{
	RELEASE(m_DebugFont);
}



/******************************************************************************
== 関数名 ： void CDebugProc::Update ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： デバッグ情報更新処理
******************************************************************************/
void CDebugProc::Update(void)
{
	//  デバイスのゲッター

	CManager *manager = GetManager();
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *m_Camera =game->GetCCamera();

	CPlayer *m_Player = game->GetPlayer();
	CField *m_Field = game->GetField();
	CSceneMouse *m_Mouse = manager->GetMouse();
	CPlayer *m_Model = game->GetPlayer();
	CBullet *m_Bullet = game->GetBullet();
	CUnique_skill *m_Unique_skill = game->GetUnique_skill();
	CLoadMap *m_LoadMap = game->GetLoadMap();
	CGamePoint *m_GamePoint = game->GetGamePoint();
	CColumnar *m_Columnar = game->GetColumnar(0);
	Print("FPS:%d\n",g_nCountFPS);
	Print( "***** カメラの情報 *****\n" );
	Print( "[カメラの視点       ( X:%.2f Y:%.2f Z:%.2f )]\n", m_Camera ->m_posV.x,m_Camera ->m_posV.y,m_Camera ->m_posV.z  );
	Print( "[カメラの注視点     ( X:%.2f Y:%.2f Z:%.2f )]\n", m_Camera ->m_posR.x,m_Camera ->m_posR.y,m_Camera ->m_posR.z  );
	Print( "[カメラの向き       ( %.2f )]\n", m_Camera ->rot.y);
	Print( "[視点と注視点の距離 ( %.2f )]\n\n", m_Camera ->m_fDistance );

	Print( "***** モデルの情報 *****\n" );
	Print( "[モデルの位置       ( X:%.2f Y:%.2f Z:%.2f )]\n",m_Model ->m_Position.x,m_Model ->m_Position.y, m_Model->m_Position.z );
	Print( "[モデルの向き       ( X:%.2f Y:%.2f Z:%.2f )]\n", m_Model ->m_Rotation.x, m_Model ->m_Rotation.y, m_Model ->m_Rotation.z );
	Print( "銃口の位置          X:%.2f Y:%.2f Z:%.2f \n\n", m_Model->m_gunpoint.x, m_Model->m_gunpoint.y, m_Model->m_gunpoint.z);
//	Print("Count:%d , Pattern:%d\n", m_Unique_skill->nCount, m_Unique_skill->nPattern);
	Print("power:%d \n", m_Player->m_Power);
	Print("今のhp:%d\n", m_Player->m_HP);
	Print("位置：x:%.2f,y:%.2f,z:%.2f\n", m_Camera->m_GunPos.x, m_Camera->m_GunPos.y, m_Camera->m_GunPos.z);

	Print("マウスのx座標:%d\n",m_Mouse->g_Mouse.x);
	Print("マウスのy座標:%d\n",m_Mouse->g_Mouse.y);
	Print("マウス:x:%.2f y:%.2f z:%.2f\n",m_Camera->m_3DPos.x,m_Camera->m_3DPos.y,m_Camera->m_3DPos.z),
	Print("debug Mode:F1\n");
	Print("score+1:F2\n");
	Print("%.6f,%.6f,%.6f\n",m_Camera->m_regulator.x,m_Camera->m_regulator.y,m_Camera->m_regulator.z);
	Print("%d\n", m_Bullet->m_Num);

	Print("モデルの読み込み：Y\n");
	Print("操作：I,K,J,L\n");
	Print("wall001の数:%d\n", m_LoadMap->m_Wall001_num);
	Print("wall002の数:%d\n", m_LoadMap->m_Wall002_num);
	Print("enemy001の数:%d\n", m_LoadMap->m_Enemy001_num);
	Print("enemy002の数:%d\n", m_LoadMap->m_Enemy002_num);
	Print("Doorの数:%d\n", m_LoadMap->m_Door_num);
	Print("天井板の数:%d\n", m_LoadMap->m_Ceiling_num);
	Print("pointの数:%d\n", m_LoadMap->m_Point_num);
	Print("今のpoint数%d\n", m_LoadMap->now_Point);
}

