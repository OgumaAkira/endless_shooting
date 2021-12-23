//=============================================================================
//
// �|���S���N���X  [scene_base.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
	// !NULL�`�F�b�N
	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
