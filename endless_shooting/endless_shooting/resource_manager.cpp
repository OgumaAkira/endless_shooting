//*****************************************************************************
//
// ���\�[�X�}�l�[�W���[����  [resource_manager.h]
// Author : Oguma Akira
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "resource_manager.h"
#include "texture.h"
#include "sound.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CResourceManager *CResourceManager::m_pResourceManager = nullptr;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResourceManager::CResourceManager()
{
	m_pTexture = nullptr;
	m_pSound = nullptr;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CResourceManager::~CResourceManager()
{
	UnLoadAll();
}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CResourceManager::Init(void)
{
	//NULL�`�F�b�N
	if (m_pTexture == nullptr)
	{
		//�e�N�X�`���̃C���X�^���X����
		m_pTexture = CTexture::Create();
	}

	//NULL�`�F�b�N
	if (m_pSound== nullptr)
	{
		m_pSound = CSound::Create();
	}
	return E_NOTIMPL;
}

//*****************************************************************************
//���[�h����
//*****************************************************************************
void CResourceManager::LoadAll(void)
{
	//NULL�`�F�b�N
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`�����[�h
		m_pTexture->LoadAll();
	}
}

//*****************************************************************************
//�A�����[�h����
//*****************************************************************************
void CResourceManager::UnLoadAll(void)
{
	//NULL�`�F�b�N
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̃A�����[�h
		m_pTexture->UnLoadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//NULL�`�F�b�N
	if (m_pSound == nullptr)
	{
		//�T�E���h�̃A�����[�h
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//*****************************************************************************
//�C���X�^���X�擾�֐�
//*****************************************************************************
CResourceManager * CResourceManager::GetInstace(void)
{
	//NULL�`�F�b�N
	if (m_pResourceManager == nullptr)
	{
		//�������m��
		m_pResourceManager = new CResourceManager;
		//NULL�`�F�b�N
		if (m_pResourceManager != nullptr)
		{
			m_pResourceManager->Init();
		}
	}
	return m_pResourceManager;
}


