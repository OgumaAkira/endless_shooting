//*****************************************************************************
//
// ���U���g��ʂ̏��� [result.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBg;
class CPlayer;
class CFade;
class CButton;
class CScore;
class CSound;
class CHIScore;
class CUi;

//*****************************************************************************
//���U���g��ʂ̃N���X�錾
//*****************************************************************************
class CResult :public CScene
{
public:
	CResult(int nPriority=1);		//�R���X�g���N�^
	~CResult();						//�f�X�g���N�^

	//�����o�֐�
	static CResult *Create();		//�N���G�C�g�֐�
	HRESULT Init();					//�������֐�
	void Uninit(void);				//�I���֐�
	void Update(void);				//�X�V�֐�
	void Draw(void);				//�`��֐�

private:
	//�����o�ϐ�
	static CBg				*m_pBg;				//�w�i�̃|�C���^
	static CFade			*m_pFade;			//�t�F�[�h�̃|�C���^
	static CPlayer			*m_pPlayer;			//�v���C���[�̃|�C���^
	static CButton			*m_pButton;			//�{�^���̃|�C���^
	static CScore			*m_pScore;			//�X�R�A�̃|�C���^
	static CHIScore			*m_pHiScore;		//�n�C�X�R�A�̃|�C���^
	static CUi				*m_pHiScoreUI;		//�n�C�X�R�AUI�̃|�C���^
	CInput*					m_pInput;			//�C���v�b�g�̃|�C���^
	bool					m_bButton;		//�X�C�b�`
};
#endif