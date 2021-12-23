//*****************************************************************************
//
// UI処理 [ui.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui.h"
#include "texture.h"
#include "sound.h"
#include "resource_manager.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CUi::m_apTexture[UITYPE_MAX] = {};		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CUi::CUi(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_Cnt = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CUi::~CUi()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType)
{
	CUi *pUi = NULL;

	//ボタンのポインタが無かった場合
	if (pUi == NULL)
	{
		pUi = new CUi;
		pUi->Init(pos, size,nType);
	}
	return pUi;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CUi::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(ハイスコア)
	D3DXCreateTextureFromFile(pDevice,
		HISCOREUI_TEXTURE, &m_apTexture[UITYPE_HISCORE]);

	//テクスチャの読み込み(スコア)
	D3DXCreateTextureFromFile(pDevice,
		MYSCOREUI_TEXTURE, &m_apTexture[UITYPE_MYSCORE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE, &m_apTexture[UITYPE_TUTORIAL]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		GAMETITLE_TEXTURE, &m_apTexture[UITYPE_TITLELOGO]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		SCOREUI_TEXTURE, &m_apTexture[UITYPE_SCORE]);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CUi::UnLoad(void)
{
	for (int nCount = 0; nCount < UITYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	//テクスチャのポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;
	CScene2D::Init(pos, size);
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PLAYER));					//テクスチャの情報
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CUi::Update(void)
{
	m_pos = GetPos();	//位置を取得

	CScene2D::Update();
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CUi::Draw(void)
{
	CScene2D::Draw();
}

