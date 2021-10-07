//*****************************************************************************
//
// �������� [explosion.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _EXLPOSION_H_
#define _EXLPOSION_H_

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
class CExplosion :public CScene2D
{
public:
	CExplosion();				//�R���X�g���N�^
	~CExplosion();				//�f�X�g���N�^

	//�����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				//�������֐�
	void Uninit(void);												//�I���֐�
	void Update(void);												//�X�V�֐�
	void Draw(void);												//�`��֐�
	static HRESULT Load(void);										//���[�h�֐�
	static void UnLoad(void);										//�A�����[�h�֐�


private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
};
#endif 