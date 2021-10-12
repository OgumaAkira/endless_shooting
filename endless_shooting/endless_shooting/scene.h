//*****************************************************************************
//
// シーンの処理 [scene.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//オブジェクトクラス宣言
//*****************************************************************************
class CScene
{
public:
	//構造体定義(種類)
	typedef enum
	{
		OBJTYPE_NONE = 0,	//何もない
		OBJTYPE_CURSOR,		//カーソル
		OBJTYPE_PLAYER ,	//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_BULLET,		//弾
		OBJTYPE_EXPLOSION,	//爆発
		OBJTYPE_EFFECT,		//エフェクト
		OBJTYPE_BG,			//背景
		OBJTYPE_BUTTON,		//ボタン
		OBJTYPE_TITLE,		//タイトル画面
		OBJTYPE_GAME,		//ゲーム画面
		OBJTYPE_RESULT,		//リザルト画面
		OBJTYPE_PAUSE,		//ポーズ画面
		OBJTYPE_COMBOUI,	//コンボUI
		OBJTYPE_MAX			//最大数
	}OBJTYPE;

	CScene(int nPriority = 0);			//コンストラクタ
	virtual~CScene();					//デストラクタ

	//メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;		//初期化処理
	virtual void Uninit(void) = 0;		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual void Draw(void) = 0;		//描画処理


	void SetObjType(OBJTYPE objType) { m_ObjType = objType; };									//オブジェクト情報格納関数
	OBJTYPE GetObjType(void) { return m_ObjType; };												//オブジェクト情報取得関数
	static CScene *GetScene(int Priority, int scene) { return m_apScene[Priority][scene]; }		//シーン情報取得関数
	static void UpdateAll(void);																//更新関数
	static void DrawAll(void);																	//描画関数
	static void ReleaseAll(void);																//終了関数
	static void	Select(int Priority);

protected:
	void Release(void);																			//終了関数

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_TEXTURE];	//シーンの配列ポインタ
	static int m_nNumAll;									//オブジェクトの総数
	int m_nID;												//テクスチャの番号
	OBJTYPE m_ObjType;										//オブジェクトの種類
	int m_Priority;											//優先順位
};
#endif // !_RENDERER_H_