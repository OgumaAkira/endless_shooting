//*****************************************************************************
//
// �V�[��2D�̏��� [scene2D.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define POLYGON_CNT		(4)									//�|���S���J�E���g��
#define AT_VECTOR_A		(D3DXVECTOR2(0.0f, 0.0f))			//�A�j���[�V�����e�N�X�`��A
#define AT_VECTOR_B		(D3DXVECTOR2(1.0f, 1.0f))			//�A�j���[�V�����e�N�X�`��B
#define COLOR_DEFAULT	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//�f�t�H���g�J���[
#define MAX_NUMBER		(10)								//�����̉摜���g���ꍇ�̐�

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CSceneBase(nPriority)
{
	m_nPatternAnim      = 0;		//�A�j���[�V�����p�^�[����
	m_nCounterAnim      = 0;		//�A�j���[�V�����J�E���^�[
	m_nCountAnim        = 0;		//�A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;		//�A�j���[�V�����̃p�^�[��
	m_nLoop             = -1;		//���[�v���邩�ǂ���
	m_nSpeedTexture     = 0;		//�e�N�X�`���̈ړ����x
	m_nFlashFlame       = 0.0f;		//�_�ŗp�̃J�E���^�[
	m_fDivisionCounter  = 0.0f;		// �X�N���[���̃J�E���^�[
	m_fDivisionBaseNum	= 0.0f;		//�X�N���[���̃J�E���^�[
	m_fRotasion         = 0.0f;		//��]�p�ϐ�
	m_fScaleNum         = 0.0f;		//�g��p�ϐ�
	m_fSubFlashNum      = 0.0f;		//�|���S���̓_���p
	m_fSubNum           = 0.0f;		//�|���S���̃T�u�_���p
	m_fFadeSpeedNum     = 0.0f;		//�t�F�[�h�̃X�s�[�h
	m_bDisappearFlag	= false;	//�_�ŗp�̃t���O
	m_bFadeOut			= false;	//�t�F�[�h�̃t���O
	m_bNumber			= false;	//�g�������̃t���O
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
// �N���G�C�g�֐�
//*****************************************************************************
CScene2D * CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene2D *pScene2D = new CScene2D();

	//�V�[��2D�̃|�C���^���������������ꍇ
	if (pScene2D != nullptr)
	{
		pScene2D->Init(pos,size);
	}
	return pScene2D;
}

//*****************************************************************************
// �t�F�[�h�N���G�C�g�֐�
//*****************************************************************************
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum)
{
	// �I�u�W�F�N�g�𐶐�
	CScene2D* pScene = new CScene2D();

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->m_fFadeSpeedNum = fFadeNum;
		pScene->m_fSubFlashNum = 0.0f;
		pScene->GetColor().a = 0.0f;
		pScene->m_bFadeOut = true;

		// ����������
		pScene->Init(pos, size);
	}

	return pScene;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CScene2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	SetPos(pos);		//���W
	SetSize(size);		//�T�C�Y

	//���_�̐���

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CScene2D::Uninit(void)
{
	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScene2D::Update(void)
{

}
//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene2D::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, nullptr);

}

//=============================================
// ���_�̐����֐�
//=============================================
void CScene2D::CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		//�o�b�t�@

	if (m_bNumber == true)
	{
		//���_�o�b�t�@�̐���
		pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_NUMBER,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pVtxBuff, nullptr);
	}
	else
	{
		//���_�o�b�t�@�̐���
		pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pVtxBuff, nullptr);
	}

	//���_���
	VERTEX_2D *pVtx = nullptr;
	D3DXCOLOR color = GetColor();

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	for (int nVertex = 0; nVertex < NUM_VERTEX; nVertex++)
	{
		pVtx[nVertex].rhw = 1.0f;
		pVtx[nVertex].col = color;
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// ���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);
}

//=============================================
// ���_�̐ݒ�
//=============================================
void CScene2D::SetVertex(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		//�o�b�t�@

	//���_���
	VERTEX_2D *pVtx = nullptr;
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR color = GetColor();

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	for (int nVertex = 0; nVertex < NUM_VERTEX; nVertex++)
	{
		pVtx[nVertex].rhw = 1.0f;
		pVtx[nVertex].col = color;
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// ���_�o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);
}

//*****************************************************************************
// �A�j���[�V�����������֐�
//*****************************************************************************
void CScene2D::InitAnimation(int nPatternAnim, int nCounterAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;

	//���_����ݒ�
	//���_���
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		//�o�b�t�@

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}
//*****************************************************************************
// �A�j���[�V�����X�V�֐�
//*****************************************************************************
void CScene2D::UpdateAnimation(void)
{
	//�A�j���[�V�����̃J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;

	//���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)
	{
		m_nCountAnim = 0;		//�A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnimPattern++;	//�A�j���[�V�����̃p�^�[�����J�E���g������
	}

	//�A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		//���l��߂��Ă���
		m_nCountAnimPattern = 0;
		if (m_nLoop == 0)
		{
			Uninit();
		}
	}
	else
	{
		// ���_����ݒ�
		VERTEX_2D *pVtx = nullptr;
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

																// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();
	}
}

