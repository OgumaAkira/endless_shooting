//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// 名前データのクリア
		m_aTexFileName[nCount].clear();
	}
}

CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// 初期値
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

HRESULT CTexture::SetTextureName(void)
{
	// 通常テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{ "data/TEXTURE/BULLET.png" },	//弾UI
		{ "data/TEXTURE/敵　UFO１.png" },	//敵1
		{ "data/TEXTURE/PAUSE_WINDOW.png" },	//ポーズウィンドウ
		{ "data/TEXTURE/TITLE_RETURN.png" },	//タイトルリターンボタン
		{ "data/TEXTURE/GAME_RETURN.png" },		//ゲームリターンボタン
		{ "data/TEXTURE/GAMETITLE.png" },		//ゲームタイトル
		{ "data/TEXTURE/TUTORIAL.png" },		//チュートリアル
		{ "data/TEXTURE/HISCORE.png" },			//ハイスコア
		{ "data/TEXTURE/YOURSCORE.png" },		//プレイヤーのスコア
		{ "data/TEXTURE/SPEEDUP!.png" },		//スピードアップ
		{ "data/TEXTURE/COMBO_BONUS.png" },		//コンボボーナス
		{ "data/TEXTURE/bg100.png" },			//背景宇宙1
		{ "data/TEXTURE/bg101.png" },			//背景宇宙2
		{ "data/TEXTURE/bg102.png" },			//背景宇宙3
		{ "data/TEXTURE/bullet000.png" },		//銃弾
		{ "data/TEXTURE/SCORE.png" },			//スコア	
		{ "data/TEXTURE/COMBO.png" }			//コンボ
	};

	// 分割テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{
		{ "data/TEXTURE/explosion000.png" },	//
		{ "data/TEXTURE/number_HGM.png" },		//数字HG明朝体
	};

	return E_NOTIMPL;
}

//=============================================================================
// 全てのテクスチャロード
//=============================================================================
void CTexture::LoadAll(void)
{
	// 通常テクスチャ
	NormalTexLoad();

	// 分割テクスチャ
	SeparateTexLoad();
}

//=============================================================================
// 全てのテクスチャアンロード
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// 通常テクスチャ
	NormalTexUnLoad();

	// 分割テクスチャ
	SeparateTexUnLoad();
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::NormalTexUnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE tex_type)
{
	if (tex_type < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[tex_type] != nullptr)
		{
			return m_apTexture[tex_type];
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE sepatex_type)
{
	//配列より小さかったら
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		//NULLチェック
		if (m_apSeparateTexture[sepatex_type].pSeparateTexture != nullptr)
		{
			//テクスチャ情報
			return m_apSeparateTexture[sepatex_type].pSeparateTexture;
		}
	}
	return LPDIRECT3DTEXTURE9();
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE sepatex_type)
{
	//配列より小さかったら
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		return m_apSeparateTexture[sepatex_type].m_TexInfo;
	}
	return D3DXVECTOR2(0.0f,0.0f);
}

//=============================================================================
// 分割テクスチャのループフラグ
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE sepatex_type)
{
	//配列より小さかったら
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		return m_apSeparateTexture[sepatex_type].bLoop;
	}

	return false;
}
