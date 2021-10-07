//*****************************************************************************
//
// スピードの処理 [speed.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SPEED_H_
#define _SPEED_H_

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
//スピードのクラス宣言
//*****************************************************************************
class CSpeed :public CScene2D
{
public:

	CSpeed(int nPriority=7);									//コンストラクタ
	~CSpeed();													//デストラクタ

	//メンバ関数
	static CSpeed *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//初期化関数
	void Uninit(void);											//終了関数
	void Update(void);											//更新関数
	void Draw(void);											//描画関数
	static HRESULT Load(void);									//ロード関数
	static void UnLoad(void);									//アンロード関数
	static void SetbUse(bool bUse) { m_bUse = bUse; }			//スイッチ情報格納関数
	static bool GetbUse(void) { return m_bUse; }				//スイッチ取得関数

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;					// ポリゴンの位置
	D3DXVECTOR3						m_move;					// ポリゴンの移動量
	D3DXVECTOR3						m_size;					// ポリゴン大きさ
	D3DXCOLOR						m_col;					//カラー
	static int						m_nFrameCnt;			//フラッシュカウント
	int								m_Cnt;					//カウント
	bool							m_bUse2;				//スイッチ2
	static bool						m_bUse;					//スイッチ
	static LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャの情報
	CSound							*pSound;				//サウンド
};
#endif 