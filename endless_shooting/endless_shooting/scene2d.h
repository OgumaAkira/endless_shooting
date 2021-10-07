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
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
//シーン2Dのクラス宣言
//*****************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = 14);												//コンストラクタ
	~CScene2D();																//デストラクタ

	//メンバ関数
	static CScene2D *Create();														//クリエイト関数
	HRESULT Init(void);																//初期化処理
	void Uninit(void);																//終了処理
	void Update(void);																//更新処理
	void Draw(void);																//描画処理
	void SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2);									//テクスチャ格納関数
	void SetPosition(D3DXVECTOR3 pos)				{ m_pos = pos; }				//位置格納関数
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; }				//大きさ格納関数
	void SetColor(D3DXCOLOR col)					{ m_color = col; }				//色格納関数
	void BirdTexture(LPDIRECT3DTEXTURE9 pTexture)	{ m_pTexture = pTexture; }		//テクスチャの情報格納関数
	void AnimationTexture(OBJTYPE objType,int PatternAnim, int CounterAnim);		//アニメーション関数
	
	D3DXVECTOR3 GetPosition(void)				{ return m_pos; }	//位置取得関数
	D3DXVECTOR3 GetSize(void)					{ return m_size; }	//大きさ取得関数
	D3DXVECTOR2	GetTex(void)					{ return m_tex, m_tex2; }	//テクスチャ取得関数
	D3DXCOLOR	GetColor(void)					{ return m_color; }	//カラー取得関数
	
private:
	//メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャの情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファの情報
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;					// ポリゴンの大きさ
	D3DXVECTOR2				m_tex;					//テスクチャ
	D3DXVECTOR2				m_tex2;					//テスクチャ
	D3DXCOLOR				m_color;				//カラー
	
	int						m_nCounterAnim;			//アニメーションカウンター
	int						m_nPatternAnim;			//アニメーションパターンNo.

};
#endif 