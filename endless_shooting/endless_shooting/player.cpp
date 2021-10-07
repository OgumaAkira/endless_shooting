//*****************************************************************************
//
// �v���C���[�̏��� [player.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "player.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer(int nPriority) :CScene2D(nPriority)
{
	m_pos = VECTOR_DEFAULT;				// �|���S���̈ʒu
	m_size = VECTOR_DEFAULT;				// �|���S���傫��
	m_nColor = 0;								// �|���S���̐F
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CPlayer::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CPlayer::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer = NULL;
	//�v���C���[�̃|�C���^���������������ꍇ
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init(pos, size);
	}
	return pPlayer;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x,pos.y , 0);		//�ʒu
	SetPosition(pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(size);
	SetObjType(OBJTYPE_CURSOR);					//�I�u�W�F�N�g�w��i�[
	BirdTexture(m_pTexture);					//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	return S_OK;;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CPlayer::Update(void)
{
	POINT posPoint;
	GetCursorPos(&posPoint);											//�}�E�X���W���擾����
	m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//�ʒu
	Range();															//�ړ��͈�
	CSound *pSound = CManager::GetSound();								//�T�E���h���擾
	CScene2D::Update();													//�I�u�W�F�N�g�̍X�V�����̎擾
	MarkerColor();														//�}�[�J�[�̐F�ς�
	MarkerObject();														//�}�[�J�[�̃I�u�W�F�N�g�؂�ւ�
	PlayerInput();														
	SetPosition(m_pos);													//�v���C���[�̈ʒu�s�i
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//�}�[�J�[�J���[�֐�
//*****************************************************************************
void CPlayer::MarkerColor(void)
{
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		bool bHit = false;		//����Ȃ�
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			//�V�[���̏��擾
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			//�V�[���ɏ�񂪓����Ă�ꍇ
			if (pScene != NULL)
			{
				//�I�u�W�F�N�g�̏��擾
				OBJTYPE objType = pScene->GetObjType();

				//�G�̓����蔻��
				if (objType == OBJTYPE_ENEMY
					&& CManager::GetMode() == CManager::MODE_GAME
					&& CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
				{
					CEnemy *pEnemy = CManager::GetEnemy();						//�G�̏����擾
					CScene2D *pScene2d = (CScene2D*)pScene;						//�L���X�g
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//�ʒu���擾
					D3DXVECTOR3 size = pScene2d->GetSize();						//�傫�����擾

					//�G�ƃ}�[�J�[�̏Ə�
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						//�������ꍇ��
						SetColor(MARKERCOLOR_RED);				//�F��Ԃɕω�
						bHit = true;											//���肠��
					}
					else
					{
						//�����ĂȂ��ꍇ���F
						SetColor(MARKERCOLOR_YELLOW);			//���̐F�ɖ߂�
					}
				}
				//�{�^���̓����蔻��
				if (objType == OBJTYPE_BUTTON && CManager::GetMode() == CManager::MODE_PAUSE)
				{
					CButton *pButton = CManager::GetButton();					//�G�̏����擾
					CScene2D *pScene2d = (CScene2D*)pScene;						//�L���X�g
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//�ʒu���擾
					D3DXVECTOR3 size = pScene2d->GetSize();						//�傫�����擾

					//�{�^���ƏƏ�����������
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						SetColor(MARKERCOLOR_RED);	//�F��Ԃɕω�
						bHit = true;				//���肠��
					}
					else
					{
						SetColor(MARKERCOLOR_YELLOW);//���̐F�ɖ߂�
					}
				}
			}
		}
		//�G�ƏƏ�����������
		if (bHit == true)
		{
			break;
		}
	}
}

//*****************************************************************************
//�ړ������֐�
//*****************************************************************************
void CPlayer::Range(void)
{
	//��͈̔�
	if (m_pos.y - (m_size.y / 2) <= 0)
	{
		m_pos.y += RANGE_MAX;
	}
	//���͈̔�
	if (m_pos.y + (m_size.y / 2) >= SCREEN_HEIGHT)
	{
		m_pos.y -= RANGE_MAX;
	}
	//�E�͈̔�
	if (m_pos.x - (m_size.x ) <= 0)
	{
		m_pos.x += RANGE_MAX;
	}
	//���͈̔�
	if (m_pos.x + (m_size.x / 2) >= SCREEN_WIDTH)
	{
		m_pos.x -= RANGE_MAX;
	}
}

//*****************************************************************************
//���@���͊֐�
//*****************************************************************************
void CPlayer::PlayerInput(void)
{
	m_pInput = CManager::GetMouse();									//�}�E�X�̓��͏��擾
	//�E�N���b�N����͂��A���Q�[����ʂ������ꍇ
	if (((CMouse*)m_pInput)->GetMousePrees(1) == true && CManager::GetMode() == CManager::MODE_GAME)
	{
		CManager::SetMode(CManager::MODE_PAUSE);
	}
	//���N���b�N����͂����Əꍇ
	else if (((CMouse*)m_pInput)->GetMouseTrigger(0) == true)
	{
		//�Q�[����ʂ��I�u�W�F�N�g���v���C���[���t�F�[�h�l���ő�ł���ꍇ
		if (CManager::GetMode() == CManager::MODE_GAME&&
			GetObjType() == OBJTYPE_PLAYER&&
			CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//�e�̐���
			CBullet::Create(D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0),
				D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_PLAYER);

			//�T�E���h
#if DEBUG_SOUND
			CSound *pSound = CManager::GetSound();		//�T�E���h���擾
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
#endif // DEBUG_SOUND
		}
		//�Q�[����ʈȊO�ŃI�u�W�F�N�g���J�[�\�����t�F�[�h�l���ő�ł���ꍇ
		else if (CManager::GetMode() != CManager::MODE_GAME&&
			GetObjType() == OBJTYPE_CURSOR&&
			CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//�e�̐���
			CBullet::Create(D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0),
				D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0),
				D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_CURSOR);
		}
	}

}

//*****************************************************************************
//�I�u�W�F�N�g�w��֐�
//*****************************************************************************
void CPlayer::MarkerObject(void)
{
	//�Q�[����ʂ̏ꍇ
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		SetObjType(OBJTYPE_PLAYER);		//�v���C���[���i�[
	}
	//����ȊO�̏ꍇ
	else
	{
		SetObjType(OBJTYPE_CURSOR);		//�J�[�\�����i�[
	}
}
