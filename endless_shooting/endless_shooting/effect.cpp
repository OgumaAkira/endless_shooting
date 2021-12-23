//*****************************************************************************
//
// 爆発の処理 [explosion.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define EFFECT_COUNTERANIM	(1)									//アニメーションカウンター
#define EFFECT_PATTERNANIM	(16)								//アニメーションNo.
#define EFFECT_ALPHATHIN	(0.03f)								//カラーを薄くする(アルファ値減少)
#define BULLET_TEXTURE	("data/TEXTURE/YellowParticle.png")		//爆発テクスチャ

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CEffect::m_pTexture = NULL;		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CEffect::CEffect()
{	
	m_move = VECTOR3_DEFAULT;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CEffect::~CEffect()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move, int type)
{
	CEffect *pEffect;
	pEffect = NULL;
	//敵のポインタが何もなかった場合
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		if (type == 1)
		{	
				pEffect->Smoke(pos, size, move, col);
		}		
		pEffect->SetObjType(OBJTYPE_EFFECT);	//オブジェクト指定
	}
	return pEffect;
}

//*****************************************************************************
//煙演出関数
//*****************************************************************************
void CEffect::Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{

		//エフェクトの設定
		float fAngle = (rand() % 314 / 100.0f)*(rand() % 100);	//角度計算
		D3DXVECTOR3 actualMove = D3DXVECTOR3((float)sin(fAngle)*move.x,
											(float)cos(fAngle)*move.y, 0.0f);//移動方向をセット
		//爆発の初期設定

		m_move = actualMove;				//移動量
		SetColor(col);						//色格納
		//BirdTexture(m_pTexture);			//テクスチャの情報をscene2dに持ってく
		Init(pos, size);
}

//*****************************************************************************
//煙演出関数
//*****************************************************************************
void CEffect::ClickEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{

	//エフェクトの設定
	float fAngle = (rand() % 314 / 100.0f)*(rand() % 100);	//角度計算
	D3DXVECTOR3 actualMove = -D3DXVECTOR3((float)sin(fAngle)*move.x, 
										(float)cos(fAngle)*move.y, 0.0f);//移動方向をセット
	//弾の初期設定
	m_move = actualMove;				//移動量
	SetColor(col);						//色格納
	//BirdTexture(m_pTexture);			//テクスチャの情報をscene2dに持ってく
	Init(pos, size);
}
//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CEffect::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,BULLET_TEXTURE, &m_pTexture);
	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CEffect::UnLoad(void)
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
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//更新位置を取得
	D3DXVECTOR3 size = GetSize();				//更新サイズを取得
	D3DXCOLOR	col = GetColor();				//更新カラーを取得

	pos += m_move;		//移動量をプラスする
	col -= D3DXCOLOR(0, EFFECT_ALPHATHIN, EFFECT_ALPHATHIN, EFFECT_ALPHATHIN);
	
	SetPos(pos);	//位置格納
	SetSize(size);		//サイズ格納
	SetColor(col);		//カラー格納

	CScene2D::Update();

	//見えなくなったら消す
	if (col.a < 0)
	{
		Uninit();
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CEffect::Draw(void)
{
	CScene2D::Draw();
}