//*****************************************************************************
// �e�N�X�`���̃X�N���[�������擾
//*****************************************************************************
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;

	////���_����ݒ�
	//VERTEX_2D *pVtx = nullptr;
	//LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	//�o�b�t�@���擾

	////�J�E���^�[��i�߂�
	//m_nCountAnim++;

	//if (m_nCountAnim>=m_nSpeedTexture)	//�A�j���[�V�����̑���
	//{
	//	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	//�e�N�X�`�����W���X�V
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

	// ���_�o�b�t�@���A�����b�N����
	//	pVtxBuff->Unlock();
	//
	//	m_fDivisionCounter += m_fDivisionBaseNum;
	//	m_nCountAnim = 0;
	//}
}

//*****************************************************************************
// �e�N�X�`���̃X�N���[�������X�V
//*****************************************************************************
void CScene2D::UpdateScroll(void)
{
	//���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	//�o�b�t�@���擾

														//�J�E���^�[��i�߂�
	m_nCountAnim++;

	if (m_nCountAnim >= m_nSpeedTexture)	//�A�j���[�V�����̑���
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();

		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCountAnim = 0;
	}
}

//*****************************************************************************
// �g��֐�
//*****************************************************************************
void CScene2D::ScaleUp(float fScaleUp)
{
	//���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	m_fScaleNum += fScaleUp;

	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

}

//*****************************************************************************
// �|���S���̓_��
//*****************************************************************************
void CScene2D::FlashPolygon(int nFlashFlame)
{
	//���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̌��Z
	m_fSubFlashNum += m_fSubNum;

	//����ɂ�������
	if (m_fSubFlashNum >= 1.0f)
	{
		m_fSubFlashNum = 1.0f;
		m_bDisappearFlag = true;
	}
	else if (m_fSubFlashNum <= 0.0f)
	{
		m_fSubFlashNum = 0;
		m_fSubNum *= -1;
	}

}

//*****************************************************************************
// �t�F�[�h�A�E�g
//*****************************************************************************
void CScene2D::FadeOut(float fSpeed)
{
	//���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//�����x�̒l
	m_fSubFlashNum += fSpeed;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�A���t�@�l�𑫂�
	GetColor().a = m_fSubFlashNum;

	//�J���[���̍X�V
	D3DXCOLOR color = GetColor();

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	// �����l�������Ȃ�����
	if (m_fSubFlashNum > 1.0f)
	{
		m_fSubFlashNum = 1.0f;
		m_bFadeOut = false;
	}
}

//*****************************************************************************
//�i���o�[�A�j���[�V�����֐�
//*****************************************************************************
void CScene2D::NumberAnimation(int nNumber)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	//���_�o�b�t�@�����b�N
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 1.0f);

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//*****************************************************************************
//�F���i�[�֐�
//*****************************************************************************
void CScene2D::SetCol(D3DXCOLOR col)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

	//�F�̐ݒ�
	SetColor(col);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�(0~255�̐��l�Őݒ�)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,a��0~255�͈̔͂Ō��߂邱��
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:���b�h g:�O���[���@b:�u���[
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //a�́A�����x��\���Ă���
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//*****************************************************************************
//��]���i�[�֐�
//*****************************************************************************
void CScene2D::SetRotation(float rotasion)
{
	//���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// ��]�̒l�����Z
	rotasion += m_fRotasion;

	float r = sqrtf(powf(size.x / 2, 2.0) + powf(size.x / 2, 2.0));	//���a

	float fTheta = atan2(size.x / 2, size.x / 2);					//�V�[�^

	float XAngle = r * cos(fTheta + rotasion);	//X�̊p�x
	float YAngle = r * sin(fTheta + rotasion);	//X�̊p�x

	// ���_����ݒ�
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// �o�b�t�@�擾

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[1].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[2].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[3].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();

	//��]��
	m_fRotasion += 0.01;
}

//*****************************************************************************
//�g����֐�
//*****************************************************************************
void CScene2D::SetScale(const float & fScale)
{
	m_fScaleNum = fScale;
}
