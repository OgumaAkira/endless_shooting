//*****************************************************************************
//
// レンダラー処理 [renderer.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//レンダリングのクラス宣言
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();												//コンストラクタ
	~CRenderer();												//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//初期化関数
	void Uninit(void);											//終了関数
	void Update(void);											//更新関数
	void Draw(void);											//描画関数
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//デバイスの取得

private:
	//メンバ関数
	void DrawFPS(void);

	//メンバ変数
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
};
#endif // !_RENDERER_H_

