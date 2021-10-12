//*****************************************************************************
//
// �R���{�X�R�A���� [comboscore.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define _CRT_SECURE_NO_WARNING

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include "combobonus.h"
#include "score.h"
#include "combo.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
int			CComboBonus::m_nScore = 0;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CComboBonus::CComboBonus(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;			//�ړ���
	m_pos = VECTOR3_DEFAULT;			// �|���S���̈ʒu
	m_size = VECTOR3_DEFAULT;			// �|���S���傫��
	m_nScore = 0;							//�X�R�A
	for (int nCount = 0; nCount < MAX_COMBOBONUS_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CComboBonus::~CComboBonus()
{
}

//*****************************************************************************
//�N���G�C�g�֐�
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
//�������֐�
//*****************************************************************************
HRESULT CComboBonus::Init()
{
	m_nScore = 0;
	m_nColor = 1.0f;
	//�X�R�A�̐���
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
//�I���֐�
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
//�X�V�֐�
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
	//�R���{�X�R�A�\��
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
//�`��֐�
//*****************************************************************************
void CComboBonus::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_COMBOBONUS_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}
