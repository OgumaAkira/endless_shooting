//*****************************************************************************
//
// リザルト画面の処理 [result.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//前方宣言
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
//リザルト画面のクラス宣言
//*****************************************************************************
class CResult :public CScene
{
public:
	CResult(int nPriority=1);		//コンストラクタ
	~CResult();						//デストラクタ

	//メンバ関数
	static CResult *Create();		//クリエイト関数
	HRESULT Init();					//初期化関数
	void Uninit(void);				//終了関数
	void Update(void);				//更新関数
	void Draw(void);				//描画関数

private:
	//メンバ変数
	static CBg				*m_pBg;				//背景のポインタ
	static CFade			*m_pFade;			//フェードのポインタ
	static CPlayer			*m_pPlayer;			//プレイヤーのポインタ
	static CButton			*m_pButton;			//ボタンのポインタ
	static CScore			*m_pScore;			//スコアのポインタ
	static CHIScore			*m_pHiScore;		//ハイスコアのポインタ
	static CUi				*m_pHiScoreUI;		//ハイスコアUIのポインタ
	CInput*					m_pInput;			//インプットのポインタ
	bool					m_bButton;		//スイッチ
};
#endif