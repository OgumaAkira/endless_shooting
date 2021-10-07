//*****************************************************************************
//
// 爆発処理 [explosion.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _EXLPOSION_H_
#define _EXLPOSION_H_

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
class CExplosion :public CScene2D
{
public:
	CExplosion();				//コンストラクタ
	~CExplosion();				//デストラクタ

	//メンバ関数
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				//初期化関数
	void Uninit(void);												//終了関数
	void Update(void);												//更新関数
	void Draw(void);												//描画関数
	static HRESULT Load(void);										//ロード関数
	static void UnLoad(void);										//アンロード関数


private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
};
#endif 