//*****************************************************************************
//
// �o���b�gUI���� [bullet.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bulletUI.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBulletUI::m_pTexture = {};				//�e�N�X�`���̏��
bool				CBulletUI::m_bSpeedFlash = false;		//�c�e�\���X�C�b�`

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBulletUI::CBulletUI(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//�V�[��2D�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBulletUI::~CBulletUI()
{

}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CBulletUI::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���(�F��1)
	D3DXCreateTextureFromFile(pDevice,
		BULLETUI_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CBulletUI::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < MAX_BULLET; nCntTex++)
	{
		if (m_pTexture != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CBulletUI * CBulletUI::Create()
{
	CBulletUI *pBulletUI = NULL;
	//�o���b�gUI�̃|�C���^���������������ꍇ
	if (pBulletUI == NULL)
	{
		pBulletUI = new CBulletUI;
		pBulletUI->Init();
	}
	return pBulletUI;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CBulletUI::Init()
{
	//�c�e�̐���
	for (int nCntInit = 0; nCntInit < MAX_BULLET; nCntInit++)
	{
		m_apScene2D[nCntInit] = NULL;
		if (m_apScene2D[nCntInit] == NULL)
		{
			m_apScene2D[nCntInit] = new CScene2D;
			m_apScene2D[nCntInit]->Init();
			m_apScene2D[nCntInit]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			m_apScene2D[nCntInit]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/1.03f - 50.0f * nCntInit,100,0));
			m_apScene2D[nCntInit]->SetSize(D3DXVECTOR3(50.0f, 100, 0));
			m_apScene2D[nCntInit]->BirdTexture(m_pTexture);

		}
	}
	m_BulletCnt = 0;	//�c�e��
	m_bSpeedFlash = false;
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CBulletUI::Uninit(void)
{
	//�c�e�̔j��
	for (int nCntUninit = 0; nCntUninit < MAX_BULLET; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			m_apScene2D[nCntUninit]->Uninit();
			delete m_apScene2D[nCntUninit];
			m_apScene2D[nCntUninit] = NULL;
		}
	}
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CBulletUI::Update(void)
{
	if (m_bSpeedFlash == true)
	{
		m_apScene2D[m_BulletCnt]->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0));
		m_bSpeedFlash = false;
		if (CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
		{
			m_BulletCnt++;
		}
	}
	else if (m_BulletCnt == MAX_BULLET &&
		CGame::GetEnemy() >= 0 &&
		CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
	{
		CGame::SetGameState(CGame::GAMESTATE_END);
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CBulletUI::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_BULLET; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//�e���U�֐�
//*****************************************************************************
void CBulletUI::Loading(void)
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//���U
		m_apScene2D[nCnt]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	m_BulletCnt = 0;
}
