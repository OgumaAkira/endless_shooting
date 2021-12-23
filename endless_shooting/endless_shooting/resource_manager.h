#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//*****************************************************************************
//
// ���\�[�X�}�l�[�W���[����  [resource_manager.h]
// Author : Oguma Akira
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CTexture;
class CSound;

//*****************************************************************************
//���\�[�X�}�l�[�W���[�N���X
//*****************************************************************************
class CResourceManager
{
public:
	~CResourceManager();

	HRESULT Init(void);//�������֐�
	void LoadAll(void);//�S���[�h�֐�
	void UnLoadAll(void);//�S�A�����[�h�֐�

	static CResourceManager *GetInstace(void);//�C���X�^���X�擾

	//Get�֐�
	CTexture *GetTextureClass(void) { return m_pTexture; }
	CSound *GetSoundClass(void) { return m_pSound; }

private:
	CResourceManager();		//�R���X�g���N�^

	//�|�C���^��
	static CResourceManager *m_pResourceManager;	//���\�[�X�}�l�[�W���[
	CTexture *m_pTexture;	//�e�N�X�`��
	CSound *m_pSound;	//�T�E���h
};
#endif // !_RESOURE_MANAGER_H_
