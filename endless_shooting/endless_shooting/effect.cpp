//*****************************************************************************
//
// �����̏��� [explosion.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define EFFECT_COUNTERANIM	(1)									//�A�j���[�V�����J�E���^�[
#define EFFECT_PATTERNANIM	(16)								//�A�j���[�V����No.
#define EFFECT_ALPHATHIN	(0.03f)								//�J���[�𔖂�����(�A���t�@�l����)
#define BULLET_TEXTURE	("data/TEXTURE/YellowParticle.png")		//�����e�N�X�`��

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CEffect::m_pTexture = NULL;		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEffect::CEffect()
{	
	m_move = VECTOR3_DEFAULT;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEffect::~CEffect()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move, int type)
{
	CEffect *pEffect;
	pEffect = NULL;
	//�G�̃|�C���^�������Ȃ������ꍇ
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		if (type == 1)
		{	
				pEffect->Smoke(pos, size, move, col);
		}		
		pEffect->SetObjType(OBJTYPE_EFFECT);	//�I�u�W�F�N�g�w��
	}
	return pEffect;
}

//*****************************************************************************
//�����o�֐�
//*****************************************************************************
void CEffect::Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{

		//�G�t�F�N�g�̐ݒ�
		float fAngle = (rand() % 314 / 100.0f)*(rand() % 100);	//�p�x�v�Z
		D3DXVECTOR3 actualMove = D3DXVECTOR3((float)sin(fAngle)*move.x,
											(float)cos(fAngle)*move.y, 0.0f);//�ړ��������Z�b�g
		//�����̏����ݒ�

		m_move = actualMove;				//�ړ���
		SetColor(col);						//�F�i�[
		//BirdTexture(m_pTexture);			//�e�N�X�`���̏���scene2d�Ɏ����Ă�
		Init(pos, size);
}

//*****************************************************************************
//�����o�֐�
//*****************************************************************************
void CEffect::ClickEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{

	//�G�t�F�N�g�̐ݒ�
	float fAngle = (rand() % 314 / 100.0f)*(rand() % 100);	//�p�x�v�Z
	D3DXVECTOR3 actualMove = -D3DXVECTOR3((float)sin(fAngle)*move.x, 
										(float)cos(fAngle)*move.y, 0.0f);//�ړ��������Z�b�g
	//�e�̏����ݒ�
	m_move = actualMove;				//�ړ���
	SetColor(col);						//�F�i�[
	//BirdTexture(m_pTexture);			//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	Init(pos, size);
}
//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CEffect::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,BULLET_TEXTURE, &m_pTexture);
	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CEffect::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//�X�V�ʒu���擾
	D3DXVECTOR3 size = GetSize();				//�X�V�T�C�Y���擾
	D3DXCOLOR	col = GetColor();				//�X�V�J���[���擾

	pos += m_move;		//�ړ��ʂ��v���X����
	col -= D3DXCOLOR(0, EFFECT_ALPHATHIN, EFFECT_ALPHATHIN, EFFECT_ALPHATHIN);
	
	SetPos(pos);	//�ʒu�i�[
	SetSize(size);		//�T�C�Y�i�[
	SetColor(col);		//�J���[�i�[

	CScene2D::Update();

	//�����Ȃ��Ȃ��������
	if (col.a < 0)
	{
		Uninit();
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CEffect::Draw(void)
{
	CScene2D::Draw();
}
