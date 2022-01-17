//*****************************************************************************
//
// リソースマネージャー処理  [resource_manager.h]
// Author : Oguma Akira
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "resource_manager.h"
#include "texture.h"
#include "sound.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CResourceManager *CResourceManager::m_pResourceManager = nullptr;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CResourceManager::CResourceManager()
{
	m_pTexture = nullptr;
	m_pSound = nullptr;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CResourceManager::~CResourceManager()
{
	UnLoadAll();
}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CResourceManager::Init(void)
{
	//NULLチェック
	if (m_pTexture == nullptr)
	{
		//テクスチャのインスタンス生成
		m_pTexture = CTexture::Create();
	}

	//NULLチェック
	if (m_pSound== nullptr)
	{
		m_pSound = CSound::Create();
	}
	return E_NOTIMPL;
}

//*****************************************************************************
//ロード処理
//*****************************************************************************
void CResourceManager::LoadAll(void)
{
	//NULLチェック
	if (m_pTexture != nullptr)
	{
		//テクスチャロード
		m_pTexture->LoadAll();
	}
}

//*****************************************************************************
//アンロード処理
//*****************************************************************************
void CResourceManager::UnLoadAll(void)
{
	//NULLチェック
	if (m_pTexture != nullptr)
	{
		//テクスチャのアンロード
		m_pTexture->UnLoadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//NULLチェック
	if (m_pSound == nullptr)
	{
		//サウンドのアンロード
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//*****************************************************************************
//インスタンス取得関数
//*****************************************************************************
CResourceManager * CResourceManager::GetInstace(void)
{
	//NULLチェック
	if (m_pResourceManager == nullptr)
	{
		//メモリ確保
		m_pResourceManager = new CResourceManager;
		//NULLチェック
		if (m_pResourceManager != nullptr)
		{
			m_pResourceManager->Init();
		}
	}
	return m_pResourceManager;
}


