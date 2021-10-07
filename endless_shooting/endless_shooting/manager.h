//*****************************************************************************
//
// �}�l�[�W���[���� [manager.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CScene;
class CScene2D;
class CInput;
class CInputKeyboard;
class CMouse;
class CPlayer;
class CTitle;
class CResult;
class CGame;
class CFade;
class CSound;
class CScore;
class CExplosion;
class CBullet;
class CEnemy;
class CButton;
class CNumber;
class CCombo;
class CSpeed;
class CComboUI;
class CUi;
class CPause;
class CComboBonus;
class CComboBonusUI;
class CEffect;

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CManager
{
public:
	//�\����
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_PAUSE,
		MODE_END
	}MODE;

	CManager();								//�R���X�g���N�^
	~CManager();							//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu);						//�������֐�
	void Uninit(void);																//�I���֐�
	void Update(void);																//�X�V�֐�
	void Draw(void);																//�`��֐�
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }			//�����_���[�̏��擾�֐�
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h���͏��擾�֐�
	static CMouse			*GetMouse(void)			{ return m_pMouse; }			//�}�E�X���͏��擾�֐�
	static CPlayer			*GetPlayer(void)		{ return m_pPlayer; }			//�v���C���[���擾�֐�
	static CEnemy			*GetEnemy(void)			{ return m_pEnemy; }			//�G�l�~�[���擾�֐�
	static CSound			*GetSound(void)			{ return m_pSound; }			//�T�E���h���擾�֐�
	static CExplosion		*GetExplosion(void)		{ return m_pExplosion; }		//�������擾�֐�
	static CBullet			*GetBullet(void)		{ return m_pBullet; }			//�o���b�g���擾�֐�
	static CButton			*GetButton(void)		{ return m_pButton; }			//�{�^�����擾�֐�
	static CScore			*GetScore(void)			{ return m_pScore; }			//�X�R�A�擾�֐�
	static CFade			*GetFade(void)			{ return m_pFade; }				//�t�F�[�h�擾�֐�
	static CCombo			*GetCombo(void)			{ return m_pCombo; }			//�R���{�擾�֐�
	static CSpeed			*GetSpeed(void)			{ return m_pSpeed; }			//�X�s�[�hUI�擾�֐�
	static CUi				*GetUi(void)			{ return m_pUi; }				//UI�擾�֐�
	static CComboUI			*GetComboUI(void)		{ return m_pComboUI; }			//�R���{UI�擾�֐�
	static CComboBonus		*GetComboBonus(void)	{ return m_pComboBonus; }		//�R���{�X�R�A�擾�֐�
	static CComboBonusUI	*GetComboBonusUI(void)	{ return m_pComboBonusUI; }	//�R���{�X�R�A�擾�֐�
	static MODE				GetMode(void)			{ return m_mode; }				//���[�h���擾�֐�
	static void				SetMode(MODE mode);

private:
	//�����o�ϐ�
	static CRenderer		*m_pRenderer;				//�����_���[�̃|�C���^
	static CScene2D			*m_paScene[MAX_TEXTURE];	//�V�[���̔z��|�C���^
	static CInputKeyboard	*m_pInputKeyboard;			//�L�[�{�[�h���͂̃|�C���^
	static CMouse			*m_pMouse;					//�}�E�X�̃|�C���^
	static CPlayer			*m_pPlayer;					//�v���C���[�̃|�C���^
	static CSound			*m_pSound;					//�T�E���h�̃|�C���^
	static CExplosion		*m_pExplosion;				//�����̃|�C���^
	static CBullet			*m_pBullet;					//�e�̃|�C���^
	static CTitle			*m_pTitle;					//�^�C�g���̃|�C���^
	static CResult			*m_pResult;					//���U���g��ʂ̃|�C���^
	static CGame			*m_pGame;					//�Q�[����ʂ̃|�C���^
	static CPause			*m_pPause;					//�|�[�Y��ʂ̃|�C���^
	static CFade			*m_pFade;					//�t�F�[�h�̃|�C���^
	static CEnemy			*m_pEnemy;					//�G�̃|�C���^
	static CScore			*m_pScore;					//�X�R�A�̃|�C���^
	static CButton			*m_pButton;					//�{�^���̃|�C���^
	static CNumber			*m_pNumber;					//�i���o�[�̃|�C���^
	static CCombo			*m_pCombo;					//�R���{�̃|�C���^
	static CSpeed			*m_pSpeed;					//�X�s�[�hUI�̃|�C���^
	static CUi				*m_pUi;						//UI�̏��
	static CComboUI			*m_pComboUI;				//�R���{UI�̃|�C���^
	static CComboBonus		*m_pComboBonus;				//�R���{�{�[�i�X�̃|�C���^
	static CComboBonusUI	*m_pComboBonusUI;			//�R���{�{�[�i�XUI�̃|�C���^
	static MODE				m_mode;						//���[�h�̏��
	CInput					*m_pInput;					//���͂̃|�C���^

};
#endif