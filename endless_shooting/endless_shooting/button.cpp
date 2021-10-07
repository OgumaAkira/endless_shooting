//*****************************************************************************
//
// �{�^������ [button.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "button.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TITELBUTTON_TEXTURE		("data/TEXTURE/SHOOT THE STARTBUTTON.png")	//Title�{�^���̃e�N�X�`��
#define RESULTBUTTON_TEXTURE	("data/TEXTURE/RETURN TO TITLE.png")		//Result�{�^���̃e�N�X�`��
#define MAX_CNT_BUTTON			(5)
#define RED_BUTTON				(D3DCOLOR_RGBA(255, 0, 0, 255))
#define DEFAULT_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))
//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CButton::m_apTexture[BUTTONTYPE_MAX] = {};	//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CButton::CButton(int nPriority) :CScene2D(nPriority)
{
	m_pos = VECTOR_DEFAULT;			// �{�^���̈ʒu
	m_size = VECTOR_DEFAULT;			// �|���S���傫��
	m_bButton = false;
	m_state = BUTTONSTATE_NORMAL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CButton::~CButton()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CButton *pButton = NULL;
	//�{�^���̃|�C���^���������������ꍇ
	if (pButton == NULL)
	{
		pButton = new CButton;
		pButton->Init(pos, size, type);
		pButton->SetObjType(OBJTYPE_BUTTON);	//�{�^���̃I�u�W�F�N�g�w��
	}
	return pButton;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CButton::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITELBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_TITLE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RESULTBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_RESULT]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		GAMERETURNBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSEGAME]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITLERETURNBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSETITLE]);
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PAUSEBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSE]); 
	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CButton::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_CNT_BUTTON; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//�e�N�X�`���̔j��
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CButton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);		//�ʒu�擾
	SetPosition(m_pos);							//�ʒu�i�[
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫���擾
	SetSize(m_size);							//�傫���i�[
	m_bButton = true;							//�{�^���̏��
	m_state = BUTTONSTATE_NORMAL;				//�������
	BirdTexture(m_apTexture[type]);				//�e�N�X�`���̏���scene2d�֊i�[
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CButton::Update(void)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h���擾
	m_pFade = CManager::GetFade();			//�t�F�[�h���擾
	CScene2D::Update();

	//�{�^���̏��
	switch (m_state)
	{
	//�^�C�g����ʂ̃{�^��
	case BUTTONSTATE_TITLE:
		if (m_bButton == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bButton = false;
		}
			//�F�̕ύX
			SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));//��
			m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	//���U���g��ʂ̃{�^��
	case BUTTONSTATE_RESULT:
		if (m_bButton == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bButton = false;
		}
		//�F�̕ύX
		SetColor(RED_BUTTON);//��
		m_pFade->SetFade(CFade::FADESTATE_IN); 
		break;

	case BUTTONSTATE_PAUSETITLE:
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//��
		CManager::SetMode(CManager::MODE_TITLE);
		break;

	case BUTTONSTATE_PAUSEGAME:
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//��	
		pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);
		CManager::SetMode(CManager::MODE_GAME);
		break;

	//�{�^���̏����ݒ�
	case BUTTONSTATE_NORMAL:
		//�����F
		SetColor(DEFAULT_COLOR);
		break;

	default:
		break;
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CButton::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//�|�[�Y��ʃ{�^���֐�
//*****************************************************************************
void CButton::PauseButton(void)
{
	POINT posPoint;
	GetCursorPos(&posPoint);		//�}�E�X���W���擾����
	if (BUTTON_POSX - m_size.x / 2 <= posPoint.x&&
		BUTTON_POSX + m_size.x / 2 >= posPoint.x&&
		BUTTON_POSY / 2 - m_size.y / 2 <= posPoint.y&&
		BUTTON_POSY / 2 + m_size.y / 2 >= posPoint.y)
	{
		m_state = BUTTONSTATE_PAUSEGAME;
	}
	else if (BUTTON_POSX - m_size.x / 2 <= posPoint.x&&
			BUTTON_POSX + m_size.x / 2 >= posPoint.x&&
			BUTTON_POSY - m_size.y / 2 <= posPoint.y&&
			BUTTON_POSY + m_size.y / 2 >= posPoint.y)
	{
		m_state = BUTTONSTATE_PAUSETITLE;
	}
}

//*****************************************************************************
//�{�^����Ԏ擾�֐�
//*****************************************************************************
void CButton::SetButton(void)
{
	//�{�^�����ʏ��Ԃ̏ꍇ
	if (m_state == BUTTONSTATE_NORMAL)
	{
		//���[�h�̏��
		switch (CManager::GetMode())
		{
			//�^�C�g����ʂ������ꍇ
		case CManager::MODE_TITLE:
			m_state = BUTTONSTATE_TITLE;	//�^�C�g���{�^����
			break;

			//�|�[�Y��ʂ������ꍇ
		case CManager::MODE_PAUSE:
			PauseButton();
			break;

			//���U���g��ʂ������ꍇ
		case CManager::MODE_RESULT:
			m_state = BUTTONSTATE_RESULT;	//���U���g�{�^����
			break;

		default:
			break;
		}
	}
}