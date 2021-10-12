//*****************************************************************************
//
// ポーズ画面の処理 [pause.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "score.h"
#include "manager.h"
#include "result.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "button.h"
#include "fade.h"
#include "hiscore.h"
#include "ui.h"
#include "pause.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CPlayer			*CPause::m_pPlayer = NULL;		//プレイヤーのポインタ
CBg				*CPause::m_pBg = NULL;			//背景のポインタ
CFade			*CPause::m_pFade = NULL;		//フェードのポインタ
CButton			*CPause::m_pButton = NULL;		//ボタンのポインタ
CUi				*CPause::m_pUi = NULL;			//ハイスコアUI

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPause::CPause(int nPriority) : CScene(nPriority)
{

}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CPause * CPause::Create()
{
	CPause *pPause = NULL;
	if (pPause == NULL)
	{
		pPause = new CPause;
		pPause->Init();
		pPause->SetObjType(OBJTYPE_PAUSE);
	}
	return pPause;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CPause::Init()
{
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0),
		D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_PAUSETITLE);
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY/1.5f, 0),
		D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_PAUSEGAME);

	//ポーズ画面のUI
	m_pButton = CButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),
								D3DXVECTOR3(900, 900, 0), CButton::BUTTONTYPE_PAUSE);

	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CPause::Uninit(void)
{
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CPause::Update(void)
{
#if DEBUG_SOUND
	//サウンド停止	
	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);			//サウンドを止める
#endif // DEBUG_SOUND
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CPause::Draw(void)
{
}
