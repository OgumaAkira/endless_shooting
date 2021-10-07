//*****************************************************************************
//
// �i���o�[�̏��� [number.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "number.h"
#include "scene.h"
//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CNumber::m_pTexture = NULL;		//�e�N�X�`���̏��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;								//���_�o�b�t�@�̏��
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̑傫��
	m_tex = D3DXVECTOR2(0.0f, 0.0f);				//�e�X�N�`��
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�J���[
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CNumber::~CNumber()
{
}

//*****************************************************************************
// ���[�h�֐�
//*****************************************************************************
HRESULT CNumber::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		NUMBER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// �A�����[�h�֐�
//*****************************************************************************
void CNumber::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// �N���G�C�g�֐�
//*****************************************************************************
CNumber * CNumber::Create(D3DXVECTOR3 pos ,D3DXVECTOR3 size, int nTex)
{
	CNumber *pNumber = NULL;
	//�i���o�[�̃|�C���^���������������ꍇ
	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		pNumber->Init(pos, size, nTex);
	}
	return pNumber;
}
//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���_����ݒ�
	VERTEX_2D *pVtx;


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE_NUMBER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);

	//�|���S���̒��S�ʒu
	m_pos = pos;
	m_size = size;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//�E��

	//rhw�̐ݒ� 
	pVtx[0].rhw = 1.0f;	//����
	pVtx[1].rhw = 1.0f;	//�E��
	pVtx[2].rhw = 1.0f;	//����
	pVtx[3].rhw = 1.0f;	//�E��

	//�F�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//����
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�E��
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//����
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�E��

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CNumber::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//�E��

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_color);//����
	pVtx[1].col = D3DXCOLOR(m_color);//�E��
	pVtx[2].col = D3DXCOLOR(m_color);//����
	pVtx[3].col = D3DXCOLOR(m_color);//�E��

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CNumber::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

//*****************************************************************************
//�i���o�[���i�[�֐�
//*****************************************************************************
void CNumber::SetNumber(int nNumber)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 1.0f);
	
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
