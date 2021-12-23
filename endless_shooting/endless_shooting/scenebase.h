//*****************************************************************************
//
// ポリゴン処理 [polygon.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
//シーン2Dのクラス宣言
//*****************************************************************************
class CSceneBase :public CScene
{
public:
	CSceneBase(int nPriority = 0);
	virtual ~CSceneBase();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;								//初期化処理
	virtual void Uninit(void) = 0;																//終了処理
	virtual void Update(void) = 0;																//更新処理
	virtual void Draw(void) = 0;																//描画処理

	// テクスチャの設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
protected:

	// Set関数
	virtual void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }			// 座標
	virtual void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			// サイズ
	virtual void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }			// 角度		
	virtual void SetColor(const D3DXCOLOR &col) { m_col = col; }			// 色
	void BindVtxBuff(const LPDIRECT3DVERTEXBUFFER9 pVtxBuff) { m_pVtxBuff = pVtxBuff; }	// 頂点バッファ

																						// Get関数
	D3DXVECTOR3 &GetPos(void) { return m_pos; }							// 座標
	D3DXVECTOR3 &GetSize(void) { return m_size; }							// サイズ
	D3DXCOLOR &GetColor(void) { return m_col; };							// 色
	D3DXVECTOR3 &GetRot(void) { return m_rot; };							// 回転量
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }						// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }						// バッファ情報

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャの情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファの情報
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;					// ポリゴンの大きさ
	D3DXVECTOR3				m_rot;					//テクスチャの回転
	D3DXCOLOR				m_col;					//カラー
};
#endif