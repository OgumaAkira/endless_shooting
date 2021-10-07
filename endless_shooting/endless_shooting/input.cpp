//*****************************************************************************
//
// 入力処理 [input.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
		
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CInput::CInput()
{
	m_pDevice = NULL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CInput::~CInput()
{

}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//インプットのポインタが何も無かった場合
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
//終了関数
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
//更新関数
//*****************************************************************************
void CInput::Update(void)
{

}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CInput::Draw(void)
{

}

//*****************************************************************************
//コンストラクタ(キーボード)
//*****************************************************************************
CInputKeyboard::CInputKeyboard()
{
	//キーの情報クリア
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateOld, 0, sizeof(m_aKeyStateOld));
	memset(m_aKeyStatePress, 0, sizeof(m_aKeyStatePress));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));

}
//*****************************************************************************
//デストラクタ(キーボード)
//*****************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}

//*****************************************************************************
//初期化関数(キーボード)
//*****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得（入力制御開始）
	m_pDevice->Acquire();
	return S_OK;
}

//*****************************************************************************
//終了関数(キーボード)
//*****************************************************************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
//更新関数(キーボード)
//*****************************************************************************
void CInputKeyboard::Update(void)
{
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &m_aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//プレス
			m_aKeyStatePress[nCntKey] = m_aKeyStateOld[nCntKey];

			//トリガー
			m_aKeyStateTrigger[nCntKey] =
				(m_aKeyState[nCntKey] & m_aKeyStateOld[nCntKey])^ m_aKeyState[nCntKey];

			//リリース
			m_aKeyStateRelease[nCntKey] =
				(m_aKeyState[nCntKey] | m_aKeyStateOld[nCntKey])^ m_aKeyState[nCntKey];

			//キープレス情報を保存
			m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
		}
	}
	else
	{
		//キーボードへのアクセス権を取得
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
//キーボード判別関数(Press)
//*****************************************************************************
bool CInputKeyboard::GetKeyPrees(int nKey)
{
	return(m_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//キーボード判別関数(Trigger)
//*****************************************************************************
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//キーボード判別関数(Release)
//*****************************************************************************
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//コンストラクタ(マウス)
//*****************************************************************************
CMouse::CMouse()
{
	//キーの情報クリア
	memset(m_aMouseState, 0, sizeof(m_aMouseState));
	memset(m_aMouseStateOld, 0, sizeof(m_aMouseStateOld));
	memset(m_CurrentMouseState.rgbButtons, 0, sizeof(m_CurrentMouseState.rgbButtons));
	memset(m_PrevMouseState.rgbButtons, 0, sizeof(m_PrevMouseState.rgbButtons));

}

//*****************************************************************************
//デストラクタ(マウス)
//*****************************************************************************
CMouse::~CMouse()
{

}

//*****************************************************************************
//初期化関数(マウス)
//*****************************************************************************
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//入力デバイス（マウス）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権を獲得（入力制御開始）
	m_pDevice->Acquire();
	return S_OK;
}

//*****************************************************************************
//終了関数(マウス)
//*****************************************************************************
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//*****************************************************************************
//更新関数(マウス)
//*****************************************************************************
void CMouse::Update(void)
{
	// 現在のマウス入力情報をデバイスから取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_CurrentMouseState), &m_CurrentMouseState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_MOUSE_MAX; nCntClick++)
		{
			//トリガー
			m_aMouseStateTrigger[nCntClick] =
				(m_CurrentMouseState.rgbButtons[nCntClick] & m_aMouseStatePress[nCntClick]) ^ m_CurrentMouseState.rgbButtons[nCntClick];

			//リリース
			m_aMouseStateRelease[nCntClick] =
				(m_CurrentMouseState.rgbButtons[nCntClick] | m_PrevMouseState.rgbButtons[nCntClick]) ^ m_CurrentMouseState.rgbButtons[nCntClick];

			//プレス情報に現在の入力情報を保存
			m_aMouseStatePress[nCntClick] = m_CurrentMouseState.rgbButtons[nCntClick];

			//キープレス情報を保存
			m_PrevMouseState = m_CurrentMouseState;
		}
		// マウス座標を取得する
		POINT posPoint;
		GetCursorPos(&posPoint);
		// スクリーン座標をクライアント座標に変換する
		ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &posPoint);
	}
	else
	{
		//キーボードへのアクセス権を取得
		m_pDevice->Acquire();
	}
}

//*****************************************************************************
//キーボード判別関数(Press)
//*****************************************************************************
bool CMouse::GetMousePrees(int nKey)
{
	return(m_aMouseStatePress[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//キーボード判別関数(Trigger)
//*****************************************************************************
bool CMouse::GetMouseTrigger(int nKey)
{
	return(m_aMouseStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************
//キーボード判別関数(Release)
//*****************************************************************************
bool CMouse::GetMouseRelease(int nKey)
{
	return(m_aMouseStateRelease[nKey] & 0x80) ? true : false;
}
