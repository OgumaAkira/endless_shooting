//*****************************************************************************
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "title.h"
#include "bg.h"
#include "enemy.h"
#include "player.h"
#include "button.h"
#include "sound.h"
#include "fade.h"
#include "hiscore.h"
#include "ui.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CBg				*CTitle::m_pBg = NULL;			//�w�i�̃|�C���^
CFade			*CTitle::m_pFade = NULL;		//�t�F�[�h�̃|�C���^
CPlayer			*CTitle::m_pPlayer = NULL;		//�v���C���[�̃|�C���^
CButton			*CTitle::m_pButton = NULL;		//�{�^���̃|�C���^
CHIScore		*CTitle::m_pHiScore = NULL;		//�n�C�X�R�A
CUi				*CTitle::m_pUi = NULL;			//�n�C�X�R�AUI


//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTitle::CTitle(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CTitle * CTitle::Create()
{
	CTitle *pTitle = NULL;
	if (pTitle == NULL)
	{
		pTitle = new CTitle;
		pTitle ->Init();
		pTitle->SetObjType(OBJTYPE_TITLE);
	}
	return pTitle;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CTitle::Init()
{
	
	m_pBg = CBg::Create();		//�w�i�̃N���G�C�g
	POINT posPoint;
	GetCursorPos(&posPoint);	// �}�E�X���W���擾����
	m_bButton = true;//�X�C�b�`
	//�{�^���̐���
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0),
								D3DXVECTOR3(500.0f, 200.0f, 0.0f), 
								CButton::BUTTONTYPE_TITLE);
	//�^�C�g�����S�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.05f, SCREEN_HEIGHT / 2.5, 0),
						D3DXVECTOR3(1000, 900, 0), CUi::UITYPE_TITLELOGO);

	//�`���[�g���A���̐���
	m_pUi = CUi::Create(D3DXVECTOR3(1600, 700, 0),
						D3DXVECTOR3(500, 500, 0), CUi::UITYPE_TUTORIAL);

	//�n�C�X�R�AUI�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.5, SCORE_POS_Y + 100, 0),
						D3DXVECTOR3(300,70,0),CUi::UITYPE_HISCORE);

	//�n�C�X�R�A�̃N���G�C�g
	m_pHiScore = CHIScore::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x,(float)posPoint.y, 0),
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0));
	
	m_pFade = CFade::Create();	//�t�F�[�h�̃N���G�C�g

	
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CTitle::Uninit(void)
{
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CTitle::Update(void)
{	
	pSound = CManager::GetSound();	//�T�E���h�̏��擾
	//�X�C�b�`���I���������ꍇ
	if (m_bButton==true)
	{
#if DEBUG_SOUND
		//�^�C�g��BGM
		pSound->PlaySound(CSound::SOUND_LABEL_TITLEBGM);
#endif // DEBUG_SOUND

		m_bButton = false;
	}
	m_pFade->Update();

	//�t�F�[�h�̏�Ԃ�NONE�������ꍇ
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
#if DEBUG_SOUND
		//�T�E���h��~
		pSound->StopSound(CSound::SOUND_LABEL_TITLEBGM);
#endif // DEBUG_SOUND
		CManager::SetMode(CManager::MODE_GAME);
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CTitle::Draw(void)
{

}
