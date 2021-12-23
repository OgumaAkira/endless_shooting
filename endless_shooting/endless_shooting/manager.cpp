//*****************************************************************************
//
// マネージャー処理 [manager.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"		//マネージャーのヘッタ
#include "input.h"			//入力のヘッター
#include "renderer.h"		//レンダラーのヘッター
#include "scene.h"			//シーンのヘッター
#include "sound.h"			//サウンドのヘッター
#include "resource_manager.h"	//リソースマネージャー
#include "mode_base.h"

#include "player.h"			//プレイヤー(ターゲットマーカ)のヘッター
#include "bg.h"				//背景のヘッター
#include "button.h"			//ボタンのヘッター
#include "explosion.h"		//爆発のヘッター
#include "enemy.h"			//敵のヘッター
#include "number.h"			//数字のヘッター
#include "score.h"			//スコア値のヘッター
#include "title.h"			//タイトル画面のヘッター
#include "game.h"			//ゲーム画面のヘッター
#include "result.h"			//リザルト画面のヘッター
#include "pause.h"			//ポーズ画面のヘッダー
#include "fade.h"			//フェードのヘッター
#include "bulletUI.h"		//残弾のヘッター
#include "speed.h"			//スピードUIのヘッダー
#include "ui.h"				//UIのヘッター
#include "combo.h"			//コンボのヘッター
#include "combobonusUI.h"	//コンボボーナスのヘッター
#include "comboUI.h"		//コンボUIのヘッター
#include "effect.h"			//エフェクト

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CRenderer		*CManager::m_pRenderer				= NULL;	//レンダリングのポインタ
CScene2D		*CManager::m_paScene[MAX_TEXTURE]	= {};	//シーンのポインタ
CInputKeyboard	*CManager::m_pInputKeyboard			= NULL;	//キーボード入力のポインタ7
CMouse			*CManager::m_pMouse					= NULL;	//エネミーのポインタ
CPlayer			*CManager::m_pPlayer				= NULL;	//プレイヤーのポインタ
CEnemy			*CManager::m_pEnemy					= NULL;	//プレイヤーのポインタ
CSound			*CManager::m_pSound					= NULL;	//サウンドのポインタ
CExplosion		*CManager::m_pExplosion				= NULL;	//エクスプロージョンのポインタ
CBullet			*CManager::m_pBullet				= NULL;	//バレットのポインタ
CButton			*CManager::m_pButton				= NULL; //ボタンのポインタ
CTitle			*CManager::m_pTitle					= NULL;	//タイトルのポインタ
CGame			*CManager::m_pGame					= NULL;	//ゲームのポインタ
CResult			*CManager::m_pResult				= NULL;	//バレットのポインタ
CPause			*CManager::m_pPause					= NULL;	//ポーズのポインタ
CFade			*CManager::m_pFade					= NULL;	//フェードのポインタ
CNumber			*CManager::m_pNumber				= NULL;	//ナンバーのポインタ
CScore			*CManager::m_pScore					= NULL;	//スコアのポインタ
CCombo			*CManager::m_pCombo					= NULL;	//コンボのポインタ
CSpeed			*CManager::m_pSpeed					= NULL;	//スピードUIのポインタ
CUi				*CManager::m_pUi					= NULL;	//UIのポインタ
CComboUI		*CManager::m_pComboUI				= NULL;	//コンボUIのポインタ
CComboBonus		*CManager::m_pComboBonus			= NULL;	//コンボスコアのポインタ
CComboBonusUI	*CManager::m_pComboBonusUI			= NULL;	//コンボスコアのポインタ
CManager::MODE	 CManager::m_mode					= CManager::MODE_TITLE;	//初期モード

unique_ptr<CResourceManager> CManager::m_pResourceManager = nullptr;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu)
{
	//メモリ確保
	m_pResourceManager.reset(CResourceManager::GetInstace());

	//レンダラーの生成
	if (m_pRenderer!=nullptr)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hInstance, hWnd, TRUE);
	}

	//キーボード入力の生成
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;
		m_pInputKeyboard->Init(hInstance, hWnd);
	}
	//マウス入力の生成
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);

	//サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init();

	//モードの情報を格納する
	SetMode(m_mode);

	return S_OK;
}
//*****************************************************************************
// 終了処理
//*****************************************************************************
void CManager::Uninit(void)
{
	//シーンの破棄
	CScene::ReleaseAll();

	//キーボード入力破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//マウス入力破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//レンダラー破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update(void)
{
	//入力の更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//マウスの更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
 }

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}
//*****************************************************************************
//モード情報格納関数
//*****************************************************************************
void CManager::SetMode(MODE mode)
{

}
