//*****************************************************************************
//
// �V�[������ [scene.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_TEXTURE] = {};		//�V�[���̃|�C���g�z��[�D�揇��][�e�N�X�`���̑���]
int CScene::m_nNumAll = 0;										//�I�u�W�F�N�g�̑���

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene::CScene(int nPriority)
{
#if 1
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nID = nCntScene;
			m_Priority = nPriority;
			m_nNumAll++;
			break;
		}
	}
#endif
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene::~CScene()
{

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Update();
			}
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Draw();
			}
		}
	}
}

//*****************************************************************************
// �����[�X�S�̏���
//*****************************************************************************
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Release();
			}
		}
	}
}

void CScene::Select(int Priority)
{
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		if (m_apScene[Priority][nCntScene] != NULL)
		{
			m_apScene[Priority][nCntScene]->Release();
		}
	}
}

//*****************************************************************************
// �����[�X����
//*****************************************************************************
void CScene::Release(void)
{
	if (m_apScene[m_Priority][m_nID]!=NULL)
	{
		int nID = m_nID;
		int nPriority = m_Priority;
		delete m_apScene[nPriority][m_nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

