//*****************************************************************************
//
// スピード処理 [speed.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "comboUI.h"
#include "sound.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CComboUI::m_pTexture = {};		//テクスチャの情報


//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CComboUI::CComboUI(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nColor = 0;
	m_nComboCountFrame = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CComboUI::~CComboUI()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CComboUI * CComboUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CComboUI *pComboUI = NULL;
	if (pComboUI == NULL)
	{
		pComboUI = new CComboUI;
		pComboUI->Init(pos, size);
		pComboUI->SetObjType(OBJTYPE_BUTTON);
	}
	return pComboUI;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CComboUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_nColor = 0;
	SetColor(D3DXCOLOR(0, 0, 0, 0));
	m_nComboCountFrame = 0;
	//サウンド取得
	pSound = CManager::GetSound();
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CComboUI::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CComboUI::Update(void)
{
	CScene2D::Update();
	switch (CGame::GetGameState())
	{
	case CGame::GAMESTATE_ENEMYBREAK:
		m_nColor = 1.0f;
		break;

	case CGame::GAMESTATE_NORMAL:
		if (m_nColor > 0 && m_nColor <= 1.0f)
		{
			m_nColor -= 0.004f;
			break;
		}
		else
		{
			m_nColor = 0;
			break;
		}
		break;
	default:
		break;
	}
	SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CComboUI::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//ロード関数
//*****************************************************************************
HRESULT CComboUI::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		COMBOUI_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CComboUI::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}