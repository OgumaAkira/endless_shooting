//*****************************************************************************
//
// �R���{�̏��� [combo.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"
#include "number.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCombo;
class CComboBonus;
class CScore;

//*****************************************************************************
//�N���X�錾
//*****************************************************************************
class CCombo :public CScene2D
{
public:

	CCombo();											//�R���X�g���N�^
	~CCombo();															//�f�X�g���N�^

	//�����o�֐�
	static CCombo *Create(void);										//�N���G�C�g�֐�
	HRESULT Init(void);													//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��
	void ComboAction(void);												//�R���{�֐�
	bool GetbCombo(void) { return m_bCombo; }							//�R���{������擾�֐�
	void SetbCombo(bool bCombo) { m_bCombo = bCombo; }					//�R���{������i�[�֐�
	int GetSocreCombo(void) { return m_nComboScore; }					//�R���{������擾�֐�
	void SetSocreCombo(int nComboScore) { m_nComboScore = nComboScore; }//�R���{������i�[�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;								//�ړ���
	D3DXVECTOR3				m_pos;								//�|���S���̈ʒu
	D3DXVECTOR3				m_size;								//�|���S���傫��
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
	CScore					*m_pScore;							//�X�R�A�̃|�C���^
	bool					m_bCombo;							//�R���{�̕\���ؑ�
	float					m_nColor;							//�F���l
	int						m_nCombo;							//�R���{��
	int						m_nComboScore;						//�R���{�̃X�R�A�l
};
#endif
