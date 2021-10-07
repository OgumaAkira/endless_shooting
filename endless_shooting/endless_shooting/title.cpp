//*****************************************************************************
//
// タイトル画面処理 [title.cpp]
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
#include "manager.h"
#include "title.h"
#include "bg.h"
#include "enemy.h"
#include "player.h"
#include "button.h"
#include "sound.h"
#include "fade.h"
#include "hiscore.h"
#include "ui.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CBg				*CTitle::m_pBg = NULL;			//背景のポインタ
CFade			*CTitle::m_pFade = NULL;		//フェードのポインタ
CPlayer			*CTitle::m_pPlayer = NULL;		//プレイヤーのポインタ
CButton			*CTitle::m_pButton = NULL;		//ボタンのポインタ
CHIScore		*CTitle::m_pHiScore = NULL;		//ハイスコア
CUi				*CTitle::m_pUi = NULL;			//ハイスコアUI


//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle::CTitle(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CTitle * CTitle::Create()
{
	CTitle *pTitle = NULL;
	if (pTitle == NULL)
	{
		pTitle = new CTitle;
		pTitle ->Init();
		pTitle->SetObjType(OBJTYPE_TITLE);
	}
	return pTitle;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CTitle::Init()
{
	
	m_pBg = CBg::Create();		//背景のクリエイト
	POINT posPoint;
	GetCursorPos(&posPoint);	// マウス座標を取得する
	m_bButton = true;//スイッチ
	//ボタンの生成
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0),
								D3DXVECTOR3(500.0f, 200.0f, 0.0f), 
								CButton::BUTTONTYPE_TITLE);
	//タイトルロゴの生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.05f, SCREEN_HEIGHT / 2.5, 0),
						D3DXVECTOR3(1000, 900, 0), CUi::UITYPE_TITLELOGO);

	//チュートリアルの生成
	m_pUi = CUi::Create(D3DXVECTOR3(1600, 700, 0),
						D3DXVECTOR3(500, 500, 0), CUi::UITYPE_TUTORIAL);

	//ハイスコアUIの生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.5, SCORE_POS_Y + 100, 0),
						D3DXVECTOR3(300,70,0),CUi::UITYPE_HISCORE);

	//ハイスコアのクリエイト
	m_pHiScore = CHIScore::Create();

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x,(float)posPoint.y, 0),
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0));
	
	m_pFade = CFade::Create();	//フェードのクリエイト

	
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CTitle::Uninit(void)
{
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CTitle::Update(void)
{	
	pSound = CManager::GetSound();	//サウンドの情報取得
	//スイッチがオンだった場合
	if (m_bButton==true)
	{
#if DEBUG_SOUND
		//タイトルBGM
		pSound->PlaySound(CSound::SOUND_LABEL_TITLEBGM);
#endif // DEBUG_SOUND

		m_bButton = false;
	}
	m_pFade->Update();

	//フェードの状態がNONEだった場合
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
#if DEBUG_SOUND
		//サウンド停止
		pSound->StopSound(CSound::SOUND_LABEL_TITLEBGM);
#endif // DEBUG_SOUND
		CManager::SetMode(CManager::MODE_GAME);
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CTitle::Draw(void)
{

}
