//*****************************************************************************
//
// �X�R�A���� [score.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include "score.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
int			CScore::m_nScore = 0;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CScore::CScore(int nPriority) :CScene(nPriority)
{
	//m_move = VECTOR3_DEFAULT;			//�ړ���
	//m_pos = VECTOR3_DEFAULT;			// �|���S���̈ʒu
	//m_size = VECTOR3_DEFAULT;			// �|���S���傫��
	m_nScore = 0;							//�X�R�A
	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CScore::~CScore()
{
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CScore * CScore::Create()
{
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		pScore->Init();
	}
	return pScore;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CScore::Init()
{
	m_nScore = 0;

	//�X�R�A�̐���
	for (int nCntInit = 0; nCntInit < MAX_SCORE_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = NULL;
		if (m_apNumber[nCntInit] == NULL)
		{
			switch (CManager::GetMode())
			{
			//�Q�[����ʂ̏ꍇ
			case CManager::MODE_GAME:
				m_apNumber[nCntInit] = CNumber::Create(
					D3DXVECTOR3((float)(SCOREUI_SIZEX + 5 + (SCORE_SIZE_X / 2) + (SCORE_SIZE_X *nCntInit)), SCORE_POS_Y, 0),
					D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), 0);
				break;
			case CManager::MODE_RESULT:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3(
					(float)(SCREEN_WIDTH / 2 + (SCORE_SIZE_X / 2)*2 + (SCORE_SIZE_X *nCntInit)*2), SCREEN_HEIGHT/2, 0),
					D3DXVECTOR3(SCORE_SIZE_X*2, SCORE_SIZE_Y*2, 0), 0);
				break;

			default:
				break;
			}
		}
	}
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CScore::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_SCORE_NUMBER; nCntUninit++)
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
//�X�V�֐�
//*****************************************************************************
void CScore::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_GAME:
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nScore = m_nScore
					/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			}
		}
		WriteFile();
		if (CGame::GetGameState()==CGame::GAMESTATE_END)
		{
			int Scoreold = CHIScore::ReadFile();
			if (Scoreold <m_nScore)
			{
				CHIScore::WriteFile(m_nScore);
			}
			Uninit();
		}
		break;

	case CManager::MODE_RESULT:
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nScore = ReadFile()
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
//�`��֐�
//*****************************************************************************
void CScore::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_SCORE_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}
//*****************************************************************************
//���_�֐�
//*****************************************************************************
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
int CScore::ReadFile(void)
{
	int ReadScore = 0;
	//�t�@�C���|�C���^
	FILE *pFile;
	//�ǂݍ��݃��[�h(r)�Ńt�@�C���I�[�v��
	pFile = fopen("RankingServer", "r");

	//�t�@�C���̒��g���m�F
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &ReadScore);
	
		//�t�@�C�������
		fclose(pFile);
	}
	return ReadScore;
}

//*****************************************************************************
//�������݊֐�
//*****************************************************************************
void CScore::WriteFile(void)
{
	//�t�@�C���|�C���^
	FILE *pFile;
	//�������݃��[�h(��)�Ńt�@�C���I�[�v��
	pFile = fopen("RankingServer", "w");

	//�t�@�C���̒��g���m�F
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
		//�t�@�C�������
		fclose(pFile);
	}
}
