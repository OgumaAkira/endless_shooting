//*****************************************************************************
//
// リザルト画面の処理 [result.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CBg;
class CPlayer;
class CFade;
class CButton;
class CScore;
class CSound;
class CUi;

//*****************************************************************************
//リザルト画面のクラス宣言
//*****************************************************************************
class CPause :public CScene
{

public:
	CPause(int nPriority = 5);		//コンストラクタ
	~CPause();						//デストラクタ

	//メンバ関数
	static CPause *Create();		//クリエイト関数
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
	static CUi				*m_pUi;				//UIのポインタ
	CInput*					m_pInput;			//インプットのポインタ
	bool					m_bButton;			//スイッチ
};
#endif