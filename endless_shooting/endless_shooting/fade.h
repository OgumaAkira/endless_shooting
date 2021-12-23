//*****************************************************************************
//
// フェードの処理 [fade.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//*****************************************************************************
//フェードのクラス宣言
//*****************************************************************************
class CFade:public CScene2D
{
public:
	//構造体定義(状態)
	typedef enum
	{
		FADESTATE_NONE = 0,		//何もない状態
		FADESTATE_IN,			//フェードイン
		FADESTATE_OUT,			//フェードアウト
		FADESTATE_MAX			//最大数
	}FADESTATE;

	CFade(int nPriority = 10);				//コンストラクタ
	~CFade();								//デストラクタ

	//メンバ関数
	static CFade *Create();									//クリエイト関数
	static HRESULT Load(void);								//ロード関数
	static void UnLoad(void);								//アンロード関数
	HRESULT Init();											//初期化処理
	void Uninit(void);										//終了処理
	void Update(void);										//更新処理
	void Draw(void);										//描画処理
	void SetFade(FADESTATE fade) { m_FadeState = fade; }	//フェードの状態格納関数
	static FADESTATE GetFade(void) { return m_FadeState; }	//フェードの状態取得関数

private:
	//メンバ変数
	D3DXVECTOR3						m_move;							//移動量
	D3DXVECTOR3						m_pos;							//ポリゴンの位置
	D3DXVECTOR3						m_size;							//ポリゴン大きさ
	static int						m_color;						//ポリゴンの色
	bool							m_bSpeedFlash;							//ONOFF
	static FADESTATE				m_FadeState;			//使用しているかどうか
	static LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャの情報[テクスチャの数]
	CScene2D						*m_pScene2D;			//シーン2Dのポインタ配列
};
#endif