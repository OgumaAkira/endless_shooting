//*****************************************************************************
//
// コンボ処理 [combo.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define COLOR_COMBO (10)

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include "combo.h"
#include "comboUI.h"
#include "combobonus.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CCombo::CCombo(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;			//移動量
	m_pos = VECTOR3_DEFAULT;			// ポリゴンの位置
	m_size = VECTOR3_DEFAULT;			// ポリゴン大きさ
	m_nColor = 0;							//色数値
	m_nCombo = 0;							//コンボ数
	m_nComboScore = 0;						//コンボスコア値
	for (int nCount = 0; nCount < MAX_COMBO_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//ナンバーのポインタ配列
	}
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CCombo::~CCombo()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CCombo * CCombo::Create()
{
	CCombo *pCombo = NULL;
	if (pCombo == NULL)
	{
		pCombo = new CCombo;
		pCombo->Init();
	}
	return pCombo;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CCombo::Init()
{
	m_nColor = 0;							//色数値
	m_nCombo = 0;							//コンボ数
	m_nComboScore = 0;						//コンボスコア値
	m_bCombo = false;						//コンボの表示切替
	//ナンバーの生成
	for (int nCntInit = 0; nCntInit < MAX_COMBO_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = CNumber::Create(
			D3DXVECTOR3((float)(COMBOUI_SIZEX + 5 + (COMBO_SIZE_X / 2) + (COMBO_POS_X *nCntInit)), COMBO_POS_Y, 0),
			D3DXVECTOR3(COMBO_SIZE_X, COMBO_SIZE_Y, 0), 0);
		m_apNumber[nCntInit]->SetColor(D3DXCOLOR(0, 0, 0, 0));
	}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CCombo::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_COMBO_NUMBER; nCntUninit++)
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
void CCombo::Update(void)
{

	switch (CManager::GetMode())
	{
	case CManager::MODE_GAME:
		for (int nCntUpdate = 0; nCntUpdate < MAX_COMBO_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nCombo = m_nCombo / (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_COMBO_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_COMBO_NUMBER - 1) - nCntUpdate]->SetNumber(nCombo);
			}
		}
		break;

	default:
		break;
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CCombo::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < MAX_COMBO_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//コンボ関数
//*****************************************************************************
void CCombo::ComboAction(void)
{
		//コンボ数による色変化
	for (int nCnt = 0; nCnt < MAX_COMBO_NUMBER; nCnt++)
	{
		//緑
		if (m_nCombo >= 0 && m_nCombo < 10)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
		}
		//青
		else if (m_nCombo >= 10 && m_nCombo < 20)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(0, m_nColor, 0, m_nColor));
		}
		//赤
		else if (m_nCombo >= 20 && m_nCombo < 30)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(0, 0, m_nColor, m_nColor));
		}
		//
		else if (m_nCombo >= 30 && m_nCombo < 40)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(m_nColor, 0, 0, m_nColor));
		}
		else
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
		}
	}


	switch (CGame::GetGameState())
	{
	//敵を倒した場合
	case CGame::GAMESTATE_ENEMYBREAK:
		m_nColor = 1.0f;
		m_nComboScore = 0;
		m_nCombo += 1;
		m_bCombo = true;
		break;

	//通常状態
	case CGame::GAMESTATE_NORMAL:
		if (m_nColor > 0 && m_nColor <= 1.0f)
		{
			m_nColor -= 0.006f;
			break;
		}
		else if(m_bCombo == true && m_nColor < 0)
		{
			m_nColor = 0;									//色を消す
			m_nComboScore = m_nCombo * 250;					//コンボのスコア値
			SetSocreCombo(m_nComboScore);					//コンボスコアを格納
			CManager::GetScore()->AddScore(m_nComboScore);	//加算スコア
			m_nCombo = 0;
			m_bCombo = false;
			break;
		}
		break;

		//通常状態
	case CGame::GAMESTATE_END:
			m_nColor = 0;									//色を消す
			m_nComboScore = m_nCombo * 250;					//コンボのスコア値
			SetSocreCombo(m_nComboScore);					//コンボスコアを格納
			CManager::GetScore()->AddScore(m_nComboScore);	//加算スコア
			m_nCombo = 0;
			m_bCombo = false;
			break;

	default:
		break;
	}
	SetbCombo(m_bCombo);
}