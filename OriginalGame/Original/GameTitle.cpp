/* GameTitle
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021/09/29
 */
#include "COriginalGameApp.h"
#include "GameResource.h"

 //___________________________________________________________________________________________________
 //変数宣言
 //___________________________________________________________________________________________________
 // ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//サイズ
//const XMFLOAT2 LOGO_SIZE = { 816.f,167.f };
const XMFLOAT2 TITLE_SIZE = { 945.f,1080.f };
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//座標
const XMFLOAT2 LOGO_POS = { 0.f,240.f };
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//画像・音声
CPicture* g_pLogo = NULL;
CPicture* g_pTitleBackground = NULL;						//タイトル画面の画像を管理する変数
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//ステータス管理
ePhase g_TitlePhase = eBegin;								//タイトル画面のフェーズを管理する変数
eGameStatus g_NextStatusFromTitle = eNone;					//タイトルから次へ進むときのフロー管理する変数



/* タイトルの処理を行う部分
 */
void COriginalGameApp::procTitle() {
	//フェーズの進行状態によって処理を切り替える
	switch (g_TitlePhase) {
		//開始時
	case eBegin: {
		//タイトル画面の開始時の処理を行う
		procTitleBegin();
		//進行状態のメインに切り替える
		g_TitlePhase = eMain;
	}break;
		//メイン
	case eMain: {
		//タイトル画面のメイン処理を行う
		procTitleMain();
	}break;
		//終了時
	case eEnd: {
		//タイトル画面の終了処理を行う
		procTitleEnd();

		//再度タイトル画面に来た時に開始から処理を行うために
		//フェーズに戻っておく
		g_TitlePhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_NextStatusFromTitle);
	}break;
	}
}

/* 関数名　	：procTitleBegin()
 * 処理内容　：タイトル画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procTitleBegin() {
	//___________________________________________________________________________
	//音声を作成する
	if (!g_pSound)g_pSound = createSound(Start_Game, false);
	//____________________________________________________________________________	
	//___________________________________________________________________________
	//画像を作成する
	//___________________________________________________________________________
	if (!g_pHeader) g_pHeader = createSprite(Tex_Header, HEADER_SIZE, HEADER_POS);
	if (!g_pTitleBackground) g_pTitleBackground = createSprite(Tex_Title, TITLE_SIZE);
}

/* 関数名　	：procTitleBegin()
 * 処理内容　：タイトル画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procTitleMain() {
	//Xキーを押されたらフェーズを終了に変更し、
	//ゲーム本編にステータスを移行する準備をする
	if (m_pDirectInput->isPressedOnce(DIK_SPACE)) {
		g_TitlePhase = eEnd;
		g_NextStatusFromTitle = ePlaying;
	}

	//___________________________________________________________________________
	//スコアの表示
	//___________________________________________________________________________
	ShowScore(g_pScore, g_iScore, g_iDigit, SCORE_POS, FONT_SIZE);
	ShowScore(g_pHiScore, g_iHiScore, g_iHiDigit, HISCORE_POS, FONT_SIZE);

	//___________________________________________________________________________
	//描画
	//___________________________________________________________________________
	if (g_pHeader)renderSprite(g_pHeader);
	if (g_pTitleBackground)	renderSprite(g_pTitleBackground);
	//___________________________________________________________________________
	//音声
	if (g_pSound)playSound(g_pSound);
	//___________________________________________________________________________
}

/* 関数名　	：procTitleBegin()
 * 処理内容　：タイトル画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procTitleEnd() {
	//___________________________________________________________________________
	//破棄
	//___________________________________________________________________________
	/*if (g_pLogo) {
		disposeSprite(g_pLogo);
		g_pLogo = NULL;
	}*/

	if (g_pTitleBackground != NULL) {
		disposeSprite(g_pTitleBackground);
		g_pTitleBackground = NULL;
	}
	//___________________________________________________________________________
	//音声破棄
	//___________________________________________________________________________
	if (g_pSound) {
		disposeSound(g_pSound);
		g_pSound = NULL;
	}
}