//*****************************************************************************
//
// �v���C���[�̏��� [player.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define RANGE_MAX (90)
#define MARKERCOLOR_RED		(D3DCOLOR_RGBA(255, 0, 0, 255))
#define MARKERCOLOR_YELLOW	(D3DCOLOR_RGBA(255, 255, 255, 255))
#define PLAYER_TEXTURE ("data/TEXTURE/TargetMarker.png")		//�v���C���[��TEXTURE
#define PLAYER_SIZEX (150.0f)									//�v���C���[��X�̒���
#define PLAYER_SIZEY (150.0f)									//�v���C���[��Y�̒���

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"
#include "enemy.h"

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CPlayer:public CScene2D
{
public:
	CPlayer(int nPriority = 11);				//�R���X�g���N�^
	~CPlayer();									//�f�X�g���N�^

	//�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size );	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//�������֐�
	void Uninit(void);															//�I���֐�
	void Update(void);															//�X�V�֐�
	void Draw(void);															//�`��֐�
	void MarkerColor(void);														//�}�[�J�[�J��-�֐�
	void Range(void);															//�ړ��͈͊֐�
	void MarkerObject(void);													//�I�u�W�F�N�g�w��֐�
	void PlayerInput(void);														//���@���͊֐�
	static HRESULT Load(void);													//���[�h�֐�
	static void UnLoad(void);													//�A�����[�h�֐�
	
private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3						m_size;			// �|���S���傫��
	int								m_nColor;		//�F
	int								m_nHP;			//���C�t
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	CFade							*m_pFade;		//�t�F�[�h�̃|�C���^
	CInput							*m_pInput;		//���͂̃|�C���^
};
#endif 