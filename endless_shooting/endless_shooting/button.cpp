//*****************************************************************************
//
// ボタン処理 [button.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "button.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define TITELBUTTON_TEXTURE		("data/TEXTURE/SHOOT THE STARTBUTTON.png")	//Titleボタンのテクスチャ
#define RESULTBUTTON_TEXTURE	("data/TEXTURE/RETURN TO TITLE.png")		//Resultボタンのテクスチャ
#define MAX_CNT_BUTTON			(5)
#define RED_BUTTON				(D3DCOLOR_RGBA(255, 0, 0, 255))
#define DEFAULT_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))
//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CButton::m_apTexture[BUTTONTYPE_MAX] = {};	//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CButton::CButton(int nPriority) :CScene2D(nPriority)
{
	m_pos = VECTOR_DEFAULT;			// ボタンの位置
	m_size = VECTOR_DEFAULT;			// ポリゴン大きさ
	m_bButton = false;
	m_state = BUTTONSTATE_NORMAL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CButton::~CButton()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CButton *pButton = NULL;
	//ボタンのポインタが何も無かった場合
	if (pButton == NULL)
	{
		pButton = new CButton;
		pButton->Init(pos, size, type);
		pButton->SetObjType(OBJTYPE_BUTTON);	//ボタンのオブジェクト指定
	}
	return pButton;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CButton::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TITELBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_TITLE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RESULTBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_RESULT]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		GAMERETURNBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSEGAME]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TITLERETURNBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSETITLE]);
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PAUSEBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_PAUSE]); 
	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CButton::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_CNT_BUTTON; nCount++)
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
HRESULT CButton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);		//位置取得
	SetPosition(m_pos);							//位置格納
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ取得
	SetSize(m_size);							//大きさ格納
	m_bButton = true;							//ボタンの状態
	m_state = BUTTONSTATE_NORMAL;				//初期状態
	BirdTexture(m_apTexture[type]);				//テクスチャの情報をscene2dへ格納
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CButton::Update(void)
{
	CSound *pSound = CManager::GetSound();	//サウンド情報取得
	m_pFade = CManager::GetFade();			//フェード情報取得
	CScene2D::Update();

	//ボタンの状態
	switch (m_state)
	{
	//タイトル画面のボタン
	case BUTTONSTATE_TITLE:
		if (m_bButton == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bButton = false;
		}
			//色の変更
			SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));//青
			m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	//リザルト画面のボタン
	case BUTTONSTATE_RESULT:
		if (m_bButton == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bButton = false;
		}
		//色の変更
		SetColor(RED_BUTTON);//赤
		m_pFade->SetFade(CFade::FADESTATE_IN); 
		break;

	case BUTTONSTATE_PAUSETITLE:
		//色の変更
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//赤
		CManager::SetMode(CManager::MODE_TITLE);
		break;

	case BUTTONSTATE_PAUSEGAME:
		//色の変更
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//赤	
		pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);
		CManager::SetMode(CManager::MODE_GAME);
		break;

	//ボタンの初期設定
	case BUTTONSTATE_NORMAL:
		//初期色
		SetColor(DEFAULT_COLOR);
		break;

	default:
		break;
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CButton::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//ポーズ画面ボタン関数
//*****************************************************************************
void CButton::PauseButton(void)
{
	POINT posPoint;
	GetCursorPos(&posPoint);		//マウス座標を取得する
	if (BUTTON_POSX - m_size.x / 2 <= posPoint.x&&
		BUTTON_POSX + m_size.x / 2 >= posPoint.x&&
		BUTTON_POSY / 2 - m_size.y / 2 <= posPoint.y&&
		BUTTON_POSY / 2 + m_size.y / 2 >= posPoint.y)
	{
		m_state = BUTTONSTATE_PAUSEGAME;
	}
	else if (BUTTON_POSX - m_size.x / 2 <= posPoint.x&&
			BUTTON_POSX + m_size.x / 2 >= posPoint.x&&
			BUTTON_POSY - m_size.y / 2 <= posPoint.y&&
			BUTTON_POSY + m_size.y / 2 >= posPoint.y)
	{
		m_state = BUTTONSTATE_PAUSETITLE;
	}
}

//*****************************************************************************
//ボタン状態取得関数
//*****************************************************************************
void CButton::SetButton(void)
{
	//ボタンが通常状態の場合
	if (m_state == BUTTONSTATE_NORMAL)
	{
		//モードの状態
		switch (CManager::GetMode())
		{
			//タイトル画面だった場合
		case CManager::MODE_TITLE:
			m_state = BUTTONSTATE_TITLE;	//タイトルボタンへ
			break;

			//ポーズ画面だった場合
		case CManager::MODE_PAUSE:
			PauseButton();
			break;

			//リザルト画面だった場合
		case CManager::MODE_RESULT:
			m_state = BUTTONSTATE_RESULT;	//リザルトボタンへ
			break;

		default:
			break;
		}
	}
}