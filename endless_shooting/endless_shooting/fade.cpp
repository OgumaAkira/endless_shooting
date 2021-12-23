//*****************************************************************************
//
// �t�F�[�h���� [fade.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "fade.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;		//�e�N�X�`���̏��
CFade::FADESTATE	CFade::m_FadeState = {};		//�g�p���Ă邩�ǂ���
int					CFade::m_color = 0;				//�F

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CFade::CFade(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_pScene2D = NULL;						//�V�[��2D�̃|�C���^�z��
	m_bSpeedFlash = true;							//
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CFade::~CFade()
{

}

//*****************************************************************************
//���[�h�֐�
//*****************************************************************************
HRESULT CFade::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		NULL, &m_pTexture);


	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CFade::UnLoad(void)
{
		if (m_pTexture != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CFade * CFade::Create()
{
	CFade *pFade = NULL;
	//�t�F�[�h�̃|�C���^���������������ꍇ
	if (pFade == NULL)
	{
		pFade = new CFade;
		pFade->Init();

	}
	return pFade;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CFade::Init()
{
		m_pScene2D = NULL;

		//�V�[��2D�̃|�C���^���������������ꍇ
		if (m_pScene2D == NULL)
		{
			m_pScene2D = new CScene2D;
			m_pScene2D->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 
							D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
			m_FadeState = FADESTATE_OUT;													//�t�F�[�h�̏��
			//BirdTexture(m_pTexture);											//�e�N�X�`���̏��
			m_bSpeedFlash = true;																	//�t�F�[�h�̃X�C�b�`
			m_color = 0;																	//�F
		}
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CFade::Uninit(void)
{
	//�w�i�̔j��
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
		}
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CFade::Update(void)
{
	//�V�[��2D��NULL���ᖳ�������ꍇ
	if (m_pScene2D != NULL)
	{
		//�t�F�[�h�̏��
		switch (m_FadeState)
		{
		//�t�F�[�h�C���̏ꍇ
		case FADESTATE_IN:
			//�t�F�[�h�X�C�b�`���I�t�̏ꍇ
			if (m_bSpeedFlash == false)
			{
				//�F�����X�ɔZ�����Ă���
				SetColor(D3DCOLOR_RGBA(m_color,m_color,m_color,m_color));
				m_color++;
			}
			//�F�̍ő�l�܂ōs�����ꍇ
			if (m_color == 255)
			{
				m_bSpeedFlash = true;					//�t�F�[�h�X�C�b�`���I���ɂ���
				m_FadeState = FADESTATE_NONE;	//�t�F�[�h��Ԃ������Ȃ���Ԃɂ���
				m_color = 255;					//��F�ɂ���
			}
			break;

		//�t�F�[�h�A�E�g�̏ꍇ
		case FADESTATE_OUT:
			//�t�F�[�h�X�C�b�`���I���̏ꍇ
			if (m_bSpeedFlash == true)
			{
				//�F�����X�ɔ����Ă���
				SetColor(D3DCOLOR_RGBA(255 - m_color, 255 - m_color, 255 - m_color, 255 - m_color));
				m_color++;
			}
			//�F�̍ő�l�܂ōs�����ꍇ
			if (m_color == 255)
			{
				m_bSpeedFlash = false;					//�t�F�[�h�X�C�b�`���I�t�ɂ���
				m_FadeState = FADESTATE_MAX;	//�t�F�[�h��Ԃ�MAX�ɂ���
				m_color = 0;					//�F�𖳂���
			}
			break;

		default:
			break;
		}
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CFade::Draw(void)
{
	//�w�i�̕`��
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Draw();
		}
}
