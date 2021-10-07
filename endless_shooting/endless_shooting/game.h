//*****************************************************************************
//
// �Q�[����ʂ̏��� [game.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _GAME_H_	//��d�̃C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define _CRT_SECURE_WANINGS

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBg;
class CEnemy;
class CPlayer;
class CFade;
class CScore;
class CBulletUI;
class CCombo;
class CSpeed;
class CUi;
class CComboUI;
class CComboBonus;
class CComboBonusUI;

//*****************************************************************************
//�Q�[����ʂ̃N���X�錾
//*****************************************************************************
class CGame:public CScene
{
public:
	//�\���̒�`(���)
	typedef enum
	{
		GAMESTATE_NONE = 0,		//�����Ȃ����
		GAMESTATE_SPEEDUP,		//�G���x���グ��
		GAMESTATE_NORMAL,		//�ʏ���
		GAMESTATE_ENEMYBREAK,	//�G��|������
		GAMESTATE_END,			//���U���g���
		GAMESTATE_FINISH,		//�Q�[���I�����(��ʑJ�ڊJ�n�҂���ԁj
		GAMESTATE_MAX			//�ő吔

	}GAMESTATE;

	CGame(int nPriority=2) ;										 //�R���X�g���N�^
	~CGame();														 //�f�X�g���N�^
																	 
	//�����o�֐�													    
	static CGame *Create();											 //�N���G�C�g
	HRESULT Init();													 //����������
	void Uninit(void);												 //�I������
	void Update(void);												 //�X�V����
	void Draw(void);												 //�X�V����
	static int GetEnemy(void)				  { return m_nNumEnemy;} //�G�̏��i�[�֐�
	static void SetGameState(GAMESTATE state) {m_GameState = state;} //�Q�[����Ԑݒ�
	static GAMESTATE GetGameState(void)		  { return m_GameState;} //�Q�[����Ԏ擾
	D3DXVECTOR3 GetRandPos(void);									 //�G�̗����z�u�ʒu�擾�֐�
	D3DXVECTOR3 GetRandMove(void);									 //�G�̗����z�u�����擾�֐�

private:
	//�����o�ϐ�
	static GAMESTATE	m_GameState;			//���
	static int			m_nNumEnemy;			//�G�̉�ʂɌ����G�̐�
	int					m_WholeEnemy;			//�G�̃X�s�[�h�A�b�v�܂ł̐�
	int					m_GameSpeed;			//�G�̈ړ����x
	CBg					*m_pBg;					//�w�i�̃|�C���^
	CFade				*m_pFade;				//�t�F�[�h�|�C���^
	CPlayer				*m_pPlayer;				//�v���C���[�̃|�C���^
	CEnemy				*m_pEnemy;				//�G�̃|�C���^
	CSpeed				*m_pSpeedUI;			//�X�s�[�h�̃|�C���^
	CBullet				*m_pBullet;				//�e�̃|�C���^
	CScore				*m_pScore;				//�X�R�A�̃|�C���^
	CBulletUI			*m_pBulletUI;			//�c�e�̃|�C���^
	CCombo				*m_pCombo;				//�R���{�̃|�C���^
	CSound				*m_pSound;				//�T�E���h�̃|�C���^
	CComboUI			*m_pComboUI;			//�R���{UI�̃|�C���^
	CComboBonus			*m_pComboBonus;			//�R���{�X�R�A�̃|�C���^
	CComboBonusUI		*m_pComboBonusUI;			//�R���{�X�R�A�̃|�C���^
	CUi			*m_pUi;					//UI�̃|�C���^
};
#endif