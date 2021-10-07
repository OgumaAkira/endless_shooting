//*****************************************************************************
//
// プレイヤーの処理 [player.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define RANGE_MAX (90)
#define MARKERCOLOR_RED		(D3DCOLOR_RGBA(255, 0, 0, 255))
#define MARKERCOLOR_YELLOW	(D3DCOLOR_RGBA(255, 255, 255, 255))
#define PLAYER_TEXTURE ("data/TEXTURE/TargetMarker.png")		//プレイヤーのTEXTURE
#define PLAYER_SIZEX (150.0f)									//プレイヤーのXの長さ
#define PLAYER_SIZEY (150.0f)									//プレイヤーのYの長さ

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"
#include "enemy.h"

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CPlayer:public CScene2D
{
public:
	CPlayer(int nPriority = 11);				//コンストラクタ
	~CPlayer();									//デストラクタ

	//メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size );	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//初期化関数
	void Uninit(void);															//終了関数
	void Update(void);															//更新関数
	void Draw(void);															//描画関数
	void MarkerColor(void);														//マーカーカラ-関数
	void Range(void);															//移動範囲関数
	void MarkerObject(void);													//オブジェクト指定関数
	void PlayerInput(void);														//自機入力関数
	static HRESULT Load(void);													//ロード関数
	static void UnLoad(void);													//アンロード関数
	
private:
	//メンバ変数
	D3DXVECTOR3						m_pos;			// ポリゴンの位置
	D3DXVECTOR3						m_size;			// ポリゴン大きさ
	int								m_nColor;		//色
	int								m_nHP;			//ライフ
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	CFade							*m_pFade;		//フェードのポインタ
	CInput							*m_pInput;		//入力のポインタ
};
#endif 