//*****************************************************************************
//
// UI���� [ui.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"
#include "sound.h"


//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CUi::m_apTexture[UITYPE_MAX] = {};		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CUi::CUi(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_Cnt = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CUi::~CUi()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType)
{
	CUi *pUi = NULL;

	//�{�^���̃|�C���^�����������ꍇ
	if (pUi == NULL)
	{
		pUi = new CUi;
		pUi->Init(pos, size,nType);
	}
	return pUi;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CUi::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���(�n�C�X�R�A)
	D3DXCreateTextureFromFile(pDevice,
		HISCOREUI_TEXTURE, &m_apTexture[UITYPE_HISCORE]);

	//�e�N�X�`���̓ǂݍ���(�X�R�A)
	D3DXCreateTextureFromFile(pDevice,
		MYSCOREUI_TEXTURE, &m_apTexture[UITYPE_MYSCORE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE, &m_apTexture[UITYPE_TUTORIAL]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		GAMETITLE_TEXTURE, &m_apTexture[UITYPE_TITLELOGO]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SCOREUI_TEXTURE, &m_apTexture[UITYPE_SCORE]);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CUi::UnLoad(void)
{
	for (int nCount = 0; nCount < UITYPE_MAX; nCount++)
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
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	BirdTexture(m_apTexture[nType]);		//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CUi::Update(void)
{
	m_pos = GetPosition();	//�ʒu���擾

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CUi::Draw(void)
{
	CScene2D::Draw();
}
