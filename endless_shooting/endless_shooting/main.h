//*****************************************************************************
//
// メイン処理 [main.h]
// Author : 小熊 朗
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include <time.h>
#include <d3dx9.h>
#include <xaudio2.h> //サウンド処理で必要
#include <windows.h>
#define DIRECTINPUT_VERSION (0x0800) //警告対処用 dinput.hの直前に書く
#include <dinput.h>
#include <vector>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"										//ウインドウのクラス名
#define WINDOW_NAME		"DISK BREAK"									//ウインドウのキャプション名
#define SCREEN_WIDTH	(1920)											//ウィンドウの横
#define SCREEN_HEIGHT	(1080)											//ウィンドウの縦
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX (4)													//頂点数
#define NUM_POLYGON (2)													//ポリゴン数
#define NUM_KEY_MAX (256)												//キーボードの最大数
#define NUM_MOUSE_MAX (4)												//マウスキーの最大数
#define BULLET_SIZEX (150.0f)											//弾Xの長さ
#define BULLET_SIZEY (150.0f)											//弾Yの長さ
#define	MAX_FLASHING (30)												//フラッシュするフレーム秒数
#define MAX_BULLET	 (5)												//最大弾数
#define DEBUG_SOUND (0)

//テクスチャマクロ
#define MAX_TEXTURE (516)												//テクスチャの最大枚数
#define BULLETUI_TEXTURE ("data/TEXTURE/BULLET.png")					//残弾のTEXTURE

#define ENEMY_TEXTURE2 ("data/TEXTURE/敵　UFO１.png")					//敵のTEXTURE

#define PAUSEBUTTON_TEXTURE ("data/TEXTURE/PAUSE_WINDOW.png")			//ポーズのテクスチャ
#define TITLERETURNBUTTON_TEXTURE ("data/TEXTURE/TITLE_RETURN.png")		//TITLEに戻るボタンのテクスチャ
#define GAMERETURNBUTTON_TEXTURE ("data/TEXTURE/GAME_RETURN.png")		//ゲームに戻るボタンのテクスチャ
#define GAMETITLE_TEXTURE ("data/TEXTURE/GAMETITLE.png")				//タイトルテクスチャ
#define TUTORIAL_TEXTURE ("data/TEXTURE/TUTORIAL.png")					//チュートリアルのテクスチャ
#define HISCOREUI_TEXTURE ("data/TEXTURE/HISCORE.png")					//ハイスコアのテクスチャ
#define MYSCOREUI_TEXTURE ("data/TEXTURE/YOURSCORE.png")				//ハイスコアのテクスチャ
#define SPEEDUP_TEXTURE ("data/TEXTURE/SPEEDUP!.png")					//スピードアップのテクスチャ
#define NUMBER_TEXTURE ("data/TEXTURE/number_HGM.png")					//ナンバーのテクスチャ
#define COMBOBONUS_TEXTURE ("data/TEXTURE/COMBO_BONUS.png")					//コンボボーナスのテクスチャ

#define VECTOR3_DEFAULT		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))//デフォルトベクター
#define ZeroVector2			(D3DXVECTOR2(0.0f, 0.0f))
#define ZeroVector3			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WhiteColor			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define BlackColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))

//ボタンマクロ
#define BUTTON_POSX (940.0f)//ボタンのXの長さ
#define BUTTON_POSY (800.0f)//ボタンのYの長さ

//エネミーマクロ
#define ENEMY_POSX (150.0f)//敵のXの長さ
#define ENEMY_POSY (150.0f)//敵のYの長さ
#define ENEMY_SIZEX (250.0f)//敵のXの長さ
#define ENEMY_SIZEY (150.0f)//敵のYの長さ


//スコアナンバーマクロ
#define MAX_SCORE_NUMBER (10)		//スコアナンバーの最大数
#define SCORE_POS_X (35)			//スコア一桁のXの位置
#define SCORE_POS_Y (70)			//スコア一桁のYの位置
#define SCORE_SIZE_X (35)			//スコア一桁のXの大きさ
#define SCORE_SIZE_Y (70)			//スコア一桁のYの大きさ

//コンボナンバーマクロ
#define MAX_COMBO_NUMBER (2)		//スコアナンバーの最大数
#define COMBO_POS_X (35)			//スコア一桁のXの位置
#define COMBO_POS_Y (140)			//スコア一桁のYの位置
#define COMBO_SIZE_X (35)			//スコア一桁のXの大きさ
#define COMBO_SIZE_Y (70)			//スコア一桁のYの大きさ

//スピードアップUIのマクロ
#define SPEEDUP_POS_X (SCREEN_WIDTH / 2)			//スコア一桁のXの位置
#define SPEEDUP_POS_Y (SCREEN_HEIGHT / 2.5)			//スコア一桁のYの位置
#define SPEEDUP_SIZE_X (SCREEN_WIDTH / 2.5)			//スコア一桁のXの大きさ
#define SPEEDUP_SIZE_Y (1000.0f)					//スコア一桁のYの大きさ

//スコアUIのマクロ
#define SCOREUI_TEXTURE ("data/TEXTURE/SCORE.png")	//スコアのテクスチャ
#define SCOREUI_POSX (100.0f)						//スコアUIのXの長さ
#define SCOREUI_POSY (70.0f)						//スコアUIのYの長さ
#define SCOREUI_SIZEX (200.0f)						//スコアUIのXの長さ
#define SCOREUI_SIZEY (70.0f)						//スコアUIのYの長さ

//コンボUIのマクロ
#define COMBOUI_TEXTURE ("data/TEXTURE/COMBO.png")	//スコアのテクスチャ
#define COMBOUI_POSX (100.0f)						//スコアUIのXの長さ
#define COMBOUI_POSY (140.0f)						//スコアUIのYの長さ
#define COMBOUI_SIZEX (200.0f)						//スコアUIのXの長さ
#define COMBOUI_SIZEY (70.0f)						//スコアUIのYの長さ

//ウィンドウ用
#define WindowVersion (0)

//フルスクリーン用
#define FullScreenVersion (1)

using namespace std;         //  名前空間指定

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標1
	float rhw;				//座標変換用係数(1.0で固定）
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ
}VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);
#endif