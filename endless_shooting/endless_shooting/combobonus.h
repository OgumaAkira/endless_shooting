//*****************************************************************************
//
// �R���{�X�R�A���� [comboscore.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _COMBOBONUS_H_
#define _COMBOBONUS_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
class CCombo;

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_COMBOBONUS_NUMBER (5)						//�X�R�A�i���o�[�̍ő吔

//*****************************************************************************
//�X�R�A�̃N���X�錾
//*****************************************************************************
class CComboBonus :public CScene
{
public:
	CComboBonus(int nPriority = 7);						//�R���X�g���N�^
	~CComboBonus();										//�f�X�g���N�^

	//�����o�֐�
	static CComboBonus *Create(void);					//�N���G�C�g�֐�
	HRESULT Init(void);									//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	void SetScore(int nScore) { m_nScore = nScore; }	//�X�R�A�l�i�[�֐�
	int GetScore(void) { return m_nScore; }				//�X�R�A�擾�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;								//�ړ���
	D3DXVECTOR3				m_pos;								// �|���S���̈ʒu
	D3DXVECTOR3				m_size;								// �|���S���傫��
	CNumber					*m_apNumber[MAX_COMBOBONUS_NUMBER];	//�V�[��2D�̃|�C���^�z��
	static int				m_nScore;							//�X�R�A
	float					m_nColor;							//�F
};
#endif