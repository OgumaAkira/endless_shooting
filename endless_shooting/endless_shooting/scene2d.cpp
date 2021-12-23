//*****************************************************************************
//
// シーン2Dの処理 [scene2D.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define POLYGON_CNT		(4)									//ポリゴンカウント回数
#define AT_VECTOR_A		(D3DXVECTOR2(0.0f, 0.0f))			//アニメーションテクスチャA
#define AT_VECTOR_B		(D3DXVECTOR2(1.0f, 1.0f))			//アニメーションテクスチャB
#define COLOR_DEFAULT	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//デフォルトカラー
#define MAX_NUMBER		(10)								//数字の画像を使う場合の数

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CSceneBase(nPriority)
{
	m_nPatternAnim      = 0;		//アニメーションパターン数
	m_nCounterAnim      = 0;		//アニメーションカウンター
	m_nCountAnim        = 0;		//アニメーションテクスチャ
	m_nCountAnimPattern = 0;		//アニメーションのパターン
	m_nLoop             = -1;		//ループするかどうか
	m_nSpeedTexture     = 0;		//テクスチャの移動速度
	m_nFlashFlame       = 0.0f;		//点滅用のカウンター
	m_fDivisionCounter  = 0.0f;		// スクロールのカウンター
	m_fDivisionBaseNum	= 0.0f;		//スクロールのカウンター
	m_fRotasion         = 0.0f;		//回転用変数
	m_fScaleNum         = 0.0f;		//拡大用変数
	m_fSubFlashNum      = 0.0f;		//ポリゴンの点灯用
	m_fSubNum           = 0.0f;		//ポリゴンのサブ点灯用
	m_fFadeSpeedNum     = 0.0f;		//フェードのスピード
	m_bDisappearFlag	= false;	//点滅用のフラグ
	m_bFadeOut			= false;	//フェードのフラグ
	m_bNumber			= false;	//使う数字のフラグ
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
// クリエイト関数
//*****************************************************************************
CScene2D * CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene2D *pScene2D = new CScene2D();

	//シーン2Dのポインタが何も無かった場合
	if (pScene2D != nullptr)
	{
		pScene2D->Init(pos,size);
	}
	return pScene2D;
}

//*****************************************************************************
// フェードクリエイト関数
//*****************************************************************************
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum)
{
	// オブジェクトを生成
	CScene2D* pScene = new CScene2D();

	// !nullcheck
	if (pScene != nullptr)
	{
		pScene->m_fFadeSpeedNum = fFadeNum;
		pScene->m_fSubFlashNum = 0.0f;
		pScene->GetColor().a = 0.0f;
		pScene->m_bFadeOut = true;

		// 初期化処理
		pScene->Init(pos, size);
	}

	return pScene;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CScene2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	SetPos(pos);		//座標
	SetSize(size);		//サイズ

	//頂点の生成

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CScene2D::Uninit(void)
{
	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene2D::Update(void)
{

}
//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene2D::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//アルファテストを有効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファテストの比較方法の設定(GREATERは基準値より大きい場合)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//アルファテストを無効化
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, nullptr);

}

//=============================================
// 頂点の生成関数
//=============================================
void CScene2D::CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		//バッファ

	if (m_bNumber == true)
	{
		//頂点バッファの生成
		pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_NUMBER,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pVtxBuff, nullptr);
	}
	else
	{
		//頂点バッファの生成
		pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pVtxBuff, nullptr);
	}

	//頂点情報
	VERTEX_2D *pVtx = nullptr;
	D3DXCOLOR color = GetColor();

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	for (int nVertex = 0; nVertex < NUM_VERTEX; nVertex++)
	{
		pVtx[nVertex].rhw = 1.0f;
		pVtx[nVertex].col = color;
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);
}

//=============================================
// 頂点の設定
//=============================================
void CScene2D::SetVertex(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;		//バッファ

	//頂点情報
	VERTEX_2D *pVtx = nullptr;
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR color = GetColor();

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	for (int nVertex = 0; nVertex < NUM_VERTEX; nVertex++)
	{
		pVtx[nVertex].rhw = 1.0f;
		pVtx[nVertex].col = color;
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);
}

//*****************************************************************************
// アニメーション初期化関数
//*****************************************************************************
void CScene2D::InitAnimation(int nPatternAnim, int nCounterAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;

	//頂点情報を設定
	//頂点情報
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		//バッファ

	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}
