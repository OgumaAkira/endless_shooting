//*****************************************************************************
//
// ナンバーの処理 [number.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CScene;

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CNumber
{
public:
	CNumber();				//コンストラクタ
	~CNumber();				//デストラクタ

	//メンバ関数
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);//クリエイト関数
	static HRESULT Load(void);											//ロード関数
	static void UnLoad(void);											//アンロード関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);			//初期化関数
	void Uninit(void);													//終了関数
	void Update(void);													//更新関数
	void Draw(void);													//描画関数
	void SetNumber(int nNumber);										//ナンバー情報格納関数
	void SetColor(D3DXCOLOR col)		{ m_color = col; }				//色格納関数
	void SetPosition(D3DXVECTOR3 pos)	{ m_pos = pos; }				//位置情報格納関数
	void SetSize(D3DXVECTOR3 size)		{ m_size = size; }				//大きさ情報取得関数
	D3DXVECTOR3 GetPosition(void)		{ return D3DXVECTOR3(m_pos); }	//位置取得関数
	D3DXVECTOR3 GetSize(void)			{ return D3DXVECTOR3(m_size); }	//大きさ取得関数
	D3DXCOLOR	GetColor()				{ return D3DXCOLOR(m_color);}	//色取得関数

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャの情報
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//頂点バッファの情報
	D3DXVECTOR3					m_pos;			// ポリゴンの位置
	D3DXVECTOR3					m_size;			// ポリゴンの大きさ
	D3DXVECTOR2					m_tex;			//テスクチャ
	D3DXCOLOR					m_color;		//カラー
	CScene						*m_pScene;		//シーンのポインタ
};
#endif