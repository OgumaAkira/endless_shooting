//*****************************************************************************
//
// �V�[��2D���� [scene.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scenebase.h"

//*****************************************************************************
//�V�[��2D�̃N���X�錾
//*****************************************************************************
class CScene2D :public CSceneBase
{
public:
	CScene2D(int nPriority = 0);												//�R���X�g���N�^
	~CScene2D();																//�f�X�g���N�^

	//�����o�֐�
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);				//�N���G�C�g�֐�
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fFadeNum);	//�t�F�[�h�N���G�C�g�֐�

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								//����������
	void Uninit(void);																//�I������
	void Update(void);																//�X�V����
	void Draw(void);																//�`�揈��

	void CreateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);							//���_�̐���
	void SetVertex(void);															//���_�̐ݒ�
	void InitAnimation(int PatternAnim, int CounterAnim, int nLoop);				//�A�j���[�V�����������֐�
	void UpdateAnimation(void);														//�A�j���[�V�����X�V�֐�
	void InitScroll(int nSpeed, float fDivision);									//��ʃX�N���[���̏�����
	void UpdateScroll(void);														//��ʃX�N���[���̍X�V
	void ScaleUp(float fScaleUp);
	void FlashPolygon(int nFlashFlame);												//�|���S���̓_��
	void FadeOut(float fSpeed);														//�t�F�[�h�A�E�g
	void NumberAnimation(int nNumber);												//�����̐ݒ�


	// �i�[�֐�
	void SetCol(D3DXCOLOR col);											// �F�̐ݒ�
	void SetRotation(float rotasion);									// ��]�̐ݒ�
	void SetScale(const float &fScale);									// �g��̒l�ݒ�
	void SetbNumber(bool bNumber) { m_bNumber = bNumber; }				// �g�p����

	//�擾�֐�
	float GetScale(void) { return m_fScaleNum; }						// �g��̒l���
	bool GetNumber(void) { return m_bNumber; }							//�i���o�[�t���O

private:
	int						m_nPatternAnim;			//�A�j���[�V�����p�^�[����
	int						m_nCounterAnim;			//�A�j���[�V�����J�E���^�[
	int						m_nCountAnim;			//�A�j���[�V�����e�N�X�`��
	int						m_nCountAnimPattern;	//�A�j���[�V�����̃p�^�[��
	int						m_nLoop;				//���[�v���邩�ǂ���
	int						m_nSpeedTexture;		//�e�N�X�`���̈ړ����x
	int						m_nFlashFlame;			//�_�ŗp�̃J�E���^�[
	float					m_fDivisionCounter;		// �X�N���[���̃J�E���^�[
	float					m_fDivisionBaseNum;		//�X�N���[���̃J�E���^�[
	float					m_fRotasion;			//��]�p�ϐ�
	float					m_fScaleNum;			//�g��p�ϐ�
	float					m_fSubFlashNum;			//�|���S���̓_���p
	float					m_fSubNum;				//�|���S���̃T�u�_���p
	float					m_fFadeSpeedNum;		//�t�F�[�h�̃X�s�[�h
	bool					m_bDisappearFlag;		//�_�ŗp�̃t���O
	bool					m_bFadeOut;				//�t�F�[�h�̃t���O
	bool					m_bNumber;				//�g�������̃t���O
};
#endif 