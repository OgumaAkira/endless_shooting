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
class CSound;

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "mode_base.h"

//*****************************************************************************
//リザルト画面のクラス宣言
//*****************************************************************************
class CResult :public CScene2D
{
public:
	CResult(int nPriority=1);		//コンストラクタ
	~CResult();						//デストラクタ

	//メンバ関数
	static CResult *Create();		//クリエイト関数
	virtual void Init(CMode *pMode);							//初期化関数
	virtual void Update(CMode *pMode);						//更新関数
	virtual void Uninit(void);						//終了関数

private:
	//メンバ変数
	CSound					*m_pSound;		//サウンドのポインタ
};
#endif