//*****************************************************************************
//
// タイトル画面の処理 [title.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CBg;
class CFade;
class CPlayer;
class CButton;
class CSound;
class CTutorial;
class CHIScore;
class CUi;

//*****************************************************************************
//タイトル画面のクラス宣言
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority=1);				//コンストラクタ
	~CTitle();								//デストラクタ

	//プロトタイプ宣言
	static CTitle *Create();				//クリエイト関数
	HRESULT Init();							//初期化関数
	void Uninit(void);						//終了関数
	void Update(void);						//更新関数
	void Draw(void);						//描画関数

private:
	//メンバ変数
	static CBg				*m_pBg;			//背景のポインタ
	static CFade			*m_pFade;		//フェードのポインタ
	static CPlayer			*m_pPlayer;		//プレイヤーのポインタ
	static CButton			*m_pButton;		//ボタンのポインタ
	static CHIScore			*m_pHiScore;	//ハイスコアのポインタ
	static CUi				*m_pUi;			//UIのポインタ
	CSound					*pSound;		//サウンドのポインタ
	CInput					*m_pInput;		//入力のポインタ
	bool					m_bButton;			//スイッチ
};
#endif