//*****************************************************************************
//
// ���͏��� [input.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"

//*****************************************************************************
//�C���v�b�g�N���X�錾
//*****************************************************************************
class CInput
{
public:
	CInput();													//�R���X�g���N�^

	//�������z�֐�
	virtual ~CInput();											//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//�������֐�
	virtual void Uninit(void);									//�I���֐�
	virtual void Update(void) = 0;								//�X�V�֐�
	virtual void Draw(void);									//�`��֐�

	//�ϐ��錾
	LPDIRECTINPUTDEVICE8 m_pDevice;								//�f�o�C�X
	static LPDIRECTINPUT8 m_pInput;								//���͂̃|�C���^
private:
};

//*****************************************************************************
//�L�[�{�[�h���͂̃N���X
//*****************************************************************************
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();									//�R���X�g���N�^
	~CInputKeyboard();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//�������֐�
	void Uninit(void);									//�I���֐�
	void Update(void);									//�X�V�֐�
	bool GetKeyPrees(int nKey);							//�L�[�{�[�h���擾�֐�(�v���X)
	bool GetKeyTrigger(int nKey);						//�L�[�{�[�h���擾�֐�(�g���K�[)
	bool GetKeyRelease(int nKey);						//�L�[�{�[�h���擾�֐�(�����[�X)

private:
	//�����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̏��
	BYTE m_aKeyStateOld[NUM_KEY_MAX];					//�ߋ��̃L�[�{�[�h�̏��
	BYTE m_aKeyStatePress[NUM_KEY_MAX];					//�v���X�̏ꍇ�̃L�[�{�[�h�̏��
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//�g���K�[�̏ꍇ�̃L�[�{�[�h�̏��
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//�����[�X�̏ꍇ�̃L�[�{�[�h�̏��
};

//*****************************************************************************
//�}�E�X���͂̃N���X
//*****************************************************************************
class CMouse:public CInput
{
public:
	CMouse();											//�R���X�g���N�^
	~CMouse();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//�������֐�
	void Uninit(void);									//�I���֐�
	void Update(void);									//�X�V�֐�
	bool GetMousePrees(int nKey);						//�L�[�{�[�h���擾�֐�(�v���X)					
	bool GetMouseTrigger(int nKey);						//�L�[�{�[�h���擾�֐�(�g���K�[)			
	bool GetMouseRelease(int nKey);						//�L�[�{�[�h���擾�֐�(�����[�X)

private:
	//�����o�ϐ�
	DIMOUSESTATE m_CurrentMouseState;					//!< �}�E�X�̌��݂̓��͏��
	DIMOUSESTATE m_PrevMouseState;						//!< �}�E�X�̈�t���[���O�̓��͏��
	BYTE m_aMouseState[NUM_MOUSE_MAX];					//�}�E�X�̏��
	BYTE m_aMouseStateOld[NUM_MOUSE_MAX];				//�ߋ��̃}�E�X�̏��
	BYTE m_aMouseStatePress[NUM_MOUSE_MAX];				//�v���X�̏ꍇ�̃}�E�X�̏��
	BYTE m_aMouseStateTrigger[NUM_MOUSE_MAX];			//�g���K�[�̏ꍇ�̃}�E�X�̏��
	BYTE m_aMouseStateRelease[NUM_MOUSE_MAX];			//�����[�X�̏ꍇ�̃}�E�X�̏��
};


#endif
