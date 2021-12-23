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
#include "sound.h"
#include "title.h"
#include "mode.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle::CTitle() 
{
	m_pSound = nullptr;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//インスタンス生成
//*****************************************************************************
CTitle * CTitle::GetInstance()
{
	CTitle *pTitle = NULL;
	if (pTitle == NULL)
	{
		pTitle = new CTitle;
	}
	return pTitle;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
void CTitle::Init(CMode *pMode)
{
	m_pSound = CManager::GetSound();
	//生成宣言
	
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CTitle::Update(CMode *pMode)
{	
	//m_pSound->Play();
	//m_pSound->Stop();

	//pMode->ChangeState();
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CTitle::Uninit(void)
{
	Release();
	Select(6);
}