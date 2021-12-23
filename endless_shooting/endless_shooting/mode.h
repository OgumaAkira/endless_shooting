//*****************************************************************************
//
// ���[�h�J�ڏ��� [mode.cpp]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _MODE_H_
#define _MODE_H_

//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CModeBase;
class CScene;
class CPlayer;

//*****************************************************************************
//�N���X�錾
//*****************************************************************************
class CMode : public CManager
{
public:
	CMode();	//�R���X�g���N�^
	~CMode();	//�f�X�g���N�^

	static CMode *Create();	//����
	HRESULT Init(void);	//������
	void Update(void);	//�X�V
	void Uninit(void);	//�I��

	void ChangeState(CModeBase *pModeBase);	//��ԑJ��
private:
	//�����o�ϐ�
	//�|�C���^
	CModeBase *m_pModeBase;	//���[�h���
	CPlayer	*m_pPlayer;	//�v���C���[
};
#endif // !_MODE_H_