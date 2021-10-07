//*****************************************************************************
//
// ハイスコア処理 [hiscore.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _HISCORE_H_
#define _HISCORE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//*****************************************************************************
//スコアクラス宣言
//*****************************************************************************
class CHIScore :public CScene
{
	//構造体定義(種類)
	typedef enum
	{
		HISCORETYPE_NONE = 0,		//何もない状態
		HISCORETYPE_HISCORE,		//ハイスコア
		HISCORETYPE_MYSCORE,		//自己スコア
		HISCORETYPE_MAX				//最大数
	}HISCORETYPE;

public:
	CHIScore();					//コンストラクタ
	~CHIScore();				//デストラクタ

	//メンバ関数
	static CHIScore *Create(void);			//クリエイト関数
	HRESULT Init(void);						//初期化関数
	void Uninit(void);						//終了関数
	void Update(void);						//更新関数
	void Draw(void);						//描画関数
	static void WriteFile(int nScore);		//書き込み関数
	static int ReadFile(void);				//読み込み関数

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;								//ポリゴンの位置
	D3DXVECTOR3				m_size;								//ポリゴン大きさ
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	static int				m_nScore;							//スコア
};
#endif