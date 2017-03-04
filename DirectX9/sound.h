//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_


//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

class CSound
{
private:
	IXAudio2 *g_pXAudio2 ;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice ;			// マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] ;	// ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] ;					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] ;					// オーディオデータサイズ
public:
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void StopAll(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

};
#endif
