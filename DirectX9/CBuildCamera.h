/********************************************************************************
* タイトル　01
* ファイル名　CBuildCamera.h
* 作成者 AT13B284 42 李昊盛
* 作成日 2016/12/20
* ツールモードで、カメラの作成
********************************************************************************/
#ifndef	_CBUILDCAMERA_H_
#define	_CBUILDCAMERA_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define BUILDCAMERA_MOVE (20.0f)		//カメラの移動量
class CBuildCamera
{
	//フレンドクラス
	friend class CWall_001;
	friend class CWall_002;
	friend class CEnemy_001;
	friend class CEnemy_002;
	friend class CBuildLight;
	friend class CTrail;
	friend class CCeiling;
	friend class CDoor;
	friend class CPoint;
	friend class CColumnar;
	friend class CStart;
	friend class CEnd;
	friend class CRobot;
private:
	D3DXVECTOR3 m_posV;		//視点
	D3DXVECTOR3 m_posR;		//注視点
	D3DXVECTOR3 m_vecU;		//上方面ベクトル
	D3DXVECTOR3 m_RotCheck;		//check向き
	D3DXVECTOR3 m_3DPos;
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX m_mtxProjection;		//プロジェクションストリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス

	float m_fDistance;		//距離
	bool m_bRotate;	//true:視点を中心、false:注視点を中心


public:
	CBuildCamera();
	~CBuildCamera();
	void Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Draw(void);		//描画処理
	void Update(void);		//更新処理


};

#endif