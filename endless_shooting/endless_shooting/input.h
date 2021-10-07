//*****************************************************************************
//
// 入力処理 [input.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"

//*****************************************************************************
//インプットクラス宣言
//*****************************************************************************
class CInput
{
public:
	CInput();													//コンストラクタ

	//純粋仮想関数
	virtual ~CInput();											//デストラクタ

	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化関数
	virtual void Uninit(void);									//終了関数
	virtual void Update(void) = 0;								//更新関数
	virtual void Draw(void);									//描画関数

	//変数宣言
	LPDIRECTINPUTDEVICE8 m_pDevice;								//デバイス
	static LPDIRECTINPUT8 m_pInput;								//入力のポインタ
private:
};

//*****************************************************************************
//キーボード入力のクラス
//*****************************************************************************
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();									//コンストラクタ
	~CInputKeyboard();									//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化関数
	void Uninit(void);									//終了関数
	void Update(void);									//更新関数
	bool GetKeyPrees(int nKey);							//キーボード情報取得関数(プレス)
	bool GetKeyTrigger(int nKey);						//キーボード情報取得関数(トリガー)
	bool GetKeyRelease(int nKey);						//キーボード情報取得関数(リリース)

private:
	//メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX];						//キーボードの情報
	BYTE m_aKeyStateOld[NUM_KEY_MAX];					//過去のキーボードの情報
	BYTE m_aKeyStatePress[NUM_KEY_MAX];					//プレスの場合のキーボードの情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//トリガーの場合のキーボードの情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//リリースの場合のキーボードの情報
};

//*****************************************************************************
//マウス入力のクラス
//*****************************************************************************
class CMouse:public CInput
{
public:
	CMouse();											//コンストラクタ
	~CMouse();											//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化関数
	void Uninit(void);									//終了関数
	void Update(void);									//更新関数
	bool GetMousePrees(int nKey);						//キーボード情報取得関数(プレス)					
	bool GetMouseTrigger(int nKey);						//キーボード情報取得関数(トリガー)			
	bool GetMouseRelease(int nKey);						//キーボード情報取得関数(リリース)

private:
	//メンバ変数
	DIMOUSESTATE m_CurrentMouseState;					//!< マウスの現在の入力情報
	DIMOUSESTATE m_PrevMouseState;						//!< マウスの一フレーム前の入力情報
	BYTE m_aMouseState[NUM_MOUSE_MAX];					//マウスの情報
	BYTE m_aMouseStateOld[NUM_MOUSE_MAX];				//過去のマウスの情報
	BYTE m_aMouseStatePress[NUM_MOUSE_MAX];				//プレスの場合のマウスの情報
	BYTE m_aMouseStateTrigger[NUM_MOUSE_MAX];			//トリガーの場合のマウスの情報
	BYTE m_aMouseStateRelease[NUM_MOUSE_MAX];			//リリースの場合のマウスの情報
};


#endif
