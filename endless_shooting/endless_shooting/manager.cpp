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
#include "sound.h"			//�T�E���h�̃w�b�^�[
#include "resource_manager.h"	//���\�[�X�}�l�[�W���[
#include "mode_base.h"

#include "player.h"			//�v���C���[(�^�[�Q�b�g�}�[�J)�̃w�b�^�[
#include "bg.h"				//�w�i�̃w�b�^�[
#include "button.h"			//�{�^���̃w�b�^�[
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

unique_ptr<CResourceManager> CManager::m_pResourceManager = nullptr;
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
	//�������m��
	m_pResourceManager.reset(CResourceManager::GetInstace());

	//�����_���[�̐���
	if (m_pRenderer!=nullptr)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hInstance, hWnd, TRUE);
	}

	//�L�[�{�[�h���͂̐���
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;
		m_pInputKeyboard->Init(hInstance, hWnd);
	}
	//�}�E�X���͂̐���
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);

	//�T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->Init();

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

}
