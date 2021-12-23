//=============================================================================
//
// ポリゴンクラス  [scene_base.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scenebase.h"

CSceneBase::CSceneBase(int nPriority) :CScene(nPriority)
{
	m_pos = VECTOR3_DEFAULT;
	m_size = VECTOR3_DEFAULT;
	m_col = WhiteColor;
	m_rot = ZeroVector3;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}

CSceneBase::~CSceneBase()
{
	// !NULLチェック
	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
