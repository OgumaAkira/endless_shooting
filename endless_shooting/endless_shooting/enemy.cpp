//*****************************************************************************
//
// 敵の処理 [enemy.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CEnemy::m_apTexture[MAX_ENEMY] = {};		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nHP = 0;								//ライフ
	m_pScore = 0;							//スコア
	m_state = ENEMYSTATE_NORMAL;			//状態
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CEnemy *pEnemy = NULL;
	//敵のポインタが何もなかった場合
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(pos, size, nType);
		pEnemy->SetObjType(OBJTYPE_ENEMY);			//オブジェクト指定
		pEnemy->m_move = move;
	}
	return pEnemy;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CEnemy::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE2, &m_apTexture[ENEMYTYPE_NORMAL]);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}
//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);		//位置
	SetPosition(m_pos);							//位置格納
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);							//大きさ格納
	m_nHP = 1;									//ライフ
	m_state = ENEMYSTATE_NORMAL;				//状態
	BirdTexture(m_apTexture[nType]);			//テクスチャの情報をscene2dに持ってく
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CEnemy::Update(void)
{
	m_pos = GetPosition();						//更新位置を取得
	CSound *pSound = CManager::GetSound();		//サウンド取得
	CScene2D::Update();							//シーンの更新
	int nCountEnemy = 1;						//敵の数

	//ポーズ画面以外の場合
	if (CManager::GetMode() != CManager::MODE_PAUSE)
	{
		Range();
	}

	//敵の状態
	switch (m_state)
	{
	//通常
	case ENEMYSTATE_NORMAL:
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));			//色の設定
		break;

		//敵が倒された時
	case ENEMYRSTATE_DEATH:
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);	//サウンド
		CExplosion::Create(m_pos, D3DXVECTOR3(300, 300, 0));						//爆発演出
		Uninit();
		CGame::SetGameState(CGame::GAMESTATE_ENEMYBREAK);		//ゲームの状態
		break;

	default:
		break;
	}
	SetPosition(m_pos);											//プレイヤーの位置更新
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//ダメージ関数
//*****************************************************************************
void CEnemy::HitDamege(int nDamege)
{
	m_nHP -= nDamege;					//ダメージ計算
	
	//ライフが0になった場合
	if (m_nHP <= 0)
	{
		m_state = ENEMYRSTATE_DEATH;	//敵の死亡状態
	}
}

//*****************************************************************************
//移動範囲関数
//*****************************************************************************
void CEnemy::Range(void)
{
	m_pos += m_move;//敵の移動速度

	//画面外へ行く場合画面内に反射させる。
	if (m_pos.x - (m_size.x / 2) < 0)
	{
		//左
		m_move.x *= -1;
	}
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH)
	{
		//右
		m_move.x *= -1;
	}
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT)
	{
		//上
		m_move.y *= -1;
	}
	if (m_pos.y - (m_size.y / 2) < 0)
	{
		//下
		m_move.y *= -1;
	}
}
