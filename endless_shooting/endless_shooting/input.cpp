//*****************************************************************************
//
// ���͏��� [input.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
		
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CInput::CInput()
{
	m_pDevice = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CInput::~CInput()
{

}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�C���v�b�g�̃|�C���^���������������ꍇ
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, 
						   DIRECTINPUT_VERSION,
						   IID_IDirectInput8,
						   (void**)&m_pInput, NULL);
	}

	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CInput::Update(void)
{

}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CInput::Draw(void)
{

}

//*****************************************************************************
//�R���X�g���N�^(�L�[�{�[�h)
//*****************************************************************************
CInputKeyboard::CInputKeyboard()
{
	//�L�[�̏��N���A
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateOld, 0, sizeof(m_aKeyStateOld));
	memset(m_aKeyStatePress, 0, sizeof(m_aKeyStatePress));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));

}
//*****************************************************************************
//�f�X�g���N�^(�L�[�{�[�h)
//*****************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}

//*****************************************************************************
//�������֐�(�L�[�{�[�h)
//*****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l���i���͐���J�n�j
	m_pDevice->Acquire();
	return S_OK;
}

//*****************************************************************************
//�I���֐�(�L�[�{�[�h)
//*****************************************************************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
//�X�V�֐�(�L�[�{�[�h)
//*****************************************************************************
void CInputKeyboard::Update(void)
{
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &m_aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�v���X
			m_aKeyStatePress[nCntKey] = m_aKeyStateOld[nCntKey];

			//�g���K�[
			m_aKeyStateTrigger[nCntKey] =
				(m_aKeyState[nCntKey] & m_aKeyStateOld[nCntKey])^ m_aKeyState[nCntKey];

			//�����[�X
			m_aKeyStateRelease[nCntKey] =
				(m_aKeyState[nCntKey] | m_aKeyStateOld[nCntKey])^ m_aKeyState[nCntKey];

			//�L�[�v���X����ۑ�
			m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
		}
	}
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Press)
//*****************************************************************************
bool CInputKeyboard::GetKeyPrees(int nKey)
{
	return(m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Trigger)
//*****************************************************************************
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Release)
//*****************************************************************************
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//�R���X�g���N�^(�}�E�X)
//*****************************************************************************
CMouse::CMouse()
{
	//�L�[�̏��N���A
	memset(m_aMouseState, 0, sizeof(m_aMouseState));
	memset(m_aMouseStateOld, 0, sizeof(m_aMouseStateOld));
	memset(m_CurrentMouseState.rgbButtons, 0, sizeof(m_CurrentMouseState.rgbButtons));
	memset(m_PrevMouseState.rgbButtons, 0, sizeof(m_PrevMouseState.rgbButtons));

}

//*****************************************************************************
//�f�X�g���N�^(�}�E�X)
//*****************************************************************************
CMouse::~CMouse()
{

}

//*****************************************************************************
//�������֐�(�}�E�X)
//*****************************************************************************
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//���̓f�o�C�X�i�}�E�X�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l���i���͐���J�n�j
	m_pDevice->Acquire();
	return S_OK;
}

//*****************************************************************************
//�I���֐�(�}�E�X)
//*****************************************************************************
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
//�X�V�֐�(�}�E�X)
//*****************************************************************************
void CMouse::Update(void)
{
	// ���݂̃}�E�X���͏����f�o�C�X����擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_CurrentMouseState), &m_CurrentMouseState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_MOUSE_MAX; nCntClick++)
		{
			//�g���K�[
			m_aMouseStateTrigger[nCntClick] =
				(m_CurrentMouseState.rgbButtons[nCntClick] & m_aMouseStatePress[nCntClick]) ^ m_CurrentMouseState.rgbButtons[nCntClick];

			//�����[�X
			m_aMouseStateRelease[nCntClick] =
				(m_CurrentMouseState.rgbButtons[nCntClick] | m_PrevMouseState.rgbButtons[nCntClick]) ^ m_CurrentMouseState.rgbButtons[nCntClick];

			//�v���X���Ɍ��݂̓��͏���ۑ�
			m_aMouseStatePress[nCntClick] = m_CurrentMouseState.rgbButtons[nCntClick];

			//�L�[�v���X����ۑ�
			m_PrevMouseState = m_CurrentMouseState;
		}
		// �}�E�X���W���擾����
		POINT posPoint;
		GetCursorPos(&posPoint);
		// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
		ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &posPoint);
	}
	else
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Press)
//*****************************************************************************
bool CMouse::GetMousePrees(int nKey)
{
	return(m_aMouseStatePress[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Trigger)
//*****************************************************************************
bool CMouse::GetMouseTrigger(int nKey)
{
	return(m_aMouseStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//�L�[�{�[�h���ʊ֐�(Release)
//*****************************************************************************
bool CMouse::GetMouseRelease(int nKey)
{
	return(m_aMouseStateRelease[nKey] & 0x80) ? true : false;
}
