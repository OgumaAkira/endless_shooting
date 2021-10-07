//*****************************************************************************
//
// �}�l�[�W���[���� [manager.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"		//�}�l�[�W���[�̃w�b�^
#include "input.h"			//���͂̃w�b�^�[
#include "renderer.h"		//�����_���[�̃w�b�^�[
#include "scene.h"			//�V�[���̃w�b�^�[
#include "player.h"			//�v���C���[(�^�[�Q�b�g�}�[�J)�̃w�b�^�[
#include "bg.h"				//�w�i�̃w�b�^�[
#include "button.h"			//�{�^���̃w�b�^�[
#include "sound.h"			//�T�E���h�̃w�b�^�[
#include "explosion.h"		//�����̃w�b�^�[
#include "enemy.h"			//�G�̃w�b�^�[
#include "number.h"			//�����̃w�b�^�[
#include "score.h"			//�X�R�A�l�̃w�b�^�[
#include "title.h"			//�^�C�g����ʂ̃w�b�^�[
#include "game.h"			//�Q�[����ʂ̃w�b�^�[
#include "result.h"			//���U���g��ʂ̃w�b�^�[
#include "pause.h"			//�|�[�Y��ʂ̃w�b�_�[
#include "fade.h"			//�t�F�[�h�̃w�b�^�[
#include "bulletUI.h"		//�c�e�̃w�b�^�[
#include "speed.h"			//�X�s�[�hUI�̃w�b�_�[
#include "ui.h"				//UI�̃w�b�^�[
#include "combo.h"			//�R���{�̃w�b�^�[
#include "combobonusUI.h"	//�R���{�{�[�i�X�̃w�b�^�[
#include "comboUI.h"		//�R���{UI�̃w�b�^�[
#include "effect.h"			//�G�t�F�N�g

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CRenderer		*CManager::m_pRenderer				= NULL;	//�����_�����O�̃|�C���^
CScene2D		*CManager::m_paScene[MAX_TEXTURE]	= {};	//�V�[���̃|�C���^
CInputKeyboard	*CManager::m_pInputKeyboard			= NULL;	//�L�[�{�[�h���͂̃|�C���^7
CMouse			*CManager::m_pMouse					= NULL;	//�G�l�~�[�̃|�C���^
CPlayer			*CManager::m_pPlayer				= NULL;	//�v���C���[�̃|�C���^
CEnemy			*CManager::m_pEnemy					= NULL;	//�v���C���[�̃|�C���^
CSound			*CManager::m_pSound					= NULL;	//�T�E���h�̃|�C���^
CExplosion		*CManager::m_pExplosion				= NULL;	//�G�N�X�v���[�W�����̃|�C���^
CBullet			*CManager::m_pBullet				= NULL;	//�o���b�g�̃|�C���^
CButton			*CManager::m_pButton				= NULL; //�{�^���̃|�C���^
CTitle			*CManager::m_pTitle					= NULL;	//�^�C�g���̃|�C���^
CGame			*CManager::m_pGame					= NULL;	//�Q�[���̃|�C���^
CResult			*CManager::m_pResult				= NULL;	//�o���b�g�̃|�C���^
CPause			*CManager::m_pPause					= NULL;	//�|�[�Y�̃|�C���^
CFade			*CManager::m_pFade					= NULL;	//�t�F�[�h�̃|�C���^
CNumber			*CManager::m_pNumber				= NULL;	//�i���o�[�̃|�C���^
CScore			*CManager::m_pScore					= NULL;	//�X�R�A�̃|�C���^
CCombo			*CManager::m_pCombo					= NULL;	//�R���{�̃|�C���^
CSpeed			*CManager::m_pSpeed					= NULL;	//�X�s�[�hUI�̃|�C���^
CUi				*CManager::m_pUi					= NULL;	//UI�̃|�C���^
CComboUI		*CManager::m_pComboUI				= NULL;	//�R���{UI�̃|�C���^
CComboBonus		*CManager::m_pComboBonus			= NULL;	//�R���{�X�R�A�̃|�C���^
CComboBonusUI	*CManager::m_pComboBonusUI			= NULL;	//�R���{�X�R�A�̃|�C���^
CManager::MODE	 CManager::m_mode					= CManager::MODE_TITLE;	//�������[�h

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu)
{
	//�����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hInstance, hWnd, TRUE);

	//�L�[�{�[�h���͂̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�}�E�X���͂̐���
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);

	//�T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->InitSound(hWnd);
	//�^�[�Q�b�g�}�[�J�[�̐���

	//�v���C���[�̃e�N�X�`�����[�h
	CPlayer::Load();

	//�G�l�~�[�̃e�N�X�`�����[�h
	CEnemy::Load();

	//�o���b�g�̃e�N�X�`�����[�h
	CBullet::Load();

	//�����̃e�N�X�`�����[�h
	CExplosion::Load();
	
	//�{�^���̃e�N�X�`�����[�h
	CButton::Load();

	//�i���o�[�̃��[�h
	CNumber::Load();

	//�w�i�̃e�N�X�`�����[�h
	CBg::Load();

	//�c�e�̃e�N�X�`�����[�h
	CBulletUI::Load();

	//�t�F�[�h�̃e�N�X�`�����[�h
	CFade::Load();

	//�X�s�[�hUI�̃|�C���^
	CSpeed::Load();

	//�R���{UI�̃e�N�X�`�����[�h
	CComboUI::Load();

	//�R���{�{�[�i�XUI�̃A�����[�h
	CComboBonusUI::Load();

	//UI�̃e�N�X�`�����[�h
	CUi::Load();

	//�G�t�F�N�g�̃e�N�X�`�����[�h
	CEffect::Load();

	//���[�h�̏����i�[����
	SetMode(m_mode);

	return S_OK;
}
//*****************************************************************************
// �I������
//*****************************************************************************
void CManager::Uninit(void)
{
	//�V�[���̔j��
	CScene::ReleaseAll();

	//�v���C���[�̃A�����[�h
	CPlayer::UnLoad();

	//�G�l�~�[�̃A�����[�h
	CEnemy::UnLoad();

	//�o���b�g�̃A�����[�h
	CBullet::UnLoad();

	//�����̃A�����[�h
	CExplosion::UnLoad();

	//�{�^���̃A�����[�h
	CButton::UnLoad();

	//�i���o�[�̃��[�h
	CNumber::UnLoad();

	//�w�i�̃A�����[�h
	CBg::UnLoad();

	//�c�e�̃A�����[�h
	CBulletUI::UnLoad();

	//�t�F�[�h�̃A�����[�h
	CFade::UnLoad();

	//�X�s�[�hUI�̃A�����[�h
	CSpeed::UnLoad();

	//�R���{UI�̃A�����[�h
	CComboUI::UnLoad();

	//�R���{�{�[�i�XUI�̃A�����[�h
	CComboBonusUI::UnLoad();

	//UI�̃A�����[�h
	CUi::UnLoad();

	//�G�t�F�N�g�̃A�����[�h
	CEffect::UnLoad();

	//�L�[�{�[�h���͔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X���͔j��
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//�T�E���h�j��
	//if (m_pSound != NULL)
	//{
	//	m_pSound->StopSoundTo();
	//	delete m_pSound;
	//	m_pSound = NULL;
	//}
	//�����_���[�j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CManager::Update(void)
{
	//���͂̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//�}�E�X�̍X�V����
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	//�����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//���[�h���
	switch (m_mode)
	{
		//�^�C�g�����
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->CTitle::Update();
		}
		break;
		//�Q�[�����
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->CGame::Update();
		}
		break;

		//�|�[�Y���
	case MODE_PAUSE:
		//�|�[�Y��ʂ��o��
		if (m_pPause != NULL)
		{
			m_pPause->CPause::Update();
		}
		break;

		//���U���g���
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->CResult::Update();
		}
		break;

	default:
		break;
	}
 }

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}
//*****************************************************************************
//���[�h���i�[�֐�
//*****************************************************************************
void CManager::SetMode(MODE mode)
{
	m_mode = mode;	//���[�h�̒l���i�[

	switch (m_mode)
	{
		//�^�C�g����ʑJ��
	case MODE_TITLE:
		//���U���g��ʂ�������
		if (m_pResult != NULL)	
		{
			m_pResult->CResult::Uninit();	
			CScene::ReleaseAll();
			m_pResult = NULL;
		}
		if (m_pGame != NULL)
		{
			m_pPause->CPause::Uninit();
			m_pGame->CGame::Uninit();
			CScene::ReleaseAll();
			m_pGame = NULL; 
			m_pPause = NULL;
		}
		//�^�C�g����ʂ��o��
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
			//���[�h�J��
		}
		break;
		
		//�Q�[����ʑJ��
	case MODE_GAME:
		//�^�C�g����ʂ�������
		if (m_pTitle != NULL)
		{
			m_pTitle->CTitle::Uninit();
			CScene::ReleaseAll();
			m_pTitle = NULL;
		}
		//�Q�[����ʂ��o��
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		if (m_pPause != NULL)
		{
			m_pPause->CPause::Uninit();
			CScene::Select(6);
			m_pPause = NULL;
		}
		break;

		//�|�[�Y��ʑJ��
	case MODE_PAUSE:
		//�|�[�Y��ʂ��o��
		if (m_pPause == NULL)
		{
			m_pPause = CPause::Create();
		}
		break;

		//���U���g��ʑJ��
	case MODE_RESULT:
		//�Q�[����ʂ�������
		if (m_pGame != NULL)
		{
			m_pGame->CGame::Uninit();
			CScene::ReleaseAll();
			m_pGame = NULL;
		}
		//���U���g��ʂ��o��
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	default:
		break;
	}
}
