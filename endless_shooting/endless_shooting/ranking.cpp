//#define _CRT_SECURE_NO_WARNINGS
////インクルードファイル
//#include "ranking.h"
//#include <stdio.h>
//
////コンストラクタ
//CRanking::CRanking()
//{
//	m_move = D3DXVECTOR3(0, 0, 0);			//移動量
//	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
//	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
//	m_nScore = 0;
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;//アニメーションパターンNo.
//	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
//	{
//		m_apNumber[nCount] = NULL;		//ナンバーのポインタ配列
//	}
//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
//	{
//		m_aScore[nCnt] = 0;
//	}
//}
//
////デストラクタ
//CRanking::~CRanking()
//{
//}
//
////クリエイト関数
//CRanking * CRanking::Create()
//{
//	CRanking *pScore = NULL;
//	if (pScore == NULL)
//	{
//		pScore = new CRanking;
//		pScore->Init();
//	}
//	return pScore;
//}
//
//HRESULT CRanking::Init()
//{
//	m_nScore = 0;
//	//スコアの生成
//	for (int nCntInit = 0; nCntInit < MAX_SCORE_NUMBER; nCntInit++)
//	{
//		m_apNumber[nCntInit] = NULL;
//
//		if (m_apNumber[nCntInit] == NULL)
//		{
//			m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3((float)(0 + (SCORE_SIZE_X / 2) + (SCORE_SIZE_X *nCntInit)), SCORE_POS_Y, 0),
//				D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), 0);
//
//		}
//	}
//	return S_OK;
//}
//
//void CRanking::Uninit(void)
//{
//	for (int nCntUninit = 0; nCntUninit < MAX_SCORE_NUMBER; nCntUninit++)
//	{
//		if (m_apNumber[nCntUninit] != NULL)
//		{
//			m_apNumber[nCntUninit]->Uninit();
//			delete m_apNumber[nCntUninit];
//			m_apNumber[nCntUninit] = NULL;
//		}
//	}
//}
//
//void CRanking::Update(void)
//{
//	for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
//	{
//		if (m_apNumber[nCntUpdate] != NULL)
//		{
//			int nScore = m_nScore
//				/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
//			m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
//			m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
//		}
//	}
//}
//
//void CRanking::Draw(void)
//{
//	//背景の描画
//	for (int nCntDraw = 0; nCntDraw < MAX_SCORE_NUMBER; nCntDraw++)
//	{
//		if (m_apNumber[nCntDraw] != NULL)
//		{
//			m_apNumber[nCntDraw]->Draw();
//		}
//	}
//}
//
//void CRanking::SetScore(int nScore)
//{
//	m_nScore = nScore;
//}
//
//void CRanking::AddScore(int nScore)
//{
//	m_nScore += nScore;
//}
//
////----------------------------------
////読み込み関数
////----------------------------------
//void  CRanking::ReadFile(void)
//{
//	//ファイルポインタ
//	FILE *pFile;
//	//読み込みモード(r)でファイルオープン
//	pFile = fopen("RankingServer", "r");
//
//	//ファイルの中身を確認
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			fscanf(pFile, "%s", g_aRankingData[nCount].aName);
//			fscanf(pFile, "%d", &g_aRankingData[nCount].nClearTime);
//		}
//		//ファイルを閉じる
//		fclose(pFile);
//	}
//}
//
////----------------------------------
////書き込み関数
////----------------------------------
//void CRanking::WriteFile(void)
//{
//	printf("書き込みます\n");
//	//ファイルポインタ
//	FILE *pFile;
//	//読み込みモード(r)でファイルオープン
//	pFile = fopen("RankingServer", "w");
//
//	//ファイルの中身を確認
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			fprintf(pFile, "%s\n", g_aRankingData[nCount].aName);
//			fprintf(pFile, "%d\n", g_aRankingData[nCount].nClearTime);
//			printf("%s\n", g_aRankingData[nCount].aName);
//			printf("%d\n", g_aRankingData[nCount].nClearTime);
//		}
//		//ファイルを閉じる
//		fclose(pFile);
//	}
//}
//int CRanking::SetRanking(int nTime, char * pName)
//{
//	int nCount;
//	for (nCount = 0; nCount < MAX_RANKING; nCount++)
//	{
//		//順位を更新する場所を判定
//		if (g_aRankingData[nCount].nClearTime == 0 || nTime<g_aRankingData[nCount].nClearTime)
//		{
//			//最初のfor文のカウントの配列まで繰り返す
//			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
//			{
//				//nTimeの値より小さい順位の値は順位を下げる
//				g_aRankingData[nCntMove].nClearTime = g_aRankingData[nCntMove - 1].nClearTime;
//				strcpy(g_aRankingData[nCntMove].aName, g_aRankingData[nCntMove - 1].aName);
//			}
//			//カウントまでのに達したら値を代入
//			g_aRankingData[nCount].nClearTime = nTime;
//			strcpy(g_aRankingData[nCount].aName, pName);
//			break;
//		}
//	}
//	WriteFile();
//	return nCount;
//}