//*****************************************************************************
//
// マネージャー処理 [manager.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
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
//オブジェクト2クラス宣言
//*****************************************************************************
class CManager
{
public:
	//構造体
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_PAUSE,
		MODE_END
	}MODE;

	CManager();								//コンストラクタ
	~CManager();							//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu);						//初期化関数
	void Uninit(void);																//終了関数
	void Update(void);																//更新関数
	void Draw(void);																//描画関数
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }			//レンダラーの情報取得関数
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pInputKeyboard; }	//キーボード入力情報取得関数
	static CMouse			*GetMouse(void)			{ return m_pMouse; }			//マウス入力情報取得関数
	static CPlayer			*GetPlayer(void)		{ return m_pPlayer; }			//プレイヤー情報取得関数
	static CEnemy			*GetEnemy(void)			{ return m_pEnemy; }			//エネミー情報取得関数
	static CSound			*GetSound(void)			{ return m_pSound; }			//サウンド情報取得関数
	static CExplosion		*GetExplosion(void)		{ return m_pExplosion; }		//爆発情報取得関数
	static CBullet			*GetBullet(void)		{ return m_pBullet; }			//バレット情報取得関数
	static CButton			*GetButton(void)		{ return m_pButton; }			//ボタン情報取得関数
	static CScore			*GetScore(void)			{ return m_pScore; }			//スコア取得関数
	static CFade			*GetFade(void)			{ return m_pFade; }				//フェード取得関数
	static CCombo			*GetCombo(void)			{ return m_pCombo; }			//コンボ取得関数
	static CSpeed			*GetSpeed(void)			{ return m_pSpeed; }			//スピードUI取得関数
	static CUi				*GetUi(void)			{ return m_pUi; }				//UI取得関数
	static CComboUI			*GetComboUI(void)		{ return m_pComboUI; }			//コンボUI取得関数
	static CComboBonus		*GetComboBonus(void)	{ return m_pComboBonus; }		//コンボスコア取得関数
	static CComboBonusUI	*GetComboBonusUI(void)	{ return m_pComboBonusUI; }	//コンボスコア取得関数
	static MODE				GetMode(void)			{ return m_mode; }				//モード情報取得関数
	static void				SetMode(MODE mode);

private:
	//メンバ変数
	static CRenderer		*m_pRenderer;				//レンダラーのポインタ
	static CScene2D			*m_paScene[MAX_TEXTURE];	//シーンの配列ポインタ
	static CInputKeyboard	*m_pInputKeyboard;			//キーボード入力のポインタ
	static CMouse			*m_pMouse;					//マウスのポインタ
	static CPlayer			*m_pPlayer;					//プレイヤーのポインタ
	static CSound			*m_pSound;					//サウンドのポインタ
	static CExplosion		*m_pExplosion;				//爆発のポインタ
	static CBullet			*m_pBullet;					//弾のポインタ
	static CTitle			*m_pTitle;					//タイトルのポインタ
	static CResult			*m_pResult;					//リザルト画面のポインタ
	static CGame			*m_pGame;					//ゲーム画面のポインタ
	static CPause			*m_pPause;					//ポーズ画面のポインタ
	static CFade			*m_pFade;					//フェードのポインタ
	static CEnemy			*m_pEnemy;					//敵のポインタ
	static CScore			*m_pScore;					//スコアのポインタ
	static CButton			*m_pButton;					//ボタンのポインタ
	static CNumber			*m_pNumber;					//ナンバーのポインタ
	static CCombo			*m_pCombo;					//コンボのポインタ
	static CSpeed			*m_pSpeed;					//スピードUIのポインタ
	static CUi				*m_pUi;						//UIの情報
	static CComboUI			*m_pComboUI;				//コンボUIのポインタ
	static CComboBonus		*m_pComboBonus;				//コンボボーナスのポインタ
	static CComboBonusUI	*m_pComboBonusUI;			//コンボボーナスUIのポインタ
	static MODE				m_mode;						//モードの情報
	CInput					*m_pInput;					//入力のポインタ

};
#endif