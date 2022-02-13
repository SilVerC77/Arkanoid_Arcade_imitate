/* GameResult
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021/09/29
 */
#include "COriginalGameApp.h"
#include "GameResource.h"

 //ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
 //番号管理
int g_iNameIndex = 0;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//サイズ
const XMFLOAT2 RESULT_SIZE = { 945.f, 1080.f };
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//座標
const XMFLOAT2 ALLSCORE_POS = { -50.f,-150.f };	//
const XMFLOAT2 NOWSCORE_POS = { -145.f,50.f };
const XMFLOAT2 NOWROUND_POS = { 45.f,50.f };
const XMFLOAT2 NOWNAME_POS = { 160.f,50.f };
const float SPACE_NAME = 275.f;
const float GAP = 37.f;							//行距離
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//アニメーション
const int INPUT_COUNTER = 10;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//画像管理
CFont* g_pAllScore[5];							//
CFont* g_pAllName[5];
CFont* g_pName = NULL;
CFont* g_pResult_Score = NULL;
CFont* g_pResult_Round = NULL;
CPicture* g_pInput = NULL;
CPicture* g_pResultBackground;					//背景の画像を管理する変数
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//ステータス管理
char g_cName[4];
ePhase g_ResultPhase = eBegin;					//リザルト画面のフェーズを管理する変数
eGameStatus g_NextStatusFromResult = eNone;		//リザルト画面から次へ進むときのフローを管理する変数
int g_iTimerinResult = 0;
bool g_bEntered = false;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
////関数
char convertToChar(BYTE _key) {
	switch (_key) {
	case DIK_A:return 'A'; break;
	case DIK_B:return 'B'; break;
	case DIK_C:return 'C'; break;
	case DIK_D:return 'D'; break;
	case DIK_E:return 'E'; break;
	case DIK_F:return 'F'; break;
	case DIK_G:return 'G'; break;
	case DIK_H:return 'H'; break;
	case DIK_I:return 'I'; break;
	case DIK_J:return 'J'; break;
	case DIK_K:return 'K'; break;
	case DIK_L:return 'L'; break;
	case DIK_M:return 'M'; break;
	case DIK_N:return 'N'; break;
	case DIK_O:return 'O'; break;
	case DIK_P:return 'P'; break;
	case DIK_Q:return 'Q'; break;
	case DIK_R:return 'R'; break;
	case DIK_S:return 'S'; break;
	case DIK_T:return 'T'; break;
	case DIK_U:return 'U'; break;
	case DIK_V:return 'V'; break;
	case DIK_W:return 'W'; break;
	case DIK_X:return 'X'; break;
	case DIK_Y:return 'Y'; break;
	case DIK_Z:return 'Z'; break;
	default:return ' ';
	}
}
BYTE key[26] = {
	DIK_A,
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z
};

//___________________________________________________________________________________________________
//リザルト画面の処理を行う部分
 //__________________________________________________________________________________________________
void COriginalGameApp::procResult() {
	switch (g_ResultPhase) {
		//開始時
	case eBegin: {
		//リザルト画面の開始処理
		procResultBegin();

		//進行状態のメインに切り替える
		if (g_bNewRecord) g_ResultPhase = eMain;
		else	          g_ResultPhase = eEnd;

	}break;
		//メイン
	case eMain: {
		//リザルト画面のメイン処理
		procResultMain();

	}break;
		//終了時
	case eEnd: {
		//リザルト画面の終了処理を行う
		procResultEnd();
		//再度リザルト画面に来た時に開始から処理を行うために
		//フェーズを戻しておく
		g_ResultPhase = eBegin;
		//次のステータスを設定する
		g_NextStatusFromResult = eGameOver;
		SetNextGameStatus(g_NextStatusFromResult);
	}break;
	}
}

