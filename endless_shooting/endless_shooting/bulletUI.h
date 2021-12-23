//*****************************************************************************
//
// 弾UI処理 [bulletUI.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _BULLETUI_H_
#define _BULLETUI_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CGame;
class CRenderer;
class CSceneBase;

//*****************************************************************************
//弾UIクラス宣言
//*****************************************************************************
class CBulletUI :public CScene2D
{
public:
	CBulletUI();								//コンストラクタ
	~CBulletUI();												//デストラクタ

	//メンバ関数
	static HRESULT Load(void);									//読み込み処理
	static void UnLoad(void);									//テクスチャの破棄
	static CBulletUI *Create();									//クリエイト関数
	HRESULT Init();												//初期化関数
	void Uninit(void);											//終了関数
	void Update(void);											//更新関数
	void Draw(void);											//描画関数
	void SetBulletCnt(int bulletcnt) {m_BulletCnt = bulletcnt;}	//残弾格納関数
	int GetBulletCnt(void)			 { return m_BulletCnt; }	//残弾取得関数
	void SetbUse(void)				 { m_bSpeedFlash = true; }	//点滅スイッチ情報格納関数
	bool GetbUse(void)				 { return m_bSpeedFlash; }	//点滅スイッチ情報取得関数
	void Loading(void);											//装填関数

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;				// ポリゴンの位置
	D3DXVECTOR3						m_size;				// ポリゴン大きさ
	int								m_nCounterAnim;		//アニメーションカウンター
	int								m_nPatternAnim;		//アニメーションパターンNo.
	static LPDIRECT3DTEXTURE9		m_pTexture;			//テクスチャの情報[テクスチャの数]
	CScene2D						*m_apScene2D[MAX_BULLET];	//シーン2Dのポインタ配列
	int								m_BulletCnt;		//残弾数
	static bool						m_bSpeedFlash;		//スイッチ
};
#endif