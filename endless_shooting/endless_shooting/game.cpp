//*****************************************************************************
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���F �N
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
#include "game.h"
#include "bg.h"
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "number.h"
#include "ui.h"
#include "bulletUI.h"
#include "fade.h"
#include "combo.h"
#include "comboUI.h"
#include "speed.h"
#include "combobonus.h"
#include "combobonusUI.h"
#include <time.h>

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CGame::GAMESTATE	CGame::m_GameState = {};	//�Q�[�����
int					CGame::m_nNumEnemy = NULL;	//�G�̕\����

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_nNumEnemy = 0;			//�G�̉�ʏ�̐�
	m_WholeEnemy = 0;			//�X�s�[�h�A�b�v�܂ł̓G�̐�
	m_GameSpeed = 5;			//�G�̃X�s�[�h
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CGame * CGame::Create()
{
	CGame *pGame = NULL;
	if (pGame == NULL)
	{
		pGame = new CGame;
		pGame->Init();
	}
	return pGame;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CGame::Init()
{

	srand((unsigned int)time(NULL));					//�����̏�����
	m_pSound = CManager::GetSound();					//�T�E���h�̏����擾
#if DEBUG_SOUND
	m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);	//�Q�[��BGM�𗬂�
#endif // DEBUG_SOUND
	m_GameState = GAMESTATE_NORMAL;						//�Q�[����ʂ̏�Ԃ͒ʏ���
	m_nNumEnemy = 0;									//��ʂɌ����G�̃J�E���g
	m_WholeEnemy = 0;									//�X�s�[�h�A�b�v�܂ł̓G�̃J�E���g
	POINT posPoint;										//�}�E�X�����擾
	GetCursorPos(&posPoint);							// �}�E�X���W���擾����
	m_pBg = CBg::Create();								//�w�i�̐���
	m_pBulletUI = CBulletUI::Create();					//�c�e�̐���
	m_pScore = CScore::Create();						//�X�R�A�̐���	
	m_pFade = CFade::Create();							//�t�F�[�h�̐���
	m_pCombo = CCombo::Create();						//�R���{�̐���

	//�G�̐���
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),
		D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0),
		CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),
		D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0),
		CEnemy::ENEMYTYPE_NORMAL);

	//�^�[�Q�b�g�}�[�J�[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f),
		D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0));

	//UI�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(SCOREUI_POSX, SCOREUI_POSY, 0),
		D3DXVECTOR3(SCOREUI_SIZEX, SCOREUI_SIZEY, 0),
		CUi::UITYPE_SCORE);

	//�X�R�AUI�̐���
	m_pComboUI = CComboUI::Create(D3DXVECTOR3(COMBOUI_POSX, COMBOUI_POSY, 0),
		D3DXVECTOR3(COMBOUI_SIZEX, COMBOUI_SIZEY, 0));
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CGame::Uninit(void)
{
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CGame::Update(void)
{
	m_pBg->Update();					//�w�i�̍X�V
	m_pFade->Update();					//�t�F�[�h�̍X�V
	m_pCombo->ComboAction();			//�R���{�A�N�V����
	m_pComboUI->Update();				//�R���{�A�N�V����

	//�Q�[����ʂ̏��
	switch (m_GameState)
	{
	//�ʏ��Ԃ̏ꍇ
	case GAMESTATE_NORMAL:
		//��ʏ�̓G���|����Čv10�̓|����Ă��Ȃ��ꍇ
		if (m_nNumEnemy >= MAX_ENEMY && m_WholeEnemy != 10)
		{
			m_pBulletUI->Loading();					//�c�e�̐���
			m_nNumEnemy = 0;						//��ʏ�̓G�̐������Z�b�g
			//�G�l�~�[�̐���
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);
		}
		//10�̂܂ł������ꍇ
		else if (m_WholeEnemy == 10)
		{
			m_GameState = GAMESTATE_SPEEDUP;		//�Q�[����ʂ̏�Ԃ��X�s�[�h�A�b�v�ɂ���
			m_pScore->AddScore(2500);				//2500�_�̃X�R�A�{�[�i�X�����_����
			//�X�s�[�h�A�b�v��UI��\��
			m_pSpeedUI = CSpeed::Create(D3DXVECTOR3(SPEEDUP_POS_X, SPEEDUP_POS_Y, 0), 
									D3DXVECTOR3(SPEEDUP_SIZE_X, SPEEDUP_SIZE_Y, 0));
			m_pSpeedUI->CSpeed::SetbUse(true);		//�X�s�[�h�A�b�v�̓_�ŕ\��
		}
		if (m_pCombo->GetbCombo() == true)
		{
			m_pComboBonus = NULL;
			m_pComboBonusUI = NULL;
			break;
		}
		else if (m_pCombo->GetbCombo() == false && m_pCombo->GetSocreCombo() > 0)
		{
			if (m_pComboBonus == NULL && m_pComboBonusUI == NULL)
			{
				m_pComboBonus = CComboBonus::Create();		//�R���{�X�R�A�̐���
				m_pComboBonusUI = CComboBonusUI::Create(D3DXVECTOR3(750, SCOREUI_POSY , 0),
				D3DXVECTOR3(SCOREUI_SIZEX*1.5, SCOREUI_SIZEY*1.5, 0));		//�R���{�X�R�A�̐���

			}
			else if (m_pComboBonus != NULL && m_pComboBonusUI != NULL)
			{
				m_pComboBonus->SetScore(m_pCombo->GetSocreCombo());
				m_pComboBonus->Update();
			}
			break;
		}
		break;

	//�X�s�[�h�A�b�v�̏�Ԃ̏ꍇ
	case GAMESTATE_SPEEDUP:
		//�X�s�[�h�A�b�v��UI�_�ŃI��
		if (m_pSpeedUI->GetbUse() == true)
		{
			m_pSpeedUI->CSpeed::Update();			//�X�s�[�hUI�̍X�V����
		}
		//�X�s�[�h�A�b�v��UI�_�ŃI�t
		else if (m_pSpeedUI->GetbUse() == false)
		{
			m_GameState = GAMESTATE_NORMAL;			//�ʏ��Ԃɂ���
			m_GameSpeed += 5;						//�G�̃X�s�[�h�A�b�v
			m_WholeEnemy = 0;						//�X�s�[�h�A�b�v�܂ł̓G�̐�
		}
		break;

	//�G��|�����Ƃ��̏��
	case GAMESTATE_ENEMYBREAK:
		m_nNumEnemy++;								//�G���J�E���g
		m_WholeEnemy++;								//�X�s�[�h�A�b�v�܂ł̓G���J�E���g
		m_pScore->AddScore(200);					//�G��|�����Ƃ��̃X�R�A
		m_GameState = GAMESTATE_NORMAL;				//�Q�[���̏�Ԃ�ʏ�ɂ���
		break;

	//�Q�[���̏�Ԃ��I�����ɂ���
	case GAMESTATE_END:
		//�t�F�[�h�̏�Ԃ�MAX�ɂ���
		if (CFade::GetFade() == (CFade::FADESTATE_MAX))
		{
			m_pFade->CFade::SetFade(CFade::FADESTATE_IN);			//�t�F�[�h�̏�Ԃ��t�F�[�h�C���ɂ���
		}
		//�t�F�[�h�̏�Ԃ�NONE�ɂ���
		if (CFade::GetFade() == (CFade::FADESTATE_NONE))
		{
			#if DEBUG_SOUND
			//�T�E���h��~
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);		//�T�E���h���~�߂�
			#endif // DEBUG_SOUND
			CManager::SetMode(CManager::MODE_RESULT);				//�Q�[����ʂ��烊�U���g��ʂɑJ�ڂ���
		}
		break;

	default:
		break;
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CGame::Draw(void)
{

}

//*****************************************************************************
//�����擾�ʒu�֐�
//*****************************************************************************
D3DXVECTOR3 CGame::GetRandPos(void)
{
	// �ϐ��錾
	D3DXVECTOR3 returnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ԃ��l
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	// Random�Ȓl�𓾂�
	fPosX = (SCREEN_WIDTH / 2) + ((float)(rand() % 1000000) 
				/100.0f - (float)(rand() % 1000000) / 100.0f);
	fPosY = (SCREEN_HEIGHT / 2) + ((float)(rand() % 50000) 
				/ 100.0f - (float)(rand() % 50000) / 100.0f);
	
	returnPos = D3DXVECTOR3(fPosX, fPosY, 0.0f);		// �Ԃ��ʒu�Ɍ��ѕt����

	return returnPos;
}

//*****************************************************************************
//�����擾�����֐�
//*****************************************************************************
D3DXVECTOR3 CGame::GetRandMove(void)
{
	// �ϐ��錾
	D3DXVECTOR3 returnMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ԃ��l
	float fAngle = 0.0f;

	// Random�Ȋp�x�𓾂�
	fAngle = (float)(rand() % 314) / 100.0f - (float)(rand() % 314) / 100.0f;

	// �Ԃ��ړ��ʂɌ��ѕt����
	returnMove = D3DXVECTOR3(sinf(fAngle)*m_GameSpeed, cosf(fAngle)*m_GameSpeed, 0.0f);

	return returnMove;
}
