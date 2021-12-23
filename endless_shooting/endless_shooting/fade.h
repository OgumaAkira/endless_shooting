//*****************************************************************************
//
// �t�F�[�h�̏��� [fade.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//*****************************************************************************
//�t�F�[�h�̃N���X�錾
//*****************************************************************************
class CFade:public CScene2D
{
public:
	//�\���̒�`(���)
	typedef enum
	{
		FADESTATE_NONE = 0,		//�����Ȃ����
		FADESTATE_IN,			//�t�F�[�h�C��
		FADESTATE_OUT,			//�t�F�[�h�A�E�g
		FADESTATE_MAX			//�ő吔
	}FADESTATE;

	CFade(int nPriority = 10);				//�R���X�g���N�^
	~CFade();								//�f�X�g���N�^

	//�����o�֐�
	static CFade *Create();									//�N���G�C�g�֐�
	static HRESULT Load(void);								//���[�h�֐�
	static void UnLoad(void);								//�A�����[�h�֐�
	HRESULT Init();											//����������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	void Draw(void);										//�`�揈��
	void SetFade(FADESTATE fade) { m_FadeState = fade; }	//�t�F�[�h�̏�Ԋi�[�֐�
	static FADESTATE GetFade(void) { return m_FadeState; }	//�t�F�[�h�̏�Ԏ擾�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_move;							//�ړ���
	D3DXVECTOR3						m_pos;							//�|���S���̈ʒu
	D3DXVECTOR3						m_size;							//�|���S���傫��
	static int						m_color;						//�|���S���̐F
	bool							m_bSpeedFlash;							//ONOFF
	static FADESTATE				m_FadeState;			//�g�p���Ă��邩�ǂ���
	static LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���̏��[�e�N�X�`���̐�]
	CScene2D						*m_pScene2D;			//�V�[��2D�̃|�C���^�z��
};
#endif