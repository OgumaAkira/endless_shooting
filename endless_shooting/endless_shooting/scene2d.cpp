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

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"
#include "input.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pTexture		= NULL;				//テクスチャの情報
	m_pVtxBuff		= NULL;				//頂点バッファの情報
	m_pos			= VECTOR_DEFAULT;	// ポリゴンの位置
	m_size			= VECTOR_DEFAULT;	// ポリゴンの大きさ
	m_tex			= AT_VECTOR_A;		//テスクチャA
	m_tex2			= AT_VECTOR_B;		//テスクチャB
	m_color			= COLOR_DEFAULT;	//カラー
	m_nCounterAnim	= 0;				//アニメーションカウント
	m_nPatternAnim	= 0;				//アニメーションパターンNo.

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
CScene2D * CScene2D::Create()
{
	CScene2D *pScene2D = NULL;

	//シーン2Dのポインタが何も無かった場合
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CScene2D::Init(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点情報を設定
	VERTEX_2D *pVtx;


	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//右下

	for (int nCntInit = 0; nCntInit < POLYGON_CNT; nCntInit++)
	{
		pVtx[nCntInit].rhw = 1.0f;				//rhwの設定
		pVtx[nCntInit].col = D3DXCOLOR(m_color);//カラーの設定
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CScene2D::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene2D::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//右下

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);//左上
	pVtx[1].tex = D3DXVECTOR2(m_tex2.x, m_tex.y);//右上
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex2.y);//左下
	pVtx[3].tex = D3DXVECTOR2(m_tex2.x, m_tex2.y);//右下

	for (int nCntUpdata = 0; nCntUpdata < POLYGON_CNT; nCntUpdata++)
	{
		
		pVtx[nCntUpdata].rhw = 1.0f;				//rhwの設定
		pVtx[nCntUpdata].col = D3DXCOLOR(m_color);	//カラーの設定
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// アルファブレンディングを行なう
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// アルファブレンディングステートを設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージの設定
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

	//テクスチャステージ：アルファ要素の設定
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
 	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);

}

//*****************************************************************************
// テクスチャ情報格納関数
//*****************************************************************************
void CScene2D::SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_tex = tex;
	m_tex2 = D3DXVECTOR2(tex2.x + 1.0f, tex2.y + 1.0f);
	pVtx[0].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex.y + 0.0f);	//左上
	pVtx[1].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex.y + 0.0f);	//右上
	pVtx[2].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex2.y + 1.0f);	//左下
	pVtx[3].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex2.y + 1.0f);	//右下
 
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
// アニメーションテクスチャ関数
//*****************************************************************************
void CScene2D::AnimationTexture(OBJTYPE objType, int PatternAnim, int CounterAnim)
{
	//TEXTUREとPRIORITYを最大数までカウントを回す。
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			//シーンのポインタの中身があった場合
			if (pScene != NULL)
			{
				 OBJTYPE ObjType = pScene->GetObjType();
				//オブジェクトタイプ指定
				if (ObjType == objType)
				{
					//アニメーションカウントの数値まで行った場合
					if (m_nCounterAnim == CounterAnim)
					{
						m_nPatternAnim++;
						SetTex(D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0),
							D3DXVECTOR2(m_nPatternAnim * 0.125f - 1.0f, 0));
						m_nCounterAnim = 0;
					}
					m_nCounterAnim++;
					//アニメーションパターンが最大値までいったら
					if (m_nPatternAnim > PatternAnim)
					{
						Uninit();
					}
				}
			}
		}
	}
}
