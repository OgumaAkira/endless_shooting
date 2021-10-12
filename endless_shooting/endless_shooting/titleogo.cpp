//�C���N���[�h�t�@�C��
#include "titlelogo.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CTitleLogo::m_pTexture = {};		//�e�N�X�`���̏��
int					CTitleLogo::m_nFrameCnt = 0;		//�_�ŃJ�E���g
//�R���X�g���N�^
CTitleLogo::CTitleLogo(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(1, 1, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_Cnt = 0;
}

//�f�X�g���N�^
CTitleLogo::~CTitleLogo()
{

}

//�N���G�C�g�֐�
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTitleLogo *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CTitleLogo;
		pButton->Init(pos, size);
	}
	return pButton;
}

//�������֐�
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_Cnt = 5;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture);
	return S_OK;
}

//�I���֐�
void CTitleLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V�֐�
void CTitleLogo::Update(void)
{
	m_pos = GetPosition();
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
	//if (m_bUse == true)
	//{
	//	m_nFrameCnt++;
	//	if (m_nFrameCnt <= 30)
	//	{
	//		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	//	}
	//	else if (m_nFrameCnt > 30)
	//	{
	//		SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	//	}
	//	if (m_nFrameCnt == 60)
	//	{
	//		m_nFrameCnt = 0;
	//		m_Cnt--;
	//	}
	//	if (m_Cnt == 0)
	//	{
	//		Uninit();
	//		m_bUse = false;
	//	}
	//}
}

//�`��֐�
void CTitleLogo::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CTitleLogo::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		GAMETITLE_TEXTURE, &m_pTexture);

	return S_OK;
}

void CTitleLogo::UnLoad(void)
{

	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}