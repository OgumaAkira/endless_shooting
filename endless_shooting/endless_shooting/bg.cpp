//*****************************************************************************
//
// 背景の処理 [bg.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "bg.h"
#include "button.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_SPACE01_TEXTURE ("data/TEXTURE/bg100.png")					//宇宙1のTEXTURE
#define BG_SPACE02_TEXTURE ("data/TEXTURE/bg101.png")					//宇宙2のTEXTURE
#define BG_SPACE03_TEXTURE ("data/TEXTURE/bg102.png")					//宇宙3のTEXTURE

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBg::m_pTexture[MAX_BG_TEXTURE] = {};		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBg::CBg(int nPriority) :CScene(nPriority)
{
	m_move = VECTOR3_DEFAULT;				//移動量
	m_pos = VECTOR3_DEFAULT;			// ポリゴンの位置
	m_size = VECTOR3_DEFAULT;			// ポリゴン大きさ
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//アニメーションパターンNo.
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//シーン2Dのポインタ配列
	}
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBg::~CBg()
{

}

//*****************************************************************************
//ロード関数
//*****************************************************************************
HRESULT CBg::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(宇宙1)
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE01_TEXTURE, &m_pTexture[BGTYPE_SPACE1]);

	//テクスチャの読み込み（宇宙2）
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE02_TEXTURE, &m_pTexture[BGTYPE_SPACE2]);

	//テクスチャの読み込み（宇宙3）
	D3DXCreateTextureFromFile(pDevice,
		BG_SPACE03_TEXTURE, &m_pTexture[BGTYPE_SPACE3]);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CBg::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < MAX_BG_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			//テクスチャの破棄
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CBg * CBg::Create()
{
	CBg *pBg = NULL;

	//背景のポインタが何も無かった場合
	if (pBg == NULL)
	{
		pBg = new CBg;
		pBg->Init();
	}
		return pBg;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CBg::Init()
{
	//背景の生成
	for (int nCntInit = 0; nCntInit < MAX_BG_TEXTURE; nCntInit++)
	{
		m_apScene2D[nCntInit] = NULL;

		if (m_apScene2D[nCntInit] == NULL)
		{
			m_apScene2D[nCntInit] = new CScene2D;
			m_apScene2D[nCntInit]->Init();
			m_apScene2D[nCntInit]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 ,0));
			m_apScene2D[nCntInit]->SetSize(D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT , 0));
			m_apScene2D[nCntInit]->BirdTexture(m_pTexture[nCntInit]);
			m_apScene2D[nCntInit]->SetObjType(OBJTYPE_BG);
		}
	}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CBg::Uninit(void)
{
	//背景の破棄
	for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			m_apScene2D[nCntUninit]->Uninit();
			delete m_apScene2D[nCntUninit];
			m_apScene2D[nCntUninit] = NULL;
		}
	}
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CBg::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		break;
	
	case CManager::MODE_GAME:
	//背景のテクスチャ座標設定
	for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			
			m_move += D3DXVECTOR3(0.001f , 0, 0);//移動量
			//背景をm_nPatternAnimで数を動かしてアニメーションする。
			m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0),
				D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0));
		}
	}
	break;

	case CManager::MODE_RESULT:
		//背景のテクスチャ座標設定
		for (int nCntUninit = 0; nCntUninit < MAX_BG_TEXTURE; nCntUninit++)
		{
			if (m_apScene2D[nCntUninit] != NULL)
			{

				m_move += D3DXVECTOR3(0.001f, 0, 0);//移動量
				//背景をm_nPatternAnimで数を動かしてアニメーションする。
				m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f)), 0),
					D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f) + 1.0f), 0));
			}
		}
		break;
	default:
		break;
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CBg::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < MAX_BG_TEXTURE; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}
