//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
int						g_nCountFPS;			// FPSカウンタ
#if 0
bool					g_bScreen = true;		//スクリーン変更
#endif // 0
//*****************************************************************************
// メイン関数
//*****************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
#if WindowVersion
		// ウィンドウの作成
		hWnd = CreateWindow(CLASS_NAME,
			WINDOW_NAME,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			(rect.right - rect.left),
			(rect.bottom - rect.top),
			NULL,
			NULL,
			hInstance,
			NULL);
#endif
#if FullScreenVersion
		// スクリーンの作成
		hWnd = CreateWindow(CLASS_NAME,
			WINDOW_NAME,
			WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			(rect.right - rect.left),
			(rect.bottom - rect.top),
			NULL,
			NULL,
			hInstance,
			NULL);
#endif // FullScreenVersion


	CManager *pManager;

	pManager = new CManager;
	pManager->Init(hInstance, hWnd, false);
	
	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
#ifdef _DEBUG
			 // FPSを算出
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

				//マネージャーの更新処理
				pManager->Update();
				//マネージャーの描画処理
				pManager->Draw();

 				dwFrameCount++;
			}
		}
	}
	if (pManager != NULL)
	{
		// 終了処理
		pManager->Uninit();	
		//中身を消去
		delete pManager;
		//中身を空にする
		pManager = NULL;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//*****************************************************************************
// ウインドウプロシージャ
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		ShowCursor(false);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
#if 0
		case VK_NUMPAD0:
			if (g_bScreen == false)
			{
				g_bScreen = true;
			}
			else if (g_bScreen == true)
			{
				g_bScreen = false;
			}
			break;
#endif
		default:
			break;
		}

	}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFPS(void)
{
	return g_nCountFPS;
}