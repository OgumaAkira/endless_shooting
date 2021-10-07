//*****************************************************************************
//
// �n�C�X�R�A���� [hiscore.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _HISCORE_H_
#define _HISCORE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//*****************************************************************************
//�X�R�A�N���X�錾
//*****************************************************************************
class CHIScore :public CScene
{
	//�\���̒�`(���)
	typedef enum
	{
		HISCORETYPE_NONE = 0,		//�����Ȃ����
		HISCORETYPE_HISCORE,		//�n�C�X�R�A
		HISCORETYPE_MYSCORE,		//���ȃX�R�A
		HISCORETYPE_MAX				//�ő吔
	}HISCORETYPE;

public:
	CHIScore();					//�R���X�g���N�^
	~CHIScore();				//�f�X�g���N�^

	//�����o�֐�
	static CHIScore *Create(void);			//�N���G�C�g�֐�
	HRESULT Init(void);						//�������֐�
	void Uninit(void);						//�I���֐�
	void Update(void);						//�X�V�֐�
	void Draw(void);						//�`��֐�
	static void WriteFile(int nScore);		//�������݊֐�
	static int ReadFile(void);				//�ǂݍ��݊֐�

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;								//�|���S���̈ʒu
	D3DXVECTOR3				m_size;								//�|���S���傫��
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
	static int				m_nScore;							//�X�R�A
};
#endif