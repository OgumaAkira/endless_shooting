//*****************************************************************************
//
// 弾の処理 [bullet.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CPlayer;
class CEnemy;
class CInput;
class CButton;
class CBulletUI;
class CCombo;

//*****************************************************************************
//弾クラス宣言
//*****************************************************************************
class CBullet :public CScene2D
{
public:
	//構造体定義(タイプ)
	typedef enum
	{
		BULLET_TYPE_NONE = 0,	//何もない
		BULLET_TYPE_CURSOR,		//カーソル
		BULLET_TYPE_PLAYER,		//プレイヤー
		BULLET_TYPE_ENEMY,		//敵
		BULLET_TYPE_MAX			//最大数
	} BULLET_TYPE;
	
	CBullet();					//コンストラクタ
	~CBullet();					//デストラクタ

	//メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);			//初期化関数
	void Uninit(void);																				//終了関数
	void Update(void);																				//更新関数
	void Draw(void);																				//描画関数
	static HRESULT Load(void);																		//ロード関数
	static void UnLoad(void);																		//アンロード関数
private:
	//メンバ変数
	D3DXVECTOR3						m_move;			//移動量
	D3DXVECTOR3						m_pos;			//ポリゴンの位置
	D3DXVECTOR3						m_size;			//ポリゴンのサイズ
	int								m_nHP;			//ヒットポイント
	BULLET_TYPE						m_type;			//種類
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	static CBulletUI				*m_pBulletUI;	//弾UIのポイント
};
#endif 