/* GameClear
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021/09/29
 */
#include "COriginalGameApp.h"
#include "GameResource.h"

//変数定義-----------------------------------------------------------------------
//ゲームクリア画面のフェーズを管理する変数
ePhase g_ClearPhase = eBegin;
//背景の画像を管理する変数
CPicture* g_pClearBackground;
//クリアから次へ進むときのフローを管理する変数
eGameStatus g_NextStatusFromClear = eNone;

/* ゲームクリア画面の処理を行う部分
 */
void COriginalGameApp::procClear() {
	switch (g_ClearPhase) {
		//開始時
	case eBegin: {
		//クリア画面の開始処理
		procClearBegin();

		//進行状態のメインに切り替える
		g_ClearPhase = eMain;
	}break;
		//メイン
	case eMain: {
		//クリア画面のメイン処理
		procClearMain();

	}break;
		//終了時
	case eEnd: {
		//クリア画面の終了処理を行う
		procClearEnd();
		//再度クリアに来た時に開始から処理を行うために
		//フェーズを戻しておく
		g_ClearPhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_NextStatusFromClear);
	}break;
	}
}

/* 関数名　	：procClearBegin()
 * 処理内容　：クリア画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procClearBegin() {
	//ゲームオーバー画像を作成する
	if (g_pClearBackground == NULL) {
		g_pClearBackground = createSprite(Tex_Blue, WINDOW_WIDTH, WINDOW_HEIGHT);
		g_pClearBackground->setPos(0.0f, 0.0f);
	}
}

/* 関数名　	：procClearBegin()
 * 処理内容　：クリア画面のメイン処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procClearMain() {
	//Xキーを押されたらフェーズを終了に変更し、
	//リザルトにステータスを移行する準備をする
	if (m_pDirectInput->isPressedOnce(DIK_SPACE)) {
		g_ClearPhase = eEnd;
		g_NextStatusFromClear = eEnding;
	}

	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//描画
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	procHeader();
	if (g_pClearBackground != NULL)	renderSprite(g_pClearBackground);
}

/* 関数名　	：procClearBegin()
 * 処理内容　：クリア画面の終了時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procClearEnd() {
	if (g_pClearBackground != NULL) {
		disposeSprite(g_pClearBackground);
		g_pClearBackground = NULL;
	}
}