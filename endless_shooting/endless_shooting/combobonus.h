//*****************************************************************************
//
// コンボスコア処理 [comboscore.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _COMBOBONUS_H_
#define _COMBOBONUS_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
class CCombo;

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_COMBOBONUS_NUMBER (5)						//スコアナンバーの最大数

//*****************************************************************************
//スコアのクラス宣言
//*****************************************************************************
class CComboBonus :public CScene
{
public:
	CComboBonus(int nPriority = 7);						//コンストラクタ
	~CComboBonus();										//デストラクタ

	//メンバ関数
	static CComboBonus *Create(void);					//クリエイト関数
	HRESULT Init(void);									//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	void SetScore(int nScore) { m_nScore = nScore; }	//スコア値格納関数
	int GetScore(void) { return m_nScore; }				//スコア取得関数

private:
	//メンバ変数
	D3DXVECTOR3				m_move;								//移動量
	D3DXVECTOR3				m_pos;								// ポリゴンの位置
	D3DXVECTOR3				m_size;								// ポリゴン大きさ
	CNumber					*m_apNumber[MAX_COMBOBONUS_NUMBER];	//シーン2Dのポインタ配列
	static int				m_nScore;							//スコア
	float					m_nColor;							//色
};
#endif