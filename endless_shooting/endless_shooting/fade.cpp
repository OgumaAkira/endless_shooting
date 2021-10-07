//*****************************************************************************
//
// フェード処理 [fade.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "fade.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;		//テクスチャの情報
CFade::FADESTATE	CFade::m_FadeState = {};		//使用してるかどうか
int					CFade::m_color = 0;				//色

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CFade::CFade(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_pScene2D = NULL;						//シーン2Dのポインタ配列
	m_bSpeedFlash = true;							//
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CFade::~CFade()
{

}

//*****************************************************************************
//ロード関数
//*****************************************************************************
HRESULT CFade::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		NULL, &m_pTexture);


	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CFade::UnLoad(void)
{
		if (m_pTexture != NULL)
		{
			//テクスチャの破棄
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CFade * CFade::Create()
{
	CFade *pFade = NULL;
	//フェードのポインタが何も無かった場合
	if (pFade == NULL)
	{
		pFade = new CFade;
		pFade->Init();

	}
	return pFade;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CFade::Init()
{
		m_pScene2D = NULL;

		//シーン2Dのポインタが何も無かった場合
		if (m_pScene2D == NULL)
		{
			m_pScene2D = new CScene2D;
			m_pScene2D->Init();
			m_pScene2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));	//位置
			m_pScene2D->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));				//大きさ
			m_FadeState = FADESTATE_OUT;													//フェードの状態
			m_pScene2D->BirdTexture(m_pTexture);											//テクスチャの情報
			m_bSpeedFlash = true;																	//フェードのスイッチ
			m_color = 0;																	//色
		}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CFade::Uninit(void)
{
	//背景の破棄
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
		}
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CFade::Update(void)
{
	//シーン2DがNULLじゃ無かった場合
	if (m_pScene2D != NULL)
	{
		//フェードの状態
		switch (m_FadeState)
		{
		//フェードインの場合
		case FADESTATE_IN:
			//フェードスイッチがオフの場合
			if (m_bSpeedFlash == false)
			{
				//色を徐々に濃くしていく
				m_pScene2D->SetColor(D3DCOLOR_RGBA(m_color,m_color,m_color,m_color));
				m_color++;
			}
			//色の最大値まで行った場合
			if (m_color == 255)
			{
				m_bSpeedFlash = true;					//フェードスイッチをオンにする
				m_FadeState = FADESTATE_NONE;	//フェード状態を何もない状態にする
				m_color = 255;					//一色にする
			}
			break;

		//フェードアウトの場合
		case FADESTATE_OUT:
			//フェードスイッチがオンの場合
			if (m_bSpeedFlash == true)
			{
				//色を徐々に抜けていく
				m_pScene2D->SetColor(D3DCOLOR_RGBA(255 - m_color, 255 - m_color, 255 - m_color, 255 - m_color));
				m_color++;
			}
			//色の最大値まで行った場合
			if (m_color == 255)
			{
				m_bSpeedFlash = false;					//フェードスイッチをオフにする
				m_FadeState = FADESTATE_MAX;	//フェード状態をMAXにする
				m_color = 0;					//色を無くす
			}
			break;

		default:
			break;
		}
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CFade::Draw(void)
{
	//背景の描画
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Draw();
		}
}
