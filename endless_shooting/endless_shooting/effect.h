#pragma once
//*****************************************************************************
//
// �������� [effect.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"

//*****************************************************************************
//�����̃N���X�錾
//*****************************************************************************
class CEffect :public CScene2D
{
public:
	//�\���̒�`(�^�C�v)
	typedef enum
	{
		EFFECT_TYPE_EXPLOSION = 0,	//�����Ȃ�
		EFFECT_TYPE_CURSOR,		//�J�[�\��
		EFFECT_TYPE_PLAYER,		//�v���C���[
		EFFECT_TYPE_ENEMY,		//�G
		EFFECT_TYPE_MAX			//�ő吔
	} EFFECT_TYPE;


	CEffect();				//�R���X�g���N�^
	~CEffect();				//�f�X�g���N�^

								//�����o�֐�
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR3 move, int type);	//�N���G�C�g�֐�
	void Smoke(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	void ClickEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);												//�������֐�
	void Uninit(void);												//�I���֐�
	void Update(void);												//�X�V�֐�
	void Draw(void);												//�`��֐�
	static HRESULT Load(void);										//���[�h�֐�
	static void UnLoad(void);										//�A�����[�h�֐�

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;	//�e�N�X�`���̏��
	D3DXVECTOR3					m_move;		//�ړ���
}; 
#endif