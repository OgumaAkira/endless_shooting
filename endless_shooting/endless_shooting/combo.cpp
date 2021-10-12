//*****************************************************************************
//
// �R���{���� [combo.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define COLOR_COMBO (10)

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include "combo.h"
#include "comboUI.h"
#include "combobonus.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CCombo::CCombo(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;			//�ړ���
	m_pos = VECTOR3_DEFAULT;			// �|���S���̈ʒu
	m_size = VECTOR3_DEFAULT;			// �|���S���傫��
	m_nColor = 0;							//�F���l
	m_nCombo = 0;							//�R���{��
	m_nComboScore = 0;						//�R���{�X�R�A�l
	for (int nCount = 0; nCount < MAX_COMBO_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CCombo::~CCombo()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
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
//�������֐�
//*****************************************************************************
HRESULT CCombo::Init()
{
	m_nColor = 0;							//�F���l
	m_nCombo = 0;							//�R���{��
	m_nComboScore = 0;						//�R���{�X�R�A�l
	m_bCombo = false;						//�R���{�̕\���ؑ�
	//�i���o�[�̐���
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
//�I���֐�
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
//�X�V�֐�
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
//�`��֐�
//*****************************************************************************
void CCombo::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_COMBO_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//�R���{�֐�
//*****************************************************************************
void CCombo::ComboAction(void)
{
		//�R���{���ɂ��F�ω�
	for (int nCnt = 0; nCnt < MAX_COMBO_NUMBER; nCnt++)
	{
		//��
		if (m_nCombo >= 0 && m_nCombo < 10)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
		}
		//��
		else if (m_nCombo >= 10 && m_nCombo < 20)
		{
			m_apNumber[nCnt]->SetColor(D3DXCOLOR(0, m_nColor, 0, m_nColor));
		}
		//��
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
	//�G��|�����ꍇ
	case CGame::GAMESTATE_ENEMYBREAK:
		m_nColor = 1.0f;
		m_nComboScore = 0;
		m_nCombo += 1;
		m_bCombo = true;
		break;

	//�ʏ���
	case CGame::GAMESTATE_NORMAL:
		if (m_nColor > 0 && m_nColor <= 1.0f)
		{
			m_nColor -= 0.006f;
			break;
		}
		else if(m_bCombo == true && m_nColor < 0)
		{
			m_nColor = 0;									//�F������
			m_nComboScore = m_nCombo * 250;					//�R���{�̃X�R�A�l
			SetSocreCombo(m_nComboScore);					//�R���{�X�R�A���i�[
			CManager::GetScore()->AddScore(m_nComboScore);	//���Z�X�R�A
			m_nCombo = 0;
			m_bCombo = false;
			break;
		}
		break;

		//�ʏ���
	case CGame::GAMESTATE_END:
			m_nColor = 0;									//�F������
			m_nComboScore = m_nCombo * 250;					//�R���{�̃X�R�A�l
			SetSocreCombo(m_nComboScore);					//�R���{�X�R�A���i�[
			CManager::GetScore()->AddScore(m_nComboScore);	//���Z�X�R�A
			m_nCombo = 0;
			m_bCombo = false;
			break;

	default:
		break;
	}
	SetbCombo(m_bCombo);
}