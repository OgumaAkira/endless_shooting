//*****************************************************************************
//
// �X�s�[�h���� [speed.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "comboUI.h"
#include "sound.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CComboUI::m_pTexture = {};		//�e�N�X�`���̏��


//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CComboUI::CComboUI(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_nColor = 0;
	m_nComboCountFrame = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CComboUI::~CComboUI()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CComboUI * CComboUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CComboUI *pComboUI = NULL;
	if (pComboUI == NULL)
	{
		pComboUI = new CComboUI;
		pComboUI->Init(pos, size);
		pComboUI->SetObjType(OBJTYPE_BUTTON);
	}
	return pComboUI;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CComboUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_nColor = 0;
	SetColor(D3DXCOLOR(0, 0, 0, 0));
	m_nComboCountFrame = 0;
	//�T�E���h�擾
	pSound = CManager::GetSound();
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture);
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CComboUI::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CComboUI::Update(void)
{
	CScene2D::Update();
	switch (CGame::GetGameState())
	{
	case CGame::GAMESTATE_ENEMYBREAK:
		m_nColor = 1.0f;
		break;

	case CGame::GAMESTATE_NORMAL:
		if (m_nColor > 0 && m_nColor <= 1.0f)
		{
			m_nColor -= 0.004f;
			break;
		}
		else
		{
			m_nColor = 0;
			break;
		}
		break;
	default:
		break;
	}
	SetColor(D3DXCOLOR(m_nColor, m_nColor, m_nColor, m_nColor));
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CComboUI::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//���[�h�֐�
//*****************************************************************************
HRESULT CComboUI::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		COMBOUI_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CComboUI::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}