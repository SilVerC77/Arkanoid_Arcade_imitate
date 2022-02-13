/* GameOver
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021/09/29
 */
#include "COriginalGameApp.h"
#include "GameResource.h"

 //変数定義-----------------------------------------------------------------------
 //ゲームオーバー画面のフェーズを管理する変数
ePhase g_OverPhase = eBegin;
//背景の画像を管理する変数
CPicture* g_pOver;
//ゲームオーバー画面から次へ進むときのフローを管理する変数
eGameStatus g_NextStatusFromOver = eNone;

const XMFLOAT2 GAME_OVER_SIZE = { 297.f,29.f };
const XMFLOAT2 GAME_OVER_POS = { 11.f,-218.f };
int g_iTimerinGameOver = 0;

/* ゲームオーバー画面の処理を行う部分
 */
void COriginalGameApp::procOver() {
	switch (g_OverPhase) {
		//開始時
	case eBegin: {
		//ゲームオーバー画面の開始処理
		procOverBegin();

		//進行状態のメインに切り替える
		g_OverPhase = eMain;
	}break;
		//メイン
	case eMain: {
		//ゲームオーバー画面のメイン処理
		procOverMain();

	}break;
		//終了時
	case eEnd: {
		//ゲームオーバー画面の終了処理を行う
		procOverEnd();
		//再度ゲームオーバー画面に来た時に開始から処理を行うために
		//フェーズを戻しておく
		g_OverPhase = eBegin;
		//次のステータスを設定する
		g_NextStatusFromOver = eOpening;
		SetNextGameStatus(g_NextStatusFromOver);
	}break;
	}
}

/* 関数名　	：procOverBegin()
 * 処理内容　：ゲームオーバー画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procOverBegin() {
	//ゲームオーバー画像を作成する
	if (g_pOver == NULL) g_pOver = createSprite(Tex_GameOver, GAME_OVER_SIZE, GAME_OVER_POS);
	g_iTimerinGameOver = 0;
}

/* 関数名　	：procOverBegin()
 * 処理内容　：ゲームオーバー画面のメイン処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procOverMain() {
	//Xキーを押されたらフェーズを終了に変更し、
	//リザルトにステータスを移行する準備をする
	g_iTimerinGameOver++;
	//if (m_pDirectInput->isPressedOnce(DIK_SPACE)) {
	if (g_iTimerinGameOver > 5 * 60) g_OverPhase = eEnd;

	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//描画
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	procHeader();
	if (g_pOver != NULL)	renderSprite(g_pOver);
}

/* 関数名　	：procOverBegin()
 * 処理内容　：ゲームオーバー画面の終了時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procOverEnd() {
	if (g_pOver != NULL) {
		disposeSprite(g_pOver);
		g_pOver = NULL;
	}
}