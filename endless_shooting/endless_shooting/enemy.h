//*****************************************************************************
//
// �G�̏��� [enemy.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_ENEMY (2)//��ʂɏo���G�̍ő吔

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CEnemy :public CScene2D
{
public:

	//�\���̒�`(���)
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,		//�ʏ�
		ENEMYRSTATE_DEATH,			//����
		ENEMYS_MAX,					//�ő吔
	}ENEMYSTATE;

	//�\���̒�`(���)
	typedef enum
	{
		ENEMYTYPE_NORMAL = 0,		//�G1
		ENEMYTYPE_MAX				//�ő吔
	}ENEMYTYPE;

	CEnemy(int nPriority = 0);				//�R���X�g���N�^
	~CEnemy();								//�f�X�g���N�^

	//�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType);//�N���G�C�g
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType);							//����������
	void Uninit(void);																			//�I������
	void Update(void);																			//�X�V����
	void Draw(void);																			//�`�揈��
	void CEnemy::HitDamege(int nDamege);														//�q�b�g�_���[�W�֐�
	void Range(void);																			//�ړ��͈�
	static HRESULT Load(void);																	//�ǂݍ��ݏ���
	static void UnLoad(void);																	//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;						// �|���S���̌��݈ʒu
	D3DXVECTOR3				m_posold;					// �|���S���̉ߋ��ʒu
	D3DXVECTOR3				m_move;						// �|���S���̈ړ���
	D3DXVECTOR3				m_size;						// �|���S���傫��
	ENEMYSTATE				m_state;					//���
	int						m_nCountState;				//�X�e�[�g�J�E���^�[
	int						m_nHP;						//�q�b�g�|�C���g
	bool					m_bLand;					//�����蔻��
	bool					m_bContact;					//�����蔻��2
	CInput* m_pInput;									//�f�o�b�O����p
	CScore* m_pScore;									//�X�R�A�̃|�C���^
	static LPDIRECT3DTEXTURE9		m_apTexture[MAX_ENEMY];		//�e�N�X�`���̏��
};
#endif 