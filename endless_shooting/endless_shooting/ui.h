//*****************************************************************************
//
// �n�C�X�R�AUI���� [hiscoreUI.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _UI_H_
#define _UI_H_

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
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CUi :public CScene2D
{
public:

	//�\���̒�`(���)
	typedef enum
	{
		UITYPE_NONE = 0,		//�����Ȃ����
		UITYPE_HISCORE,			//�n�C�X�R�A
		UITYPE_MYSCORE,			//���ȃX�R�A
		UITYPE_TITLELOGO,		//�^�C�g�����S
		UITYPE_TUTORIAL,		//�`���[�g���A��
		UITYPE_SCORE,			//�X�R�A��UI
		UITYPE_MAX				//�ő吔
	}UITYPE;

	CUi(int nPriority = 7);													//�R���X�g���N�^
	~CUi();																	//�f�X�g���N�^

	//�����o�֐�
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType);	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE nType);			//�������֐�
	void Uninit(void);														//�I���֐�
	void Update(void);														//�X�V�֐�
	void Draw(void);														//�`��֐�
	static HRESULT Load(void);												//���[�h�֐�
	static void UnLoad(void);												//�A�����[�h�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;						//�ʒu
	D3DXVECTOR3						m_size;						//�傫��
	D3DXCOLOR						m_col;						//�J���[
	int								m_Cnt;						//�J�E���g
	static LPDIRECT3DTEXTURE9		m_apTexture[UITYPE_MAX];	//�e�N�X�`���̏��
	CSound							*pSound;					//�T�E���h
};
#endif 