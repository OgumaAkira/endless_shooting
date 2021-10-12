//*****************************************************************************
//
// バレット処理 [bullet.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define EFFECT_COUNTERANIM	(1)/								//アニメーションカウンター
#define EFFECT_PATTERNANIM	(16)								//アニメーションNo.
#define EFFECT_ALPHATHIN	(0.03f)								//カラーを薄くする(アルファ値減少)
#define BULLET_TEXTURE	("data/TEXTURE/bullet000.png")	//爆発テクスチャ

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "bulletUI.h"
#include "effect.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		CBullet::m_pTexture = NULL;		//テクスチャの情報
CBulletUI				*CBullet::m_pBulletUI = NULL;	//残弾のポインタ

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBullet::CBullet()
{
	m_pos = VECTOR3_DEFAULT;			//位置
	m_size = VECTOR3_DEFAULT;			//大きさ
	m_move = VECTOR3_DEFAULT;			//移動量
	m_nHP = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBullet::~CBullet()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CBullet *pBullet = NULL;

	//バレットのポインタが何も無かった場合
	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		pBullet->Init(pos, size, move, type);
		pBullet->SetObjType(OBJTYPE_BULLET);	//オブジェクトタイプ指定
	}
	return pBullet;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CBullet::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CBullet::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	//弾の初期設定
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	m_size = D3DXVECTOR3(size.x, size.y, 0);//大きさ　
	m_move = move;							//移動量
	m_nHP = 1;								//ヒットポイント
	m_type = type;							//タイプ
	BirdTexture(m_pTexture);				//テクスチャの情報をscene2dに持ってく
	SetObjType(CScene::OBJTYPE_BULLET);		//オブジェクトタイプ指定
	SetPosition(m_pos);						//初期ポジション指定
	SetSize(m_size);						//初期の大きさ指定
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CBullet::Uninit(void)
{
	CScene2D::Uninit();	
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CBullet::Update(void)
{
	CScene2D::Update();
	m_nHP--;	//弾のライフ

	//当たり判定
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		bool bHitEnemy = false;		//判定なし
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				//敵の当たり判定
				if ((objType == OBJTYPE_ENEMY) && (m_type == BULLET_TYPE_PLAYER))
				{
					CEnemy *pEnemy = CManager::GetEnemy();						//敵の情報を取得
					CScene2D *pScene2d = (CScene2D*)pScene;						//キャスト
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//位置を取得
					D3DXVECTOR3 size = pScene2d->GetSize();						//大きさを取得

					//敵を当てた場合
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CEnemy *pEnemy = (CEnemy*)pScene;	//キャスト;
						pEnemy->HitDamege(1);				//敵へのダメージを取得
						bHitEnemy = true;					//判定あり
						break;
					}
				}
				//ボタンの当たり判定
				else if ((objType == OBJTYPE_BUTTON) && (m_type == BULLET_TYPE_CURSOR))
				{
					CButton *pButton = CManager::GetButton();					//ボタンの当たり判定
					CScene2D *pScene2d = (CScene2D*)pScene;						//キャスト
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//位置
					D3DXVECTOR3 size = pScene2d->GetSize();						//大きさ
					
					//ボタンの当たり判定
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CButton *pButton = (CButton*)pScene;	//キャスト;
						pButton->SetButton();					//ボタン情報格納関数
					}
				}
			}
		}
		//判定ありのとき
		if (bHitEnemy == true)
		{ 
			break;
		}
	}
	//弾が消えるとき
	if (m_nHP <= 0)
	{
		//タイプがプレイヤーの弾であれば
		if (m_type == BULLET_TYPE_PLAYER)
		{
			//発生させる数をループ
			for (int nCntEffect = 0; nCntEffect < 100; nCntEffect++)
			{
				CEffect::Create(m_pos, m_size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f), 1);	//爆発生成
			}
			m_pBulletUI->SetbUse();				//点滅スイッチ情報格納関数
		}
		Uninit();								//終了関数
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
