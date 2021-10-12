//*****************************************************************************
//
// �|�[�Y��ʂ̏��� [pause.cpp]
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
#include "score.h"
#include "manager.h"
#include "result.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "button.h"
#include "fade.h"
#include "hiscore.h"
#include "ui.h"
#include "pause.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CPlayer			*CPause::m_pPlayer = NULL;		//�v���C���[�̃|�C���^
CBg				*CPause::m_pBg = NULL;			//�w�i�̃|�C���^
CFade			*CPause::m_pFade = NULL;		//�t�F�[�h�̃|�C���^
CButton			*CPause::m_pButton = NULL;		//�{�^���̃|�C���^
CUi				*CPause::m_pUi = NULL;			//�n�C�X�R�AUI

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPause::CPause(int nPriority) : CScene(nPriority)
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CPause * CPause::Create()
{
	CPause *pPause = NULL;
	if (pPause == NULL)
	{
		pPause = new CPause;
		pPause->Init();
		pPause->SetObjType(OBJTYPE_PAUSE);
	}
	return pPause;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CPause::Init()
{
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0),
		D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_PAUSETITLE);
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY/1.5f, 0),
		D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_PAUSEGAME);

	//�|�[�Y��ʂ�UI
	m_pButton = CButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),
								D3DXVECTOR3(900, 900, 0), CButton::BUTTONTYPE_PAUSE);

	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CPause::Uninit(void)
{
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CPause::Update(void)
{
#if DEBUG_SOUND
	//�T�E���h��~	
	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);			//�T�E���h���~�߂�
#endif // DEBUG_SOUND
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CPause::Draw(void)
{
}
