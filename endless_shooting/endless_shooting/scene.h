//*****************************************************************************
//
// �V�[���̏��� [scene.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//�I�u�W�F�N�g�N���X�錾
//*****************************************************************************
class CScene
{
public:
	//�\���̒�`(���)
	typedef enum
	{
		OBJTYPE_NONE = 0,	//�����Ȃ�
		OBJTYPE_CURSOR,		//�J�[�\��
		OBJTYPE_PLAYER ,	//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_BULLET,		//�e
		OBJTYPE_EXPLOSION,	//����
		OBJTYPE_EFFECT,		//�G�t�F�N�g
		OBJTYPE_BG,			//�w�i
		OBJTYPE_BUTTON,		//�{�^��
		OBJTYPE_TITLE,		//�^�C�g�����
		OBJTYPE_GAME,		//�Q�[�����
		OBJTYPE_RESULT,		//���U���g���
		OBJTYPE_PAUSE,		//�|�[�Y���
		OBJTYPE_COMBOUI,	//�R���{UI
		OBJTYPE_MAX			//�ő吔
	}OBJTYPE;

	CScene(int nPriority = 0);			//�R���X�g���N�^
	virtual~CScene();					//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;		//����������
	virtual void Uninit(void) = 0;		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��


	void SetObjType(OBJTYPE objType) { m_ObjType = objType; };									//�I�u�W�F�N�g���i�[�֐�
	OBJTYPE GetObjType(void) { return m_ObjType; };												//�I�u�W�F�N�g���擾�֐�
	static CScene *GetScene(int Priority, int scene) { return m_apScene[Priority][scene]; }		//�V�[�����擾�֐�
	static void UpdateAll(void);																//�X�V�֐�
	static void DrawAll(void);																	//�`��֐�
	static void ReleaseAll(void);																//�I���֐�
	static void	Select(int Priority);

protected:
	void Release(void);																			//�I���֐�

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_TEXTURE];	//�V�[���̔z��|�C���^
	static int m_nNumAll;									//�I�u�W�F�N�g�̑���
	int m_nID;												//�e�N�X�`���̔ԍ�
	OBJTYPE m_ObjType;										//�I�u�W�F�N�g�̎��
	int m_Priority;											//�D�揇��
};
#endif // !_RENDERER_H_