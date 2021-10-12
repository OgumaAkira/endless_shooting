//*****************************************************************************
//
// コンボスコア処理 [comboscore.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define _CRT_SECURE_NO_WARNING

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include "combobonus.h"
#include "score.h"
#include "combo.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
int			CComboBonus::m_nScore = 0;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CComboBonus::CComboBonus(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;			//移動量
	m_pos = VECTOR3_DEFAULT;			// ポリゴンの位置
	m_size = VECTOR3_DEFAULT;			// ポリゴン大きさ
	m_nScore = 0;							//スコア
	for (int nCount = 0; nCount < MAX_COMBOBONUS_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//ナンバーのポインタ配列
	}
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CComboBonus::~CComboBonus()
{
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CComboBonus * CComboBonus::Create()
{
	CComboBonus *pComboScore = NULL;
	if (pComboScore == NULL)
	{
		pComboScore = new CComboBonus;
		pComboScore->Init();
	}
	return pComboScore;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CComboBonus::Init()
{
	m_nScore = 0;
	m_nColor = 1.0f;
	//スコアの生成
	for (int nCntInit = 0; nCntInit < MAX_COMBOBONUS_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = NULL;
		if (m_apNumber[nCntInit] == NULL)
		{
			m_apNumber[nCntInit] = CNumber::Create(
				D3DXVECTOR3((float)(700 + (SCORE_SIZE_X / 4) + (SCORE_SIZE_X *nCntInit)), SCORE_POS_Y+15, 0),
				D3DXVECTOR3(SCORE_SIZE_X/2, SCORE_SIZE_Y/2, 0), 0);
		}
	}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CComboBonus::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_COMBOBONUS_NUMBER; nCntUninit++)
	{
		if (m_apNumber[nCntUninit] != NULL)
		{
			m_apNumber[nCntUninit]->Uninit();
			delete m_apNumber[nCntUninit];
			m_apNumber[nCntUninit] = NULL;
		}
	}
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CComboBonus::Update(void)
{
	
	for (int nCntUpdate = 0; nCntUpdate < MAX_COMBOBONUS_NUMBER; nCntUpdate++)
	{
		if (m_apNumber[nCntUpdate] != NULL)
		{
			int nScore = m_nScore
				/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
			m_apNumber[(MAX_COMBOBONUS_NUMBER - 1) - nCntUpdate]->Update();
			m_apNumber[(MAX_COMBOBONUS_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			m_apNumber[nCntUpdate]->SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
		}
	}
	//コンボスコア表示
	if (m_nColor > 0 && m_nColor <= 1.0f)
	{
		m_nColor -= 0.005f;
	}
	else
	{
		m_nColor = 0;
		Uninit();
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CComboBonus::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < MAX_COMBOBONUS_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}
