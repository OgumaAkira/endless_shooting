//*****************************************************************************
//
// �X�R�A�̏��� [score.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"
#include "hiscore.h"

//*****************************************************************************
//�X�R�A�̃N���X�錾
//*****************************************************************************
class CScore :public CScene
{
public:
	CScore(int nPriority = 7);						//�R���X�g���N�^
	~CScore();										//�f�X�g���N�^

	//�����o�֐�
	static CScore *Create(void);						//�N���G�C�g�֐�
	HRESULT Init(void);									//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	void AddScore(int nScore);							//���Z�X�R�A�֐�	
	int ReadFile(void);									//�ǂݍ��݃t�@�C���֐�
	void WriteFile(void);								//�������݃t�@�C���֐�
	void SetScore(int nScore)	{ m_nScore = nScore; }	//�X�R�A�l�i�[�֐�
	static int GetScore(void)			{ return m_nScore; }	//�X�R�A�擾�֐�
private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;								//�ړ���
	D3DXVECTOR3				m_pos;								// �|���S���̈ʒu
	D3DXVECTOR3				m_size;								// �|���S���傫��
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
	static int				m_nScore;							//�X�R�A
};
#endif