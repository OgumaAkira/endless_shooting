//*****************************************************************************
//
// ���U���g��ʂ̏��� [result.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBg;
class CPlayer;
class CFade;
class CButton;
class CScore;
class CSound;
class CUi;

//*****************************************************************************
//���U���g��ʂ̃N���X�錾
//*****************************************************************************
class CPause :public CScene
{

public:
	CPause(int nPriority = 5);		//�R���X�g���N�^
	~CPause();						//�f�X�g���N�^

	//�����o�֐�
	static CPause *Create();		//�N���G�C�g�֐�
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
	static CUi				*m_pUi;				//UI�̃|�C���^
	CInput*					m_pInput;			//�C���v�b�g�̃|�C���^
	bool					m_bButton;			//�X�C�b�`
};
#endif