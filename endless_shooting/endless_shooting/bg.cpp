//*****************************************************************************
//
// �w�i�̏��� [bg.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bg.h"
#include "button.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_SPACE01_TEXTURE ("data/TEXTURE/bg100.png")					//�F��1��TEXTURE
#define BG_SPACE02_TEXTURE ("data/TEXTURE/bg101.png")					//�F��2��TEXTURE
#define BG_SPACE03_TEXTURE ("data/TEXTURE/bg102.png")					//�F��3��TEXTURE

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBg::m_pTexture[MAX_BG_TEXTURE] = {};		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBg::CBg(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;				//�ړ���
	m_pos = VECTOR3_DEFAULT;			// �|���S���̈ʒu
	m_size = VECTOR3_DEFAULT;			// �|���S���傫��
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��No.
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//�V�[��2D�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBg::~CBg()
{

}

//*****************************************************************************
//���[�h�֐�
//*****************************************************************************
HRESULT CBg::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���(�F��1)
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE01_TEXTURE, &m_pTexture[BGTYPE_SPACE1]);

	//�e�N�X�`���̓ǂݍ��݁i�F��2�j
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE02_TEXTURE, &m_pTexture[BGTYPE_SPACE2]);

	//�e�N�X�`���̓ǂݍ��݁i�F��3�j
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE03_TEXTURE, &m_pTexture[BGTYPE_SPACE3]);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CBg::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < MAX_BG_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CBg * CBg::Create()
{
	CBg *pBg = NULL;

	//�w�i�̃|�C���^���������������ꍇ
	if (pBg == NULL)
	{
		pBg = new CBg;
		pBg->Init();
	}
		return pBg;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CBg::Init()
{
	//�w�i�̐���
	for (int nCntInit = 0; nCntInit < MAX_BG_TEXTURE; nCntInit++)
	{
		m_apScene2D[nCntInit] = NULL;

		if (m_apScene2D[nCntInit] == NULL)
		{
			m_apScene2D[nCntInit] = new CScene2D;
			m_apScene2D[nCntInit]->Init();
			m_apScene2D[nCntInit]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 ,0));
			m_apScene2D[nCntInit]->SetSize(D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT , 0));
			m_apScene2D[nCntInit]->BirdTexture(m_pTexture[nCntInit]);
			m_apScene2D[nCntInit]->SetObjType(OBJTYPE_BG);
		}
	}
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CBg::Uninit(void)
{
	//�w�i�̔j��
	for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
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
void CBg::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		break;
	
	case CManager::MODE_GAME:
	//�w�i�̃e�N�X�`�����W�ݒ�
	for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			
			m_move += D3DXVECTOR3(0.001f , 0, 0);//�ړ���
			//�w�i��m_nPatternAnim�Ő��𓮂����ăA�j���[�V��������B
			m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0),
				D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0));
		}
	}
	break;

	case CManager::MODE_RESULT:
		//�w�i�̃e�N�X�`�����W�ݒ�
		for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
		{
			if (m_apScene2D[nCntUninit] != NULL)
			{

				m_move += D3DXVECTOR3(0.001f, 0, 0);//�ړ���
				//�w�i��m_nPatternAnim�Ő��𓮂����ăA�j���[�V��������B
				m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f)), 0),
					D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f) + 1.0f), 0));
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
void CBg::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_BG_TEXTURE; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}
