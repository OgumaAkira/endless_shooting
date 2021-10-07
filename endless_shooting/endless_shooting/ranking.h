//#ifndef _RANKING_H_
//#define _RANKING_H_
//
////インクルードファイル
//#include "main.h"
//#include "renderer.h"
//#include "scene.h"
//#include "game.h"
//#include "number.h"
//
////マクロ定義
//#define MAX_RANKING (10)	//ランキング最大数
//
////スコアクラス宣言
//class CRanking :public CScene
//{
//public:
//
//	CRanking();				//コンストラクタ
//	~CRanking();				//デストラクタ
//
//							//メンバ関数
//	static CRanking *Create(void);
//	HRESULT Init(void);		//初期化処理
//	void Uninit(void);		//終了処理
//	void Update(void);		//更新処理
//	void Draw(void);		//描画処理
//	void SetScore(int nScore);//スコア値格納処理
//	void AddScore(int nScore);//加算スコア処理
//	int GetScore(void) { return m_nScore; }
//	void ReadFile(void);					//読み込み関数
//	void WriteFile(void);					//書き込み関数
//	int SetRanking(int nTime, char *pName);	//セットランキング
//	void GetRanking(void);
//
//private:
//	//メンバ変数
//	D3DXVECTOR3				m_move;			//移動量
//	D3DXVECTOR3				m_pos;			// ポリゴンの位置
//	D3DXVECTOR3				m_size;			// ポリゴン大きさ
//	int						m_nCounterAnim;//アニメーションカウンター
//	int						m_nPatternAnim;//アニメーションパターンNo.
//	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
//	int						m_nScore;
//	int						m_aScore[MAX_RANKING];
//};
//#endif