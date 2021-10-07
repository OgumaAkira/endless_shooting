//*****************************************************************************
//
// スコアの処理 [score.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"
#include "hiscore.h"

//*****************************************************************************
//スコアのクラス宣言
//*****************************************************************************
class CScore :public CScene
{
public:
	CScore(int nPriority = 7);						//コンストラクタ
	~CScore();										//デストラクタ

	//メンバ関数
	static CScore *Create(void);						//クリエイト関数
	HRESULT Init(void);									//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	void AddScore(int nScore);							//加算スコア関数	
	int ReadFile(void);									//読み込みファイル関数
	void WriteFile(void);								//書き込みファイル関数
	void SetScore(int nScore)	{ m_nScore = nScore; }	//スコア値格納関数
	static int GetScore(void)			{ return m_nScore; }	//スコア取得関数
private:
	//メンバ変数
	D3DXVECTOR3				m_move;								//移動量
	D3DXVECTOR3				m_pos;								// ポリゴンの位置
	D3DXVECTOR3				m_size;								// ポリゴン大きさ
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	static int				m_nScore;							//スコア
};
#endif