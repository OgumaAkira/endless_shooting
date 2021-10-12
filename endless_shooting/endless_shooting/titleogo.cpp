//インクルードファイル
#include "titlelogo.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CTitleLogo::m_pTexture = {};		//テクスチャの情報
int					CTitleLogo::m_nFrameCnt = 0;		//点滅カウント
//コンストラクタ
CTitleLogo::CTitleLogo(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(1, 1, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_Cnt = 0;
}

//デストラクタ
CTitleLogo::~CTitleLogo()
{

}

//クリエイト関数
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTitleLogo *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CTitleLogo;
		pButton->Init(pos, size);
	}
	return pButton;
}

//初期化関数
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_Cnt = 5;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	return S_OK;
}

//終了関数
void CTitleLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CTitleLogo::Update(void)
{
	m_pos = GetPosition();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
	//if (m_bUse == true)
	//{
	//	m_nFrameCnt++;
	//	if (m_nFrameCnt <= 30)
	//	{
	//		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	//	}
	//	else if (m_nFrameCnt > 30)
	//	{
	//		SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	//	}
	//	if (m_nFrameCnt == 60)
	//	{
	//		m_nFrameCnt = 0;
	//		m_Cnt--;
	//	}
	//	if (m_Cnt == 0)
	//	{
	//		Uninit();
	//		m_bUse = false;
	//	}
	//}
}

//描画関数
void CTitleLogo::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CTitleLogo::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		GAMETITLE_TEXTURE, &m_pTexture);

	return S_OK;
}

void CTitleLogo::UnLoad(void)
{

	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}