#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : OgumaAkira
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̎��
	enum TEXTURE_TYPE_NUM
	{
		TEXTURE_TYPE_NUM_NONE = -1,		// �����l
		TEXTURE_TYPE_NUM_NORMAL,		// �ʏ�e�N�X�`��
		TEXTURE_TYPE_NUM_SEPARATE,		// �����e�N�X�`��
		TEXTURE_TYPE_NUM_MAX			// �ő�l
	};

	// �e�N�X�`���̔ԍ��̗񋓌^
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,			// �����l
		TEXTURE_NUM_BULLET,				//�e
		TEXTURE_NUM_MAX
	};

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_NUMBER,			// ����
		SEPARATE_TEX_MAX				// �ő�l
	};

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	};
	CTexture();
	~CTexture();

	static CTexture *Create(void);	//�C���X�^���X����
	HRESULT SetTextureName(void);	//�������֐�
	void LoadAll(void);				//�S�Ẵ��[�h
	void UnLoadAll(void);				//�S�ẴA�����[�h

	//�ʏ�e�N�X�`��
	HRESULT NormalTexLoad(void);	//�e�N�X�`�����[�h
	void NormalTexUnLoad(void);		//�e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE tex_type);	//�e�N�X�`���̏��

	//�����e�N�X�`��
	HRESULT SeparateTexLoad(void);	//�e�N�X�`�����[�h
	void SeparateTexUnLoad(void);	//�e�N�X�`���A�����[�h
	LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE sepatex_type);	//�e�N�X�`���̏��
	D3DXVECTOR2	GetSparateTexInfo(SEPARATE_TEX_TYPE sepatex_type);			//�����e�N�X�`�� UV�̖����擾
	bool GetSparateTexLoop(SEPARATE_TEX_TYPE sepatex_type);					//���[�v���邩

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];	//�e�N�X�`���̔z��|�C���^
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr,SEPARATE_TEX_NUMBER,D3DXVECTOR2(0,0),false,
	};

	vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];					// �e�N�X�`���̖��O
};
#endif // !_TEXTURE_H_
