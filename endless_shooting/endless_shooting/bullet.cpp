//*****************************************************************************
//
// �o���b�g���� [bullet.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define EFFECT_COUNTERANIM	(1)/								//�A�j���[�V�����J�E���^�[
#define EFFECT_PATTERNANIM	(16)								//�A�j���[�V����No.
#define EFFECT_ALPHATHIN	(0.03f)								//�J���[�𔖂�����(�A���t�@�l����)
#define BULLET_TEXTURE	("data/TEXTURE/bullet000.png")	//�����e�N�X�`��

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "bulletUI.h"
#include "effect.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		CBullet::m_pTexture = NULL;		//�e�N�X�`���̏��
CBulletUI				*CBullet::m_pBulletUI = NULL;	//�c�e�̃|�C���^

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBullet::CBullet()
{
	m_pos = VECTOR3_DEFAULT;			//�ʒu
	m_size = VECTOR3_DEFAULT;			//�傫��
	m_move = VECTOR3_DEFAULT;			//�ړ���
	m_nHP = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBullet::~CBullet()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CBullet *pBullet = NULL;

	//�o���b�g�̃|�C���^���������������ꍇ
	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		pBullet->Init(pos, size, move, type);
		pBullet->SetObjType(OBJTYPE_BULLET);	//�I�u�W�F�N�g�^�C�v�w��
	}
	return pBullet;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CBullet::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CBullet::UnLoad(void)
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
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	//�e�̏����ݒ�
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	m_size = D3DXVECTOR3(size.x, size.y, 0);//�傫���@
	m_move = move;							//�ړ���
	m_nHP = 1;								//�q�b�g�|�C���g
	m_type = type;							//�^�C�v
	BirdTexture(m_pTexture);				//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	SetObjType(CScene::OBJTYPE_BULLET);		//�I�u�W�F�N�g�^�C�v�w��
	SetPosition(m_pos);						//�����|�W�V�����w��
	SetSize(m_size);						//�����̑傫���w��
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CBullet::Uninit(void)
{
	CScene2D::Uninit();	
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CBullet::Update(void)
{
	CScene2D::Update();
	m_nHP--;	//�e�̃��C�t

	//�����蔻��
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		bool bHitEnemy = false;		//����Ȃ�
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				//�G�̓����蔻��
				if ((objType == OBJTYPE_ENEMY) && (m_type == BULLET_TYPE_PLAYER))
				{
					CEnemy *pEnemy = CManager::GetEnemy();						//�G�̏����擾
					CScene2D *pScene2d = (CScene2D*)pScene;						//�L���X�g
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//�ʒu���擾
					D3DXVECTOR3 size = pScene2d->GetSize();						//�傫�����擾

					//�G�𓖂Ă��ꍇ
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CEnemy *pEnemy = (CEnemy*)pScene;	//�L���X�g;
						pEnemy->HitDamege(1);				//�G�ւ̃_���[�W���擾
						bHitEnemy = true;					//���肠��
						break;
					}
				}
				//�{�^���̓����蔻��
				else if ((objType == OBJTYPE_BUTTON) && (m_type == BULLET_TYPE_CURSOR))
				{
					CButton *pButton = CManager::GetButton();					//�{�^���̓����蔻��
					CScene2D *pScene2d = (CScene2D*)pScene;						//�L���X�g
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//�ʒu
					D3DXVECTOR3 size = pScene2d->GetSize();						//�傫��
					
					//�{�^���̓����蔻��
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CButton *pButton = (CButton*)pScene;	//�L���X�g;
						pButton->SetButton();					//�{�^�����i�[�֐�
					}
				}
			}
		}
		//���肠��̂Ƃ�
		if (bHitEnemy == true)
		{ 
			break;
		}
	}
	//�e��������Ƃ�
	if (m_nHP <= 0)
	{
		//�^�C�v���v���C���[�̒e�ł����
		if (m_type == BULLET_TYPE_PLAYER)
		{
			//���������鐔�����[�v
			for (int nCntEffect = 0; nCntEffect < 100; nCntEffect++)
			{
				CEffect::Create(m_pos, m_size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f), 1);	//��������
			}
			m_pBulletUI->SetbUse();				//�_�ŃX�C�b�`���i�[�֐�
		}
		Uninit();								//�I���֐�
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
