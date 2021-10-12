//*****************************************************************************
//
// 敵の処理 [enemy.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_ENEMY (2)//画面に出す敵の最大数

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CEnemy :public CScene2D
{
public:

	//構造体定義(状態)
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,		//通常
		ENEMYRSTATE_DEATH,			//撃墜
		ENEMYS_MAX,					//最大数
	}ENEMYSTATE;

	//構造体定義(種類)
	typedef enum
	{
		ENEMYTYPE_NORMAL = 0,		//敵1
		ENEMYTYPE_MAX				//最大数
	}ENEMYTYPE;

	CEnemy(int nPriority = 0);				//コンストラクタ
	~CEnemy();								//デストラクタ

	//メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType);//クリエイト
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType);							//初期化処理
	void Uninit(void);																			//終了処理
	void Update(void);																			//更新処理
	void Draw(void);																			//描画処理
	void CEnemy::HitDamege(int nDamege);														//ヒットダメージ関数
	void Range(void);																			//移動範囲
	static HRESULT Load(void);																	//読み込み処理
	static void UnLoad(void);																	//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;						// ポリゴンの現在位置
	D3DXVECTOR3				m_posold;					// ポリゴンの過去位置
	D3DXVECTOR3				m_move;						// ポリゴンの移動量
	D3DXVECTOR3				m_size;						// ポリゴン大きさ
	ENEMYSTATE				m_state;					//状態
	int						m_nCountState;				//ステートカウンター
	int						m_nHP;						//ヒットポイント
	bool					m_bLand;					//当たり判定
	bool					m_bContact;					//当たり判定2
	CInput* m_pInput;									//デバッグ操作用
	CScore* m_pScore;									//スコアのポインタ
	static LPDIRECT3DTEXTURE9		m_apTexture[MAX_ENEMY];		//テクスチャの情報
};
#endif 