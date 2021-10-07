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

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"
#include "input.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pTexture		= NULL;				//�e�N�X�`���̏��
	m_pVtxBuff		= NULL;				//���_�o�b�t�@�̏��
	m_pos			= VECTOR_DEFAULT;	// �|���S���̈ʒu
	m_size			= VECTOR_DEFAULT;	// �|���S���̑傫��
	m_tex			= AT_VECTOR_A;		//�e�X�N�`��A
	m_tex2			= AT_VECTOR_B;		//�e�X�N�`��B
	m_color			= COLOR_DEFAULT;	//�J���[
	m_nCounterAnim	= 0;				//�A�j���[�V�����J�E���g
	m_nPatternAnim	= 0;				//�A�j���[�V�����p�^�[��No.

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
CScene2D * CScene2D::Create()
{
	CScene2D *pScene2D = NULL;

	//�V�[��2D�̃|�C���^���������������ꍇ
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CScene2D::Init(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���_����ݒ�
	VERTEX_2D *pVtx;


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//�E��

	for (int nCntInit = 0; nCntInit < POLYGON_CNT; nCntInit++)
	{
		pVtx[nCntInit].rhw = 1.0f;				//rhw�̐ݒ�
		pVtx[nCntInit].col = D3DXCOLOR(m_color);//�J���[�̐ݒ�
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScene2D::Update(void)
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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);//����
	pVtx[1].tex = D3DXVECTOR2(m_tex2.x, m_tex.y);//�E��
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex2.y);//����
	pVtx[3].tex = D3DXVECTOR2(m_tex2.x, m_tex2.y);//�E��

	for (int nCntUpdata = 0; nCntUpdata < POLYGON_CNT; nCntUpdata++)
	{
		
		pVtx[nCntUpdata].rhw = 1.0f;				//rhw�̐ݒ�
		pVtx[nCntUpdata].col = D3DXCOLOR(m_color);	//�J���[�̐ݒ�
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �A���t�@�u�����f�B���O���s�Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O�X�e�[�g��ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

	//�e�N�X�`���X�e�[�W�F�A���t�@�v�f�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);

}

//*****************************************************************************
// �e�N�X�`�����i�[�֐�
//*****************************************************************************
void CScene2D::SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_tex = tex;
	m_tex2 = D3DXVECTOR2(tex2.x + 1.0f, tex2.y + 1.0f);
	pVtx[0].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex.y + 0.0f);	//����
	pVtx[1].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex.y + 0.0f);	//�E��
	pVtx[2].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex2.y + 1.0f);	//����
	pVtx[3].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex2.y + 1.0f);	//�E��
 
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// �A�j���[�V�����e�N�X�`���֐�
//*****************************************************************************
void CScene2D::AnimationTexture(OBJTYPE objType, int PatternAnim, int CounterAnim)
{
	//TEXTURE��PRIORITY���ő吔�܂ŃJ�E���g���񂷁B
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			//�V�[���̃|�C���^�̒��g���������ꍇ
			if (pScene != NULL)
			{
				 OBJTYPE ObjType = pScene->GetObjType();
				//�I�u�W�F�N�g�^�C�v�w��
				if (ObjType == objType)
				{
					//�A�j���[�V�����J�E���g�̐��l�܂ōs�����ꍇ
					if (m_nCounterAnim == CounterAnim)
					{
						m_nPatternAnim++;
						SetTex(D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0),
							D3DXVECTOR2(m_nPatternAnim * 0.125f - 1.0f, 0));
						m_nCounterAnim = 0;
					}
					m_nCounterAnim++;
					//�A�j���[�V�����p�^�[�����ő�l�܂ł�������
					if (m_nPatternAnim > PatternAnim)
					{
						Uninit();
					}
				}
			}
		}
	}
}
