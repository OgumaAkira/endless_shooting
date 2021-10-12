//*****************************************************************************
//
// �X�s�[�h�̏��� [speed.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SPEED_H_
#define _SPEED_H_

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
class CSpeed :public CScene2D
{
public:

	CSpeed(int nPriority=7);									//�R���X�g���N�^
	~CSpeed();													//�f�X�g���N�^

	//�����o�֐�
	static CSpeed *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//�������֐�
	void Uninit(void);											//�I���֐�
	void Update(void);											//�X�V�֐�
	void Draw(void);											//�`��֐�
	static HRESULT Load(void);									//���[�h�֐�
	static void UnLoad(void);									//�A�����[�h�֐�
	static void SetbUse(bool bUse) { m_bUse = bUse; }			//�X�C�b�`���i�[�֐�
	static bool GetbUse(void) { return m_bUse; }				//�X�C�b�`�擾�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3						m_move;					// �|���S���̈ړ���
	D3DXVECTOR3						m_size;					// �|���S���傫��
	D3DXCOLOR						m_col;					//�J���[
	static int						m_nFrameCnt;			//�t���b�V���J�E���g
	int								m_Cnt;					//�J�E���g
	bool							m_bUse2;				//�X�C�b�`2
	static bool						m_bUse;					//�X�C�b�`
	static LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���̏��
	CSound							*pSound;				//�T�E���h
};
#endif 