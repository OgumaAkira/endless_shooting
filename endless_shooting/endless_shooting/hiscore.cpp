//*****************************************************************************
//
// ハイスコア処理 [hiscore.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "hiscore.h"
#include "number.h"
#include "score.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
int	CHIScore::m_nScore = 0;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CHIScore::CHIScore()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nScore = 0;							//スコア
	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;			//ナンバーのポインタ配列
	}
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CHIScore::~CHIScore()
{
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CHIScore * CHIScore::Create()
{
	CHIScore *pHiScore = NULL;
	
	//ハイスコアのポインタが何も無かった場合
	if (pHiScore == NULL)
	{
		pHiScore = new CHIScore;
		pHiScore->Init();
	}
	return pHiScore;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CHIScore::Init(void)
{
	m_nScore = 0;	//スコア
	//スコアの生成
	for (int nCntInit = 0; nCntInit < MAX_SCORE_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = NULL;

		//ナンバーの配列ポインタが何も無かった場合
		if (m_apNumber[nCntInit] == NULL)
		{
			//モード取得
			switch (CManager::GetMode())
			{
			//タイトル画面の場合
			case CManager::MODE_TITLE:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3(
					(float)(SCREEN_WIDTH / 2 + (SCORE_SIZE_X / 2) + (SCORE_SIZE_X *nCntInit)),
					SCORE_POS_Y+100, 0),
					D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), 0);
				break;

			//リザルト画面の場合
			case CManager::MODE_RESULT:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3(
					(float)(150 + (SCORE_SIZE_X / 2) * 2 + (SCORE_SIZE_X *nCntInit) * 2),
					SCREEN_HEIGHT / 2, 0),
					D3DXVECTOR3(SCORE_SIZE_X * 2, SCORE_SIZE_Y * 2, 0), 0);
			default:
				break;
			}
		}
	}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CHIScore::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_SCORE_NUMBER; nCntUninit++)
	{
		//ナンバーがNULLではない場合
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
void CHIScore::Update(void)
{
	//モード取得
	switch (CManager::GetMode())
	{
	//タイトル画面の場合
	case CManager::MODE_TITLE:
		ReadFile();
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			//ナンバーの配列ポインタがNULLではない場合
			if (m_apNumber[nCntUpdate] != NULL)
			{
				//ハイスコア内容
				int nScore = m_nScore
					/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			}
		}
		break;
	
	//リザルト画面場合
	case CManager::MODE_RESULT:
		ReadFile();
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			//ナンバーの配列ポインタがNULLではない場合
			if (m_apNumber[nCntUpdate] != NULL)
			{
				//ハイスコア内容
				int nScore = m_nScore
					/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			}
		}
		break;

	default:
		break;
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CHIScore::Draw(void)
{
	for (int nCntDraw = 0; nCntDraw < MAX_SCORE_NUMBER; nCntDraw++)
	{
		//NULLではない場合
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//書き込み関数
//*****************************************************************************
void CHIScore::WriteFile(int nScore)
{
	m_nScore = nScore;
	//ファイルポインタ
	FILE *pFile;
	//書き込みモード(ｗ)でファイルオープン
	pFile = fopen("ScoreFile", "w");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
int CHIScore::ReadFile(void)
{
	//ファイルポインタ
	FILE *pFile;
	//読み込みモード(r)でファイルオープン
	pFile = fopen("ScoreFile", "r");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nScore);

		//ファイルを閉じる
		fclose(pFile);
	}
	return m_nScore;
}
