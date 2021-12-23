//*****************************************************************************
//
// コンボの処理 [combo.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"
#include "number.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CCombo;
class CComboBonus;
class CScore;

//*****************************************************************************
//クラス宣言
//*****************************************************************************
class CCombo :public CScene2D
{
public:

	CCombo();											//コンストラクタ
	~CCombo();															//デストラクタ

	//メンバ関数
	static CCombo *Create(void);										//クリエイト関数
	HRESULT Init(void);													//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理
	void ComboAction(void);												//コンボ関数
	bool GetbCombo(void) { return m_bCombo; }							//コンボ判定情報取得関数
	void SetbCombo(bool bCombo) { m_bCombo = bCombo; }					//コンボ判定情報格納関数
	int GetSocreCombo(void) { return m_nComboScore; }					//コンボ判定情報取得関数
	void SetSocreCombo(int nComboScore) { m_nComboScore = nComboScore; }//コンボ判定情報格納関数

private:
	//メンバ変数
	D3DXVECTOR3				m_move;								//移動量
	D3DXVECTOR3				m_pos;								//ポリゴンの位置
	D3DXVECTOR3				m_size;								//ポリゴン大きさ
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	CScore					*m_pScore;							//スコアのポインタ
	bool					m_bCombo;							//コンボの表示切替
	float					m_nColor;							//色数値
	int						m_nCombo;							//コンボ数
	int						m_nComboScore;						//コンボのスコア値
};
#endif
