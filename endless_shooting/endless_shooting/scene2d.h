//*****************************************************************************
//
// シーン2D処理 [scene.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scenebase.h"

//*****************************************************************************
//シーン2Dのクラス宣言
//*****************************************************************************
class CScene2D :public CSceneBase
{
public:
	CScene2D(int nPriority = 0);												//コンストラクタ
	~CScene2D();																//デストラクタ

	//メンバ関数
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);				//クリエイト関数
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum);	//フェードクリエイト関数

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								//初期化処理
	void Uninit(void);																//終了処理
	void Update(void);																//更新処理
	void Draw(void);																//描画処理

	void CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);							//頂点の生成
	void SetVertex(void);															//頂点の設定
	void InitAnimation(int PatternAnim, int CounterAnim, int nLoop);				//アニメーション初期化関数
	void UpdateAnimation(void);														//アニメーション更新関数
	void InitScroll(int nSpeed, float fDivision);									//画面スクロールの初期化
	void UpdateScroll(void);														//画面スクロールの更新
	void ScaleUp(float fScaleUp);
	void FlashPolygon(int nFlashFlame);												//ポリゴンの点滅
	void FadeOut(float fSpeed);														//フェードアウト
	void NumberAnimation(int nNumber);												//数字の設定


	// 格納関数
	void SetCol(D3DXCOLOR col);											// 色の設定
	void SetRotation(float rotasion);									// 回転の設定
	void SetScale(const float &fScale);									// 拡大の値設定
	void SetbNumber(bool bNumber) { m_bNumber = bNumber; }				// 使用判定

	//取得関数
	float GetScale(void) { return m_fScaleNum; }						// 拡大の値情報
	bool GetNumber(void) { return m_bNumber; }							//ナンバーフラグ

private:
	int						m_nPatternAnim;			//アニメーションパターン数
	int						m_nCounterAnim;			//アニメーションカウンター
	int						m_nCountAnim;			//アニメーションテクスチャ
	int						m_nCountAnimPattern;	//アニメーションのパターン
	int						m_nLoop;				//ループするかどうか
	int						m_nSpeedTexture;		//テクスチャの移動速度
	int						m_nFlashFlame;			//点滅用のカウンター
	float					m_fDivisionCounter;		// スクロールのカウンター
	float					m_fDivisionBaseNum;		//スクロールのカウンター
	float					m_fRotasion;			//回転用変数
	float					m_fScaleNum;			//拡大用変数
	float					m_fSubFlashNum;			//ポリゴンの点灯用
	float					m_fSubNum;				//ポリゴンのサブ点灯用
	float					m_fFadeSpeedNum;		//フェードのスピード
	bool					m_bDisappearFlag;		//点滅用のフラグ
	bool					m_bFadeOut;				//フェードのフラグ
	bool					m_bNumber;				//使う数字のフラグ
};
#endif 