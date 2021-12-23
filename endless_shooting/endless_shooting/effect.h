#pragma once
//*****************************************************************************
//
// 爆発処理 [effect.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"

//*****************************************************************************
//爆発のクラス宣言
//*****************************************************************************
class CEffect :public CScene2D
{
public:
	//構造体定義(タイプ)
	typedef enum
	{
		EFFECT_TYPE_EXPLOSION = 0,	//何もない
		EFFECT_TYPE_CURSOR,		//カーソル
		EFFECT_TYPE_PLAYER,		//プレイヤー
		EFFECT_TYPE_ENEMY,		//敵
		EFFECT_TYPE_MAX			//最大数
	} EFFECT_TYPE;


	CEffect();				//コンストラクタ
	~CEffect();				//デストラクタ

								//メンバ関数
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR3 move, int type);	//クリエイト関数
	void Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	void ClickEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);												//初期化関数
	void Uninit(void);												//終了関数
	void Update(void);												//更新関数
	void Draw(void);												//描画関数
	static HRESULT Load(void);										//ロード関数
	static void UnLoad(void);										//アンロード関数

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture;	//テクスチャの情報
	D3DXVECTOR3					m_move;		//移動量
}; 
#endif