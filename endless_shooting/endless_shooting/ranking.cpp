//#define _CRT_SECURE_NO_WARNINGS
////�C���N���[�h�t�@�C��
//#include "ranking.h"
//#include <stdio.h>
//
////�R���X�g���N�^
//CRanking::CRanking()
//{
//	m_move = D3DXVECTOR3(0, 0, 0);			//�ړ���
//	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
//	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
//	m_nScore = 0;
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��No.
//	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
//	{
//		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
//	}
//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
//	{
//		m_aScore[nCnt] = 0;
//	}
//}
//
////�f�X�g���N�^
//CRanking::~CRanking()
//{
//}
//
////�N���G�C�g�֐�
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
//	//�X�R�A�̐���
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
//	//�w�i�̕`��
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
////�ǂݍ��݊֐�
////----------------------------------
//void  CRanking::ReadFile(void)
//{
//	//�t�@�C���|�C���^
//	FILE *pFile;
//	//�ǂݍ��݃��[�h(r)�Ńt�@�C���I�[�v��
//	pFile = fopen("RankingServer", "r");
//
//	//�t�@�C���̒��g���m�F
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			fscanf(pFile, "%s", g_aRankingData[nCount].aName);
//			fscanf(pFile, "%d", &g_aRankingData[nCount].nClearTime);
//		}
//		//�t�@�C�������
//		fclose(pFile);
//	}
//}
//
////----------------------------------
////�������݊֐�
////----------------------------------
//void CRanking::WriteFile(void)
//{
//	printf("�������݂܂�\n");
//	//�t�@�C���|�C���^
//	FILE *pFile;
//	//�ǂݍ��݃��[�h(r)�Ńt�@�C���I�[�v��
//	pFile = fopen("RankingServer", "w");
//
//	//�t�@�C���̒��g���m�F
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			fprintf(pFile, "%s\n", g_aRankingData[nCount].aName);
//			fprintf(pFile, "%d\n", g_aRankingData[nCount].nClearTime);
//			printf("%s\n", g_aRankingData[nCount].aName);
//			printf("%d\n", g_aRankingData[nCount].nClearTime);
//		}
//		//�t�@�C�������
//		fclose(pFile);
//	}
//}
//int CRanking::SetRanking(int nTime, char * pName)
//{
//	int nCount;
//	for (nCount = 0; nCount < MAX_RANKING; nCount++)
//	{
//		//���ʂ��X�V����ꏊ�𔻒�
//		if (g_aRankingData[nCount].nClearTime == 0 || nTime<g_aRankingData[nCount].nClearTime)
//		{
//			//�ŏ���for���̃J�E���g�̔z��܂ŌJ��Ԃ�
//			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
//			{
//				//nTime�̒l��菬�������ʂ̒l�͏��ʂ�������
//				g_aRankingData[nCntMove].nClearTime = g_aRankingData[nCntMove - 1].nClearTime;
//				strcpy(g_aRankingData[nCntMove].aName, g_aRankingData[nCntMove - 1].aName);
//			}
//			//�J�E���g�܂ł̂ɒB������l����
//			g_aRankingData[nCount].nClearTime = nTime;
//			strcpy(g_aRankingData[nCount].aName, pName);
//			break;
//		}
//	}
//	WriteFile();
//	return nCount;
//}