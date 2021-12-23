//*****************************************************************************
//
// ゲーム画面の処理 [game.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _GAME_H_	//二重のインクルード防止のマクロ定義
#define _GAME_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define _CRT_SECURE_WANINGS

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "mode_base.h"
#include "scene2d.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CPlayer;

//*****************************************************************************
//ゲーム画面のクラス宣言
//*****************************************************************************
class CGame : public CScene2D
{
public:
	//構造体定義(状態)
	enum GAMESTATE
	{
		GAMESTATE_NONE = 0,		//何もない状態
		GAMESTATE_SPEEDUP,		//敵速度を上げる
		GAMESTATE_NORMAL,		//通常状態
		GAMESTATE_ENEMYBREAK,	//敵を倒した状況
		GAMESTATE_END,			//リザルト画面
		GAMESTATE_FINISH,		//ゲーム終了状態(画面遷移開始待ち状態）
		GAMESTATE_MAX			//最大数
	};

	CGame();										 //コンストラクタ
	~CGame();														 //デストラクタ
																	 
	//メンバ関数													    
	static CGame *Create();											 //クリエイト
	virtual void Init(CMode *pMode);							//初期化関数
	virtual void Update(CMode *pMode);						//更新関数
	virtual void Uninit(void);						//終了関数
	void Draw(void);												 //更新処理
	static void SetGameState(GAMESTATE state) {m_GameState = state;} //ゲーム状態設定
	static GAMESTATE GetGameState(void)		  { return m_GameState;} //ゲーム状態取得
	D3DXVECTOR3 GetRandPos(void);									 //敵の乱数配置位置取得関数
	D3DXVECTOR3 GetRandMove(void);									 //敵の乱数配置慣性取得関数

private:
	//メンバ変数
	static GAMESTATE	m_GameState;			//状態
	CPlayer				*m_pPlayer;				//プレイヤーのポインタ	
	float				m_GameSpeed;			//ゲームスピード
};
#endif