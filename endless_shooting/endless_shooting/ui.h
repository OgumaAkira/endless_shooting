//*****************************************************************************
//
// ハイスコアUI処理 [hiscoreUI.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
class CSound;


//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CUi :public CScene2D
{
public:

	//構造体定義(種類)
	typedef enum
	{
		UITYPE_NONE = 0,		//何もない状態
		UITYPE_HISCORE,			//ハイスコア
		UITYPE_MYSCORE,			//自己スコア
		UITYPE_TITLELOGO,		//タイトルロゴ
		UITYPE_TUTORIAL,		//チュートリアル
		UITYPE_SCORE,			//スコアのUI
		UITYPE_MAX				//最大数
	}UITYPE;

	CUi(int nPriority = 7);													//コンストラクタ
	~CUi();																	//デストラクタ

	//メンバ関数
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType);	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType);			//初期化関数
	void Uninit(void);														//終了関数
	void Update(void);														//更新関数
	void Draw(void);														//描画関数
	static HRESULT Load(void);												//ロード関数
	static void UnLoad(void);												//アンロード関数

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;						//位置
	D3DXVECTOR3						m_size;						//大きさ
	D3DXCOLOR						m_col;						//カラー
	int								m_Cnt;						//カウント
	static LPDIRECT3DTEXTURE9		m_apTexture[UITYPE_MAX];	//テクスチャの情報
	CSound							*pSound;					//サウンド
};
#endif 