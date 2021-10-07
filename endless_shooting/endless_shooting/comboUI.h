//*****************************************************************************
//
// �X�s�[�h�̏��� [speed.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _COMBOUI_H_
#define _COMBOUI_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
class CSound;

//*****************************************************************************
//�X�s�[�h�̃N���X�錾
//*****************************************************************************
class CComboUI :public CScene2D
{
public:

	CComboUI(int nPriority = 7);									//�R���X�g���N�^
	~CComboUI();													//�f�X�g���N�^

																//�����o�֐�
	static CComboUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//�������֐�
	void Uninit(void);											//�I���֐�
	void Update(void);											//�X�V�֐�
	void Draw(void);											//�`��֐�
	static HRESULT Load(void);									//���[�h�֐�
	static void UnLoad(void);									//�A�����[�h�֐�
	
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���̏��
	D3DXVECTOR3						m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3						m_move;					// �|���S���̈ړ���
	D3DXVECTOR3						m_size;					// �|���S���傫��
	CSound							*pSound;				//�T�E���h
	float							m_nColor;				//�F���l
	int								m_nComboCountFrame;		//�R���{�\���̃t���[����

};
#endif 