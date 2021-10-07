//*****************************************************************************
//
// �i���o�[�̏��� [number.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScene;

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CNumber
{
public:
	CNumber();				//�R���X�g���N�^
	~CNumber();				//�f�X�g���N�^

	//�����o�֐�
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);//�N���G�C�g�֐�
	static HRESULT Load(void);											//���[�h�֐�
	static void UnLoad(void);											//�A�����[�h�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);			//�������֐�
	void Uninit(void);													//�I���֐�
	void Update(void);													//�X�V�֐�
	void Draw(void);													//�`��֐�
	void SetNumber(int nNumber);										//�i���o�[���i�[�֐�
	void SetColor(D3DXCOLOR col)		{ m_color = col; }				//�F�i�[�֐�
	void SetPosition(D3DXVECTOR3 pos)	{ m_pos = pos; }				//�ʒu���i�[�֐�
	void SetSize(D3DXVECTOR3 size)		{ m_size = size; }				//�傫�����擾�֐�
	D3DXVECTOR3 GetPosition(void)		{ return D3DXVECTOR3(m_pos); }	//�ʒu�擾�֐�
	D3DXVECTOR3 GetSize(void)			{ return D3DXVECTOR3(m_size); }	//�傫���擾�֐�
	D3DXCOLOR	GetColor()				{ return D3DXCOLOR(m_color);}	//�F�擾�֐�

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���̏��
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//���_�o�b�t�@�̏��
	D3DXVECTOR3					m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3					m_size;			// �|���S���̑傫��
	D3DXVECTOR2					m_tex;			//�e�X�N�`��
	D3DXCOLOR					m_color;		//�J���[
	CScene						*m_pScene;		//�V�[���̃|�C���^
};
#endif