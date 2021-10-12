//*****************************************************************************
//
// サウンドの処理 [sound.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
//サウンドのクラス宣言
//*****************************************************************************
class CSound
{
public:
	//構造体定義(再生内容)
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,			// TITLEBGM
		SOUND_LABEL_GAMEBGM,				// GAMEBGM
		SOUND_LABEL_RESULTBGM,				// RESULTBGM
		SOUND_LABEL_SE_SHOT,				// 弾発射音
		SOUND_LABEL_SE_BUTTON,				// ヒット音
		SOUND_LABEL_SE_EXPLOSION,			// 爆発音
		SOUND_LABEL_SE_SPEEDUP,				// スピードアップ
		SOUND_LABEL_MAX,					//最大数
	}SOUND_LABEL;

	CSound();								//コンストラクタ
	~CSound();								//デストラクタ

	//メンバ関数
	HRESULT InitSound(HWND hWnd);			//初期化関数
	void UninitSound(void);					//終了関数
	HRESULT PlaySound(SOUND_LABEL label);	//再生関数
	void StopSound(SOUND_LABEL label);		//停止関数
	void StopSoundTo(void);					//一時停止関数

private:
	//メンバ変数
	//構造体定義(変数宣言)
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	//チェックチャンク
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	
	//読み込みチェックチャンク
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	

	IXAudio2 *m_pXAudio2 ;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];			// 各音素材のパラメータ
};
#endif 