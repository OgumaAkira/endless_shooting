//#ifndef _RANKING_H_
//#define _RANKING_H_
//
////�C���N���[�h�t�@�C��
//#include "main.h"
//#include "renderer.h"
//#include "scene.h"
//#include "game.h"
//#include "number.h"
//
////�}�N����`
//#define MAX_RANKING (10)	//�����L���O�ő吔
//
////�X�R�A�N���X�錾
//class CRanking :public CScene
//{
//public:
//
//	CRanking();				//�R���X�g���N�^
//	~CRanking();				//�f�X�g���N�^
//
//							//�����o�֐�
//	static CRanking *Create(void);
//	HRESULT Init(void);		//����������
//	void Uninit(void);		//�I������
//	void Update(void);		//�X�V����
//	void Draw(void);		//�`�揈��
//	void SetScore(int nScore);//�X�R�A�l�i�[����
//	void AddScore(int nScore);//���Z�X�R�A����
//	int GetScore(void) { return m_nScore; }
//	void ReadFile(void);					//�ǂݍ��݊֐�
//	void WriteFile(void);					//�������݊֐�
//	int SetRanking(int nTime, char *pName);	//�Z�b�g�����L���O
//	void GetRanking(void);
//
//private:
//	//�����o�ϐ�
//	D3DXVECTOR3				m_move;			//�ړ���
//	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
//	D3DXVECTOR3				m_size;			// �|���S���傫��
//	int						m_nCounterAnim;//�A�j���[�V�����J�E���^�[
//	int						m_nPatternAnim;//�A�j���[�V�����p�^�[��No.
//	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
//	int						m_nScore;
//	int						m_aScore[MAX_RANKING];
//};
//#endif