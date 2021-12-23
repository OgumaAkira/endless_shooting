#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//*****************************************************************************
//
// リソースマネージャー処理  [resource_manager.h]
// Author : Oguma Akira
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CTexture;
class CSound;

//*****************************************************************************
//リソースマネージャークラス
//*****************************************************************************
class CResourceManager
{
public:
	~CResourceManager();

	HRESULT Init(void);//初期化関数
	void LoadAll(void);//全ロード関数
	void UnLoadAll(void);//全アンロード関数

	static CResourceManager *GetInstace(void);//インスタンス取得

	//Get関数
	CTexture *GetTextureClass(void) { return m_pTexture; }
	CSound *GetSoundClass(void) { return m_pSound; }

private:
	CResourceManager();		//コンストラクタ

	//ポインタ類
	static CResourceManager *m_pResourceManager;	//リソースマネージャー
	CTexture *m_pTexture;	//テクスチャ
	CSound *m_pSound;	//サウンド
};
#endif // !_RESOURE_MANAGER_H_
