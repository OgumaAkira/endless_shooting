//*****************************************************************************
//
// リザルト画面の処理 [result.cpp]
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

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CPlayer			*CResult::m_pPlayer = NULL;	//プレイヤーのポインタ
CBg				*CResult::m_pBg = NULL;	//背景のポインタ
CFade			*CResult::m_pFade = NULL;	//フェードのポインタ
CButton			*CResult::m_pButton = NULL;	//ボタンのポインタ
CScore			*CResult::m_pScore = NULL;//スコアのポインタ
CHIScore		*CResult::m_pHiScore = NULL;		//ハイスコア
CUi				*CResult::m_pHiScoreUI = NULL;		//ハイスコアUI

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_bButton = true;//リザルト画面のスイッチ
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CResult * CResult::Create()
{
	CResult *pResult = NULL;
	if (pResult == NULL)
	{
		pResult = new CResult;
		pResult->Init();
		pResult->SetObjType(OBJTYPE_RESULT);
	}
	return pResult;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CResult::Init()
{

	m_pBg = CBg::Create();				//背景のクリエイト
	POINT posPoint;						
	GetCursorPos(&posPoint);			// マウス座標を取得する
	//ボタンの生成
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0), 
								D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_RESULT);

	//ハイスコアUIの生成
	m_pHiScoreUI = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.3f, SCORE_POS_Y + 270, 0), 
									D3DXVECTOR3(600, 150, 0),CUi::UITYPE_HISCORE);
	m_pHiScoreUI = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCORE_POS_Y + 270, 0),
									D3DXVECTOR3(600, 150, 0), CUi::UITYPE_MYSCORE);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f), 
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0));


	m_pFade = CFade::Create();				//フェードのクリエイト
	m_bButton = true;						//リザルト画面のスイッチ
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CResult::Uninit(void)
{
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CResult::Update(void)
{
	CSound *pSound = CManager::GetSound();		//サウンド情報取得
	m_pFade->Update();							//フェードの更新
	m_pBg->Update();							//背景の更新

	//ボタンが押されていない場合
	if (m_bButton==true)
	{
		#if DEBUG_SOUND
		pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);	//リザルトBGMを流す
		#endif // DEBUG_SOUND
		m_bButton = false;									//リザルト画面のボタン
		m_pHiScore = CHIScore::Create();
		m_pScore = CScore::Create();
	}
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
		#if DEBUG_SOUND
		//サウンド停止
		pSound->StopSound(CSound::SOUND_LABEL_RESULTBGM);
		#endif // DEBUG_SOUND
		CManager::SetMode(CManager::MODE_TITLE);
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CResult::Draw(void)
{
}