/* 関数名　	：procResultBegin()
 * 処理内容　：リザルト画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procResultBegin() {
	//背景を作成する
	if (g_pResultBackground == NULL)g_pResultBackground = createSprite(Tex_Result, RESULT_SIZE);

	//初期化
	g_iTimerinResult = 0;
	g_bEntered = false;
}

/* 関数名　	：procResultBegin()
 * 処理内容　：リザルト画面のメイン処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procResultMain() {
	//Xキーを押されたらフェーズを終了に変更し、
	//タイトルにステータスを移行する準備をする
	if (g_bEntered) ++g_iTimerinResult;
	if (g_iTimerinResult > 5 * 60)g_ResultPhase = eEnd;

	ShowScore(g_pScore, g_iScore, g_iDigit, SCORE_POS, FONT_SIZE);
	ShowScore(g_pHiScore, g_iHiScore, g_iHiDigit, HISCORE_POS, FONT_SIZE);
	for (int i = 0; i < 5; ++i) {
		XMFLOAT2 pos = ALLSCORE_POS;
		pos.y -= float(i) * (FONT_SIZE.y + GAP);
		ShowScore(g_pAllScore[i], g_sRecord[i].score, g_sRecord[i].digit, pos, FONT_SIZE);
		if (!g_pAllName[i]) g_pAllName[i] = createFont(Tex_Alphabet, 3, FONT_SIZE.x, FONT_SIZE.y);
		g_pAllName[i]->setPos(pos.x + SPACE_NAME, pos.y);
	}
	int digit_round, digit_score;
	ShowScore(g_pResult_Round, g_sRecordNow.round, digit_round, NOWROUND_POS, FONT_SIZE);
	ShowScore(g_pResult_Score, g_sRecordNow.score, digit_score, NOWSCORE_POS, FONT_SIZE);
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//名前を入力する処理ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	bool wordchange = false;
	for (int i = 0; i < 26; ++i) {
		if (m_pDirectInput->isPressedOnce(key[i])) {
			if (g_iNameIndex > 2)break;
			g_cName[g_iNameIndex] = convertToChar(key[i]);
			g_iNameIndex++;
			g_cName[g_iNameIndex] = '\0';
			wordchange = true;
			break;
		}
	}
	if (m_pDirectInput->isPressedOnce(DIK_BACK)) {
		if (g_iNameIndex <= 0)	g_iNameIndex = 0;
		else {
			g_cName[g_iNameIndex] = '\0';
			g_iNameIndex--;
			wordchange = true;
		}
	}
	if (m_pDirectInput->isPressedOnce(DIK_SPACE)) {
		if (g_iNameIndex > 2) {
			for (int i = 0; i < 5; ++i) {
				if (g_iScore == g_sRecord[i].score) {
					g_sRecord[i].name = g_cName;
					g_bEntered = true;
					break;
				}
			}
		}
	}
	if (wordchange) {
		disposeFont(g_pName);
		g_pName = NULL;
	}
	if (!g_pName) {
		g_pName = createFont(Tex_Alphabet, g_iNameIndex, FONT_SIZE.x, FONT_SIZE.y);
		g_pName->setPos(NOWNAME_POS.x, NOWNAME_POS.y);
	}

	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//描画
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	procHeader();
	if (g_pName) renderFont(g_pName, g_cName);
	//名前入ってるのを描画
	for (int i = 0; i < 5; ++i) {
		if (g_sRecord[i].name == "")continue;
		if (g_pAllName[i])renderFont(g_pAllName[i], g_sRecord[i].name);
	}
	if (g_pResult_Round)renderFont(g_pResult_Round, g_sRecordNow.round);
	if (g_pResult_Score)renderFont(g_pResult_Score, g_sRecordNow.score);
	if (g_pResultBackground != NULL)renderSprite(g_pResultBackground);
}


/* 関数名　	：procResultBegin()
 * 処理内容　：リザルト画面の終了時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procResultEnd() {
	if (g_pResultBackground != NULL) {
		disposeSprite(g_pResultBackground);
		g_pResultBackground = NULL;
	}
	if (g_pScore) {
		disposeFont(g_pScore);
		g_pScore = NULL;
	}
	if (g_pHiScore) {
		disposeFont(g_pHiScore);
		g_pHiScore = NULL;
	}
	if (g_pName) {
		disposeFont(g_pName);
		g_pName = NULL;
	}

	//リセットーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	g_iScore = 0;									//スコアをリセット
	for (int i = 0; i < 3; ++i) g_cName[i] = '\0';	//名前をリセット
	g_iNameIndex = 0;
}


