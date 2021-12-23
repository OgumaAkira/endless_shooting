//*****************************************************************************
//
// �eUI���� [bulletUI.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _BULLETUI_H_
#define _BULLETUI_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGame;
class CRenderer;
class CSceneBase;

//*****************************************************************************
//�eUI�N���X�錾
//*****************************************************************************
class CBulletUI :public CScene2D
{
public:
	CBulletUI();								//�R���X�g���N�^
	~CBulletUI();												//�f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);									//�ǂݍ��ݏ���
	static void UnLoad(void);									//�e�N�X�`���̔j��
	static CBulletUI *Create();									//�N���G�C�g�֐�
	HRESULT Init();												//�������֐�
	void Uninit(void);											//�I���֐�
	void Update(void);											//�X�V�֐�
	void Draw(void);											//�`��֐�
	void SetBulletCnt(int bulletcnt) {m_BulletCnt = bulletcnt;}	//�c�e�i�[�֐�
	int GetBulletCnt(void)			 { return m_BulletCnt; }	//�c�e�擾�֐�
	void SetbUse(void)				 { m_bSpeedFlash = true; }	//�_�ŃX�C�b�`���i�[�֐�
	bool GetbUse(void)				 { return m_bSpeedFlash; }	//�_�ŃX�C�b�`���擾�֐�
	void Loading(void);											//���U�֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3						m_size;				// �|���S���傫��
	int								m_nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	static LPDIRECT3DTEXTURE9		m_pTexture;			//�e�N�X�`���̏��[�e�N�X�`���̐�]
	CScene2D						*m_apScene2D[MAX_BULLET];	//�V�[��2D�̃|�C���^�z��
	int								m_BulletCnt;		//�c�e��
	static bool						m_bSpeedFlash;		//�X�C�b�`
};
#endif