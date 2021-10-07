//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// ���O�f�[�^�̃N���A
		m_aTexFileName[nCount].clear();
	}
}

CTexture * CTexture::Create(void)
{
	// �������m��
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// �����l
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

HRESULT CTexture::SetTextureName(void)
{
	// �ʏ�e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{ "data/TEXTURE/BULLET.png" },	//�eUI
		{ "data/TEXTURE/�G�@UFO�P.png" },	//�G1
		{ "data/TEXTURE/PAUSE_WINDOW.png" },	//�|�[�Y�E�B���h�E
		{ "data/TEXTURE/TITLE_RETURN.png" },	//�^�C�g�����^�[���{�^��
		{ "data/TEXTURE/GAME_RETURN.png" },		//�Q�[�����^�[���{�^��
		{ "data/TEXTURE/GAMETITLE.png" },		//�Q�[���^�C�g��
		{ "data/TEXTURE/TUTORIAL.png" },		//�`���[�g���A��
		{ "data/TEXTURE/HISCORE.png" },			//�n�C�X�R�A
		{ "data/TEXTURE/YOURSCORE.png" },		//�v���C���[�̃X�R�A
		{ "data/TEXTURE/SPEEDUP!.png" },		//�X�s�[�h�A�b�v
		{ "data/TEXTURE/COMBO_BONUS.png" },		//�R���{�{�[�i�X
		{ "data/TEXTURE/bg100.png" },			//�w�i�F��1
		{ "data/TEXTURE/bg101.png" },			//�w�i�F��2
		{ "data/TEXTURE/bg102.png" },			//�w�i�F��3
		{ "data/TEXTURE/bullet000.png" },		//�e�e
		{ "data/TEXTURE/SCORE.png" },			//�X�R�A	
		{ "data/TEXTURE/COMBO.png" }			//�R���{
	};

	// �����e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{
		{ "data/TEXTURE/explosion000.png" },	//
		{ "data/TEXTURE/number_HGM.png" },		//����HG������
	};

	return E_NOTIMPL;
}

//=============================================================================
// �S�Ẵe�N�X�`�����[�h
//=============================================================================
void CTexture::LoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexLoad();

	// �����e�N�X�`��
	SeparateTexLoad();
}

//=============================================================================
// �S�Ẵe�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexUnLoad();

	// �����e�N�X�`��
	SeparateTexUnLoad();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::NormalTexUnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE tex_type)
{
	if (tex_type < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[tex_type] != nullptr)
		{
			return m_apTexture[tex_type];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// �����e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE sepatex_type)
{
	//�z���菬����������
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		//NULL�`�F�b�N
		if (m_apSeparateTexture[sepatex_type].pSeparateTexture != nullptr)
		{
			//�e�N�X�`�����
			return m_apSeparateTexture[sepatex_type].pSeparateTexture;
		}
	}
	return LPDIRECT3DTEXTURE9();
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE sepatex_type)
{
	//�z���菬����������
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		return m_apSeparateTexture[sepatex_type].m_TexInfo;
	}
	return D3DXVECTOR2(0.0f,0.0f);
}

//=============================================================================
// �����e�N�X�`���̃��[�v�t���O
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE sepatex_type)
{
	//�z���菬����������
	if (sepatex_type < SEPARATE_TEX_MAX)
	{
		return m_apSeparateTexture[sepatex_type].bLoop;
	}

	return false;
}
