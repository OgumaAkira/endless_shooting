//*****************************************************************************
//
// スピードの処理 [speed.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _COMBOBONUSUI_H_
#define _COMBOBONUSUI_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CSound;

//*****************************************************************************
//スピードのクラス宣言
//*****************************************************************************
class CComboBonusUI :public CScene2D
{
public:
	CComboBonusUI(int nPriority = 7);								//コンストラクタ
	~CComboBonusUI();												//デストラクタ

	//メンバ関数
	static CComboBonusUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				//初期化関数
	void Uninit(void);												//終了関数
	void Update(void);												//更新関数
	void Draw(void);												//描画関数
	void ComboEvent(void);											//コンボ表示関数
	static HRESULT Load(void);										//ロード関数
	static void UnLoad(void);										//アンロード関数

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture;			//テクスチャの情報
	D3DXVECTOR3						m_pos;				// ポリゴンの位置
	D3DXVECTOR3						m_move;				// ポリゴンの移動量
	D3DXVECTOR3						m_size;				// ポリゴン大きさ
	CSound							*pSound;			//サウンド
	float							m_nColor;			//色数値
};
#endif 