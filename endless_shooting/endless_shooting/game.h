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
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "mode_base.h"
#include "scene2d.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPlayer;

//*****************************************************************************
//�Q�[����ʂ̃N���X�錾
//*****************************************************************************
class CGame : public CScene2D
{
public:
	//�\���̒�`(���)
	enum GAMESTATE
	{
		GAMESTATE_NONE = 0,		//�����Ȃ����
		GAMESTATE_SPEEDUP,		//�G���x���グ��
		GAMESTATE_NORMAL,		//�ʏ���
		GAMESTATE_ENEMYBREAK,	//�G��|������
		GAMESTATE_END,			//���U���g���
		GAMESTATE_FINISH,		//�Q�[���I�����(��ʑJ�ڊJ�n�҂���ԁj
		GAMESTATE_MAX			//�ő吔
	};

	CGame();										 //�R���X�g���N�^
	~CGame();														 //�f�X�g���N�^
																	 
	//�����o�֐�													    
	static CGame *Create();											 //�N���G�C�g
	virtual void Init(CMode *pMode);							//�������֐�
	virtual void Update(CMode *pMode);						//�X�V�֐�
	virtual void Uninit(void);						//�I���֐�
	void Draw(void);												 //�X�V����
	static void SetGameState(GAMESTATE state) {m_GameState = state;} //�Q�[����Ԑݒ�
	static GAMESTATE GetGameState(void)		  { return m_GameState;} //�Q�[����Ԏ擾
	D3DXVECTOR3 GetRandPos(void);									 //�G�̗����z�u�ʒu�擾�֐�
	D3DXVECTOR3 GetRandMove(void);									 //�G�̗����z�u�����擾�֐�

private:
	//�����o�ϐ�
	static GAMESTATE	m_GameState;			//���
	CPlayer				*m_pPlayer;				//�v���C���[�̃|�C���^	
	float				m_GameSpeed;			//�Q�[���X�s�[�h
};
#endif