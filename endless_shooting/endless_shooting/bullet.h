//*****************************************************************************
//
// �e�̏��� [bullet.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPlayer;
class CEnemy;
class CInput;
class CButton;
class CBulletUI;
class CCombo;

//*****************************************************************************
//�e�N���X�錾
//*****************************************************************************
class CBullet :public CScene2D
{
public:
	//�\���̒�`(�^�C�v)
	typedef enum
	{
		BULLET_TYPE_NONE = 0,	//�����Ȃ�
		BULLET_TYPE_CURSOR,		//�J�[�\��
		BULLET_TYPE_PLAYER,		//�v���C���[
		BULLET_TYPE_ENEMY,		//�G
		BULLET_TYPE_MAX			//�ő吔
	} BULLET_TYPE;
	
	CBullet();					//�R���X�g���N�^
	~CBullet();					//�f�X�g���N�^

	//�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);	//�N���G�C�g�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);			//�������֐�
	void Uninit(void);																				//�I���֐�
	void Update(void);																				//�X�V�֐�
	void Draw(void);																				//�`��֐�
	static HRESULT Load(void);																		//���[�h�֐�
	static void UnLoad(void);																		//�A�����[�h�֐�
private:
	//�����o�ϐ�
	D3DXVECTOR3						m_move;			//�ړ���
	D3DXVECTOR3						m_pos;			//�|���S���̈ʒu
	D3DXVECTOR3						m_size;			//�|���S���̃T�C�Y
	int								m_nHP;			//�q�b�g�|�C���g
	BULLET_TYPE						m_type;			//���
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	static CBulletUI				*m_pBulletUI;	//�eUI�̃|�C���g
};
#endif 