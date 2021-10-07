//*****************************************************************************
//
// �^�C�g�����S���� [titlelogo.h]
// Author : ���F �N
//
//*****************************************************************************
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"

//�I�u�W�F�N�g2�N���X�錾
class CTitleLogo :public CScene2D
{
public:

	CTitleLogo(int nPriority = 7);				//�R���X�g���N�^
	~CTitleLogo();				//�f�X�g���N�^

							//�����o�֐�
	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;			// �|���S���̈ړ���
	D3DXVECTOR3				m_size;			// �|���S���傫��
	D3DXCOLOR				m_col;			//�J���[
	static int				m_nFrameCnt;	//�t���b�V���J�E���g
	int						m_Cnt;			//�J�E���g
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
};
#endif 