//*****************************************************************************
// アニメーション更新関数
//*****************************************************************************
void CScene2D::UpdateAnimation(void)
{
	//アニメーションのカウントを進めて、パターンを切り替える
	m_nCountAnim++;

	//頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)
	{
		m_nCountAnim = 0;		//アニメーションのカウントを0にする
		m_nCountAnimPattern++;	//アニメーションのパターンをカウントさせる
	}

	//アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		//数値を戻しておく
		m_nCountAnimPattern = 0;
		if (m_nLoop == 0)
		{
			Uninit();
		}
	}
	else
	{
		// 頂点情報を設定
		VERTEX_2D *pVtx = nullptr;
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ取得

																// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		pVtxBuff->Unlock();
	}
}

//*****************************************************************************
// テクスチャのスクロール情報を取得
//*****************************************************************************
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;

	////頂点情報を設定
	//VERTEX_2D *pVtx = nullptr;
	//LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	//バッファを取得

	////カウンターを進める
	//m_nCountAnim++;

	//if (m_nCountAnim>=m_nSpeedTexture)	//アニメーションの速さ
	//{
	//	// 頂点バッファをロックし、頂点情報へのポインタを取得
	//	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	//テクスチャ座標を更新
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

	// 頂点バッファをアンロックする
	//	pVtxBuff->Unlock();
	//
	//	m_fDivisionCounter += m_fDivisionBaseNum;
	//	m_nCountAnim = 0;
	//}
}

//*****************************************************************************
// テクスチャのスクロール情報を更新
//*****************************************************************************
void CScene2D::UpdateScroll(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	//バッファを取得

														//カウンターを進める
	m_nCountAnim++;

	if (m_nCountAnim >= m_nSpeedTexture)	//アニメーションの速さ
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// 頂点バッファをアンロックする
		pVtxBuff->Unlock();

		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCountAnim = 0;
	}
}

//*****************************************************************************
// 拡大関数
//*****************************************************************************
void CScene2D::ScaleUp(float fScaleUp)
{
	//情報取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	m_fScaleNum += fScaleUp;

	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y - (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (size.x / 2 * m_fScaleNum), pos.y + (size.y / 2 * m_fScaleNum), 0.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

}

//*****************************************************************************
// ポリゴンの点滅
//*****************************************************************************
void CScene2D::FlashPolygon(int nFlashFlame)
{
	//頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラーの減算
	m_fSubFlashNum += m_fSubNum;

	//上限にいったら
	if (m_fSubFlashNum >= 1.0f)
	{
		m_fSubFlashNum = 1.0f;
		m_bDisappearFlag = true;
	}
	else if (m_fSubFlashNum <= 0.0f)
	{
		m_fSubFlashNum = 0;
		m_fSubNum *= -1;
	}

}

//*****************************************************************************
// フェードアウト
//*****************************************************************************
void CScene2D::FadeOut(float fSpeed)
{
	//頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//透明度の値
	m_fSubFlashNum += fSpeed;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//アルファ値を足す
	GetColor().a = m_fSubFlashNum;

	//カラー情報の更新
	D3DXCOLOR color = GetColor();

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[1].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[2].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);
	pVtx[3].col = D3DXCOLOR(color.r, color.g, color.b, color.a - m_fSubFlashNum);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

	// 引く値が無くなったら
	if (m_fSubFlashNum > 1.0f)
	{
		m_fSubFlashNum = 1.0f;
		m_bFadeOut = false;
	}
}

//*****************************************************************************
//ナンバーアニメーション関数
//*****************************************************************************
void CScene2D::NumberAnimation(int nNumber)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	//頂点バッファをロック
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ取得
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 1.0f);

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//*****************************************************************************
//色情報格納関数
//*****************************************************************************
void CScene2D::SetCol(D3DXCOLOR col)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ取得

	//色の設定
	SetColor(col);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定(0~255の数値で設定)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,aは0~255の範囲で決めること
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:レッド g:グリーン　b:ブルー
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //aは、透明度を表している
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//*****************************************************************************
//回転情報格納関数
//*****************************************************************************
void CScene2D::SetRotation(float rotasion)
{
	//情報取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// 回転の値を加算
	rotasion += m_fRotasion;

	float r = sqrtf(powf(size.x / 2, 2.0) + powf(size.x / 2, 2.0));	//半径

	float fTheta = atan2(size.x / 2, size.x / 2);					//シータ

	float XAngle = r * cos(fTheta + rotasion);	//Xの角度
	float YAngle = r * sin(fTheta + rotasion);	//Xの角度

	// 頂点情報を設定
	VERTEX_2D *pVtx = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();		// バッファ取得

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[1].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[2].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);
	XAngle = r * cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r * sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[3].pos = D3DXVECTOR3(pos.x + XAngle, pos.y + YAngle, 0.0f);

	//頂点バッファをアンロック
	pVtxBuff->Unlock();

	//回転量
	m_fRotasion += 0.01;
}

//*****************************************************************************
//拡大情報関数
//*****************************************************************************
void CScene2D::SetScale(const float & fScale)
{
	m_fScaleNum = fScale;
}
