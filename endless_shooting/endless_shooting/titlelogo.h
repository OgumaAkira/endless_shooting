//*****************************************************************************
//
// タイトルロゴ処理 [titlelogo.h]
// Author : 小熊 朗
//
//*****************************************************************************
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"

//オブジェクト2クラス宣言
class CTitleLogo :public CScene2D
{
public:

	CTitleLogo(int nPriority = 7);				//コンストラクタ
	~CTitleLogo();				//デストラクタ

							//メンバ関数
	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	D3DXCOLOR				m_col;			//カラー
	static int				m_nFrameCnt;	//フラッシュカウント
	int						m_Cnt;			//カウント
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
};
#endif 