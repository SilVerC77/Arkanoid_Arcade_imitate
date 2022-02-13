/* GamePlay
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021/09/29
 */
#include "COriginalGameApp.h"
#include "GameResource.h"
 //#include "Block.h"

  //___________________________________________________________________________________________________
  //変数定義
  //___________________________________________________________________________________________________
  //Itemの構造体
struct Item {
	CPicture* body;
	ePowerType eIndex;
};
struct Enemy {
	CPicture* body;
	CPicture* death;
	XMFLOAT2 velocity;
	bool type;
	bool dead;
	int dir;
	int counter;
	int animindex;
};
struct Boss {
	CPicture* body;
	CPicture* death;
	CPicture* laser[5];
	XMFLOAT2 laser_vel[5];
	int hp;
	int score;
	int laser_counter;
	int animindex;
	int animcounter;
	bool damage;
};
//___________________________________________________________________________________________________
//変数宣言
//___________________________________________________________________________________________________
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//個数管理
const int BLOCK_COUNT_Y = 18;						//ブロック縦の個数
const int BLOCK_COUNT_X = 13;						//ブロック横の個数
const int BALL_COUNT = 3;							//ボールの個数
const int MAX_ROUND = 33;							//最大ラウンド
const int FULLHP = 3;								//Vaus初期残機数
const int MAXHP = 5;								//Vaus最大残機数
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//速度・角度管理
const int BOSS_LASER_RATE = 10;						//ボス攻撃の連射速度
const int LASER_RATE = 10;							//レーザーの連射速度
const float LASER_SPEED = 30.f;						//レーザーの速度
const float ITEM_DROP = 5.f;						//アイテムの落ちる速度
const float BALL_SPEED = 12.f;						//Ball初期速度
const float BALL_LIMIT_SPEED = 24.f;				//Ball最高速度
const float BALL_ANGLE = 55.f;						//Ball初期角度
const float ENEMY_SPEED = 2.5f;						//敵の移動速度
const XMFLOAT2 BOSS_BULLET_SPEED = { 5.f,-10.f };   //ボス弾移動速度
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//アニメーション管理
const int BOSS_SHOOT = 8;
const int BOSS_CLOSE = BOSS_SHOOT + 3;
const int BOSS_CD = BOSS_CLOSE + 3;
const int BLOCK_ANIM = 5;
const int ITEM_ANIM = 8;
const int ENEMY_ANIM = 10;
const int EXPLODE_ANIM = 10;
const int BOSS_LASER_ANIM = 5;
const int ROUND_APPEAR = 2 * 60;
int g_iExitIndex = 0;
int g_iBossIndex = 0;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//サイズ
const float FRAME_WIDTH = 34.f;
const XMFLOAT2 VAUS_SIZE = { 128.f,32.f };
const XMFLOAT2 BALL_SIZE = { 20.f,16.f };
const XMFLOAT2 HP_SIZE = { 65.f,35.f };
const XMFLOAT2 LASER_SIZE = { 64.f,32.f };
const XMFLOAT2 ITEM_SIZE = { 64.f,28.f };
const XMFLOAT2 BREAK_SIZE = { 34.f,160.f };
const XMFLOAT2 ENEMY_SIZE = { 50.f,50.f };
const XMFLOAT2 EXIT_SIZE = { 128.f,34.f };
const XMFLOAT2 BLOCK_SIZE = { 68.f,34.f };
const XMFLOAT2 BOSS_SIZE = { 248.f,384.f };
const XMFLOAT2 BOSS_BULLET_SIZE = { 20.f,20.f };
const XMFLOAT2 STAGE_SIZE = { 950.f,1010.f };
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//その他
const int ITEM_DROP_CHANCE = 5;
const int ENEMY_APPEAR_PROB = 10;
const float ENEMY_APPEAR_RATE = 5 * 60;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//座標
const XMFLOAT2 VAUS_POS = {							//Vaus初期位置
	0.f,											//X
	-(WINDOW_HEIGHT - VAUS_SIZE.y) / 2.f + 65.f };	//Y
const XMFLOAT2 ENEMY_POS = { 240.f,454.f };			//敵が出るところ
const XMFLOAT2 STAGE_POS = {						//背景画像の位置
	0.f,											//Ｘ
	-(WINDOW_HEIGHT - STAGE_SIZE.y) / 2.f };		//Ｙ
const float BORDER[4] = {							//境界線
	-STAGE_SIZE.x / 2.f + FRAME_WIDTH ,				//左
	STAGE_POS.y + STAGE_SIZE.y / 2.f - FRAME_WIDTH ,//上
	STAGE_SIZE.x / 2.f - FRAME_WIDTH ,				//右
	WINDOW_BOTTOM };								//下
const XMFLOAT2 BREAK_POS = {						//ブレイク画像の位置
	(STAGE_SIZE.x - FRAME_WIDTH) * 0.5f,
	-460.f };
const XMFLOAT2 ROUND_POS = { -150.f,-250.f };				//ラウンド情報
const XMFLOAT2 BOSS_POS = { 0.f,100.f };			//ボス
const XMFLOAT2 BOSS_MOUTH_POS = { 0.f,90.f };		//ボスの口
const float BOSS_ATK_POS = 200.f;					//ボス攻撃判定範囲　　　　　　　
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//画像管理
CPicture* g_pStage = NULL;							//ステージ画像
CPicture* g_pBreak = NULL;							//Break
CPicture* g_pHp[MAXHP];								//残機
CPicture* g_pHighScore;
CPicture* g_pExit[2] = { NULL,NULL };
CFont* g_pRound[3];
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//クラス・構造体
CVaus* g_pVaus = NULL;								//Vaus
CBall* g_pBall[BALL_COUNT];							//Ball
CBlock* g_pBlock[BLOCK_COUNT_Y][BLOCK_COUNT_X];		//ブロック
Item g_Item = { NULL,eNoPower };					//アイテム
Enemy g_Enemy[3];									//敵
Boss* DOH;
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//音声
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
//ステータス管理
bool automove = false;								//自動運転モード
int g_iRound = 1;									//ステージ管理する変数
int g_iVausHp = FULLHP;								//残機
int g_iTimer = 0;									//ステージの経った時間
bool g_bNewRound = true;							//新しいラウンドであるか
bool g_bBreak = false;
bool g_bTestMode = true;
ePhase g_GamePhase = eBegin;						//ゲーム画面のフェーズを管理する変数
eGameStatus g_NextStatusFromGame = eNone;			//ゲーム画面から次へ進むときのフローを管理する変数

//_______________________________________________________________________________________________________
// ゲーム本編の処理を行う部分
// eBegin: 開始時
// eMain: メイン
// eEnd: 終了時
//_______________________________________________________________________________________________________
void COriginalGameApp::procGame()
{
	switch (g_GamePhase) {
		//開始時
	case eBegin: {
		//ゲーム画面の開始処理
		procPlayBegin();

		//進行状態のメインに切り替える
		g_GamePhase = eMain;
		//次のフローを初期化
		g_NextStatusFromGame = eNone;
	}break;
		//メイン
	case eMain: {
		//ゲーム画面のメイン処理
		procPlayMain();

	}break;
		//終了時
	case eEnd: {
		//ゲーム画面の終了処理を行う
		procPlayEnd();
		//再度ゲーム画面に来た時に開始から処理を行うために
		//フェーズを戻しておく
		g_GamePhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_NextStatusFromGame);
	}break;
	}
}
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//関数名　	：procPlayBegin()
//処理内容　：ゲーム画面の開始時に行う処理
//引数　　　：なし
//戻り値　　：なし
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
void COriginalGameApp::procPlayBegin() {
	//乱数の種
	srand((unsigned)time(NULL));
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//音声
	if (g_iRound == MAX_ROUND) setSound(Boss_Fight);
	else setSound(Round_Start);
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿

	//最大ラウンドより多い場合、初期化
	if (g_iRound > MAX_ROUND) {
		g_iRound = 1;
		g_iVausHp = FULLHP;
		g_GamePhase = eBegin;
	}

	//ステージ画像を作成する
	//ステージの画像は4ラウンドで繰り返す
	if (g_pStage)	disposeSprite(g_pStage);
	if (g_iRound == MAX_ROUND)g_pStage = createSprite(Tex_StageBoss, STAGE_SIZE.x, STAGE_SIZE.y);
	else {
		int background = g_iRound % 4;
		switch (background) {
		case 1: g_pStage = createSprite(Tex_Stage01, STAGE_SIZE.x, STAGE_SIZE.y); break;
		case 2: g_pStage = createSprite(Tex_Stage02, STAGE_SIZE.x, STAGE_SIZE.y); break;
		case 3: g_pStage = createSprite(Tex_Stage03, STAGE_SIZE.x, STAGE_SIZE.y); break;
		case 0: g_pStage = createSprite(Tex_Stage04, STAGE_SIZE.x, STAGE_SIZE.y); break;
		}
	}
	g_pStage->setPos(STAGE_POS);
	//＿＿＿＿＿＿＿＿
	//Vaus初期設定
	//＿＿＿＿＿＿＿＿
	if (g_pVaus) delete g_pVaus;
	g_pVaus = new CVaus;
	g_pVaus->body = createSprite(Tex_Vaus_Normal, VAUS_SIZE.x, VAUS_SIZE.y);			//本体
	g_pVaus->shadow = createSprite(Tex_Vaus_Normal_Shadow, VAUS_SIZE.x, VAUS_SIZE.y);	//影
	g_pVaus->setPos(VAUS_POS);
	//残機画像初期設定
	for (int i = 0; i < g_iVausHp; ++i) {
		if (!g_pHp[i]) {
			g_pHp[i] = createSprite(Tex_Hp, HP_SIZE.x, HP_SIZE.y);
			g_pHp[i]->setPos((BORDER[0] + HP_SIZE.x / 2.f) + (float)i * HP_SIZE.x, BORDER[3] + HP_SIZE.y / 2.f);
		}
	}
	//＿＿＿＿＿＿＿＿
	//Ball初期設定
	//＿＿＿＿＿＿＿＿
	for (int i = 0; i < BALL_COUNT; ++i)
		if (g_pBall[i]) {
			delete g_pBall[i];
		}
	g_pBall[0] = new CBall(BALL_ANGLE, BALL_SPEED);
	g_pBall[0]->body = createSprite(Tex_Ball, BALL_SIZE.x, BALL_SIZE.y);
	g_pBall[0]->shadow = createSprite(Tex_Ball_Shadow, BALL_SIZE.x, BALL_SIZE.y);
	g_pBall[0]->setPos(g_pVaus);
	//＿＿＿＿＿＿＿＿＿
	//ブロック配列　（蝦名伸太郎）
	//＿＿＿＿＿＿＿＿＿ 
	StageBlock();
	//________________
	//ボス
	//________________
	if (g_iRound == MAX_ROUND) {
		if (!DOH) {
			DOH = new Boss;
			DOH->body = createSprite(Tex_Boss, BOSS_SIZE.x, BOSS_SIZE.y);
			DOH->body->setPos(BOSS_POS.x, BOSS_POS.y);
			for (int i = 0; i < 5; ++i) {
				DOH->laser[i] = NULL;
				DOH->laser_vel[i] = { 10.f,10.f };
			}
			DOH->death = NULL;
			DOH->hp = 16;
			DOH->score = 1000;
			DOH->animindex = 0;
			DOH->laser_counter = 0;
			DOH->animcounter = 0;
			DOH->damage = false;
		}
	}
	//＿＿＿＿＿＿＿＿＿
	//ラウンド数
	//＿＿＿＿＿＿＿＿＿
	for (int i = 0; i < 3; ++i)if (g_pRound[i])disposeFont(g_pRound[i]);
	int digit = 0;
	for (int i = g_iRound; i > 0; i /= 10)digit++;
	g_pRound[0] = createFont(Tex_Alphabet, 5, FONT_SIZE.x, FONT_SIZE.y);
	g_pRound[1] = createFont(Tex_Number, digit, FONT_SIZE.x, FONT_SIZE.y);
	g_pRound[2] = createFont(Tex_Alphabet, 5, FONT_SIZE.x, FONT_SIZE.y);
	XMFLOAT2 pos = ROUND_POS;
	g_pRound[0]->setPos(pos.x, pos.y);
	pos.x += FONT_SIZE.x * 7.f;
	g_pRound[1]->setPos(pos.x, pos.y);
	pos.x = ROUND_POS.x + FONT_SIZE.x * 1.5f;
	pos.y -= FONT_SIZE.y * 1.5f;
	g_pRound[2]->setPos(pos.x, pos.y);
	//＿＿＿＿＿＿＿＿＿
	//初期化
	//＿＿＿＿＿＿＿＿＿
	g_bBreak = false;
	g_iTimer = 0;
}

/* 関数名　	：procGameMain()
 * 処理内容　：ゲーム画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procPlayMain() {

	//TestAREA//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_bTestMode) {
		if (m_pDirectInput->isPressedOnce(DIK_R)) g_GamePhase = eEnd;
		if (m_pDirectInput->isPressedOnce(DIK_P)) g_pVaus->setPower(ePlayerExtend);
		if (m_pDirectInput->isPressedOnce(DIK_L)) g_pVaus->setPower(eLaser);
		if (m_pDirectInput->isPressedOnce(DIK_D)) g_pVaus->setPower(eDisruption);
		if (m_pDirectInput->isPressedOnce(DIK_C)) g_pVaus->setPower(eCatch);
		if (m_pDirectInput->isPressedOnce(DIK_B)) g_pVaus->setPower(eBreak);
		if (m_pDirectInput->isPressedOnce(DIK_S)) g_pVaus->setPower(eSpeedDown);
		if (m_pDirectInput->isPressedOnce(DIK_A)) automove = !automove;
		if (m_pDirectInput->isPressedOnce(DIK_A)) g_iScore += 1000;
		if (m_pDirectInput->isPressedOnce(DIK_T)) {
			for (int i = 0; i < 3; ++i)if (g_pBall[i])if (g_pBall[i]->body)
				g_pBall[i]->disposeBall();
		}
	}

	//____________________________________________________________________________________________________________
	//ステージステータス表示
	//____________________________________________________________________________________________________________
	for (int i = 0; i < 3; ++i)if (g_pRound[i]) {
		g_iTimer++;
		if (g_iTimer > ROUND_APPEAR) {
			disposeFont(g_pRound[i]);
			g_pRound[i] = NULL;
		}
	}
	//________________________________________________________________________________________________________________________
	//Vaus処理
	//________________________________________________________________________________________________________________________
	if (g_pVaus && g_pVaus->body) {
		if (!automove)
			g_pVaus->move(m_pDirectInput->isKeyPressed(DIK_LEFTARROW), m_pDirectInput->isKeyPressed(DIK_RIGHTARROW));
		else
			if (g_pBall[0] && g_pBall[0]->body) g_pVaus->move(g_pBall[0]->getPos().x);
		g_pVaus->border(BORDER[0], BORDER[2], g_bBreak);
	}
	if (!g_pVaus) g_GamePhase = eEnd;
	//_________________________________________________________________________________
	//パワーに関する処理
	//_________________________________________________________________________________
	//CATCH//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus) g_pVaus->releaseBall(automove || m_pDirectInput->isKeyPressed(DIK_SPACE));

	//LASER//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus)if (g_pVaus->canShoot(LASER_SPEED, LASER_RATE, automove || m_pDirectInput->isPressedOnce(DIK_SPACE))) {
		for (int i = 0; i < 2; ++i) {
			if (!g_pVaus->laser[i]) {
				g_pVaus->laser[i] = createSprite(Tex_Laser, LASER_SIZE.x, LASER_SIZE.y);
				g_pVaus->laser[i]->setPos(g_pVaus->getPos());
				//_____________________________________
				//音声
				setSound(Shoot_Laser);
				//_____________________________________
				break;
			}
		}
	}
	//消えるレーザーを管理する
	//ブロックに当たったレーザーをベクトル型に保存する
	vector<int>dead;
	for (int i = 0; i < 2; ++i) {
		if (!g_pVaus)break;
		if (g_pVaus->laser[i]) {
			for (int y = 0; y < BLOCK_COUNT_Y; ++y)
				for (int x = 0; x < BLOCK_COUNT_X; ++x) {
					if (!g_pBlock[y][x])continue;
					if (g_pVaus->laser[i]->collision(g_pBlock[y][x]->body)) {
						g_pBlock[y][x]->damage();
						dead.push_back(i);
					}
				}
			//枠外にでたら破棄
			float posY = g_pVaus->laser[i]->getPos().y + g_pVaus->laser[i]->getSize().y / 2.f;
			if (posY > BORDER[1])	dead.push_back(i);
		}
	}
	//保存したレーザーを消す
	for (auto j : dead) {
		disposeSprite(g_pVaus->laser[j]);
		g_pVaus->laser[j] = NULL;
	}
	//DISRUPTION//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus) if (g_pVaus->getPower() == eDisruption) {
		int alive = -1;
		float angle = 0.f;
		for (int i = 0; i < BALL_COUNT; ++i) {
			if (!g_pBall[i])continue;
			if (!g_pBall[i]->body)continue;
			alive = i;
			angle = g_pBall[alive]->getAngle();
			break;
		}
		//ボール存在するなら
		//現在のボールのところで新しいボール作る
		if (alive >= 0) {
			float delta = -10.f;
			for (int i = 0; i < BALL_COUNT; ++i) {
				if (i == alive) continue;
				if (!g_pBall[i]) {
					g_pBall[i] = new CBall(angle + delta, g_pBall[alive]->getSpeed(), true);
					g_pBall[i]->body = createSprite(Tex_Ball, BALL_SIZE.x, BALL_SIZE.y);
					g_pBall[i]->shadow = createSprite(Tex_Ball_Shadow, BALL_SIZE.x, BALL_SIZE.y);
					g_pBall[i]->setPos(g_pBall[alive]->getPos());
					delta *= -1.f;
				}
			}
		}
		//パワーない状態に戻す
		g_pVaus->setPower(eNoPower);
	}

	//PLAYEREXTEND//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus)if ((g_pVaus->getPower() == ePlayerExtend)) {
		g_iVausHp++;
		if (g_iVausHp < 0)g_iVausHp = 0;
		if (g_iVausHp > MAXHP)g_iVausHp = MAXHP;
		if (!g_pHp[g_iVausHp - 1]) {
			g_pHp[g_iVausHp - 1] = createSprite(Tex_Hp, HP_SIZE.x, HP_SIZE.y);
			g_pHp[g_iVausHp - 1]->setPos((BORDER[0] + HP_SIZE.x / 2.f) + float(g_iVausHp - 1) * HP_SIZE.x, BORDER[3] + HP_SIZE.y / 2.f);
		}
		//パワーない状態に戻す
		g_pVaus->setPower(eNoPower);
	}
	//SPEEDDOWN//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus)if (g_pVaus->getPower() == eSpeedDown) {
		for (int i = 0; i < BALL_COUNT; ++i) {
			if (!g_pBall[i])continue;
			if (!g_pBall[i]->body)continue;
			g_pBall[i]->setSpeed(g_pBall[i]->getSpeed() / 2.f);
		}
		//パワーない状態に戻す
		g_pVaus->setPower(eNoPower);
	}
	//BREAK//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus)if (g_pVaus->getPower() == eBreak) {
		if (!g_pBreak) g_pBreak = createSprite(Tex_Frame_Break, BREAK_SIZE, BREAK_POS);
		g_bBreak = true;
	}
	if (g_pBreak) {
		g_pBreak->stepAnimation();
		g_pBreak->setAnimationRange(1, 3);
	}
	if (g_pBreak && g_pVaus) {
		if (g_pBreak->collision(g_pVaus->body)) {
			g_iScore += 10000;
			//_____________________________________
			//音声
			setSound(Break);
			//_____________________________________
			g_GamePhase = eEnd;
		}
	}
	//パワー変わった時画像を変更//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (g_pVaus)if (g_pVaus->powerChange()) {
		XMFLOAT4 pos = g_pVaus->getPos();
		g_pVaus->dispose();
		if (g_pVaus->getPower() == eLaser) {
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			//音声
			setSound(Got_Laser);
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			g_pVaus->body = createSprite(Tex_Vaus_Laser, VAUS_SIZE);			//本体
			g_pVaus->shadow = createSprite(Tex_Vaus_Laser_Shadow, VAUS_SIZE);	//影
		}
		else if (g_pVaus->getPower() == eExpand) {
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			//音声
			setSound(Expand);
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			g_pVaus->body = createSprite(Tex_Vaus_Expand, VAUS_SIZE.x * 1.5f, VAUS_SIZE.y);			//本体
			g_pVaus->shadow = createSprite(Tex_Vaus_Expand_Shadow, VAUS_SIZE.x * 1.5f, VAUS_SIZE.y);	//影
		}
		else {
			g_pVaus->body = createSprite(Tex_Vaus_Normal, VAUS_SIZE);			//本体
			g_pVaus->shadow = createSprite(Tex_Vaus_Normal_Shadow, VAUS_SIZE);	//影
		}
		g_pVaus->setPos(pos);
	}
	//________________________________________________________________________________________________________________
	//Ballの処理
	//________________________________________________________________________________________________________________
	for (int i = 0; i < BALL_COUNT; ++i)if (g_pBall[i]) if (g_pVaus) {
		g_pBall[i]->move(BALL_LIMIT_SPEED);
		//_____________________________________
		//音声
		if (g_pBall[i]->body)
			if (g_pBall[i]->body->collision(g_pVaus->body)) {
				setSound(Ball_Bar);
			}
		//_____________________________________
		g_pBall[i]->bounce(g_pVaus);
		g_pBall[i]->border(BORDER[0], BORDER[1], BORDER[2]);

		//if (getInput()->isKeyPressed(DIK_V)) g_pBall[i]->setAngle(0.f);

	}
	//画面下にでたらBallを破棄
	for (int i = 0; i < BALL_COUNT; ++i)if (g_pBall[i])if (g_pBall[i]->body)
		if (g_pBall[i]->getPos().y < BORDER[3]) {
			delete g_pBall[i];
			g_pBall[i] = NULL;
		}
	//Ball存在するか確認,存在するBALLない場合は終了処理に行く
	bool alive = false;
	for (int i = 0; i < BALL_COUNT; ++i)
		if (g_pBall[i]) {
			alive = true;
			break;
		}
	if (!alive) {
		if (g_pVaus) {
			delete g_pVaus;
			g_pVaus = NULL;
		}
	}

	//BALLとブロックの当たり判定処理
	for (int i = 0; i < BALL_COUNT; ++i) {
		if (!g_pBall[i])continue;
		if (!g_pBall[i]->body)continue;
		//ブロック番号と当たり判定の距離を格納するベクトル型
		//vector<pair<int, float>> length;
		//一番近いブロックの番号を格納
		pair<int, float> shortest = {-1,FLT_MAX};
		XMFLOAT2 pos;
		float hit_near = 1.f;
		eDirection dir;
		for (int y = 0; y < BLOCK_COUNT_Y; ++y)
			for (int x = 0; x < BLOCK_COUNT_X; ++x) {
				if (!g_pBlock[y][x])continue;
				//当たったら、ブロック番号と当たった距離を保存する
				if (g_pBall[i]->collisionRay(g_pBlock[y][x]->body, pos, hit_near, dir)) {
					int b = y * BLOCK_COUNT_X + x;
					if (hit_near < shortest.second) {
						shortest = { b,hit_near };
					}
					//length.push_back({ b, hit_near });
					
				}
			}
		if(shortest.first>=0){
			int y = shortest.first / BLOCK_COUNT_X;
			int x = shortest.first % BLOCK_COUNT_X;
			if (g_pBall[i]->collisionRay(g_pBlock[y][x]->body, pos, hit_near, dir)) {
				//__________________________________________
				//音声
				int index = g_pBlock[y][x]->getIndex();
				if (index == 9 || index == 10) setSound(Ball_SG_Block);
				//__________________________________________
				g_pBall[i]->setPos(pos.x, pos.y);
				g_pBall[i]->bounce(dir, g_pBlock[y][x]->body);
				g_pBlock[y][x]->damage();
			}
		}
		
		////距離で当たり判定の順番を決めてから当たり判定の処理
		//sort(length.begin(), length.end(),
		//	[](const pair<int, float>& a, const pair<int, float>& b) {return a.second < b.second; });
		//
		//for (auto j : length) {
		//	int y = j.first / BLOCK_COUNT_X;
		//	int x = j.first % BLOCK_COUNT_X;
		//	if (g_pBall[i]->collisionRay(g_pBlock[y][x]->body, pos, hit_near, dir)) {
		//		//__________________________________________
		//		//音声
		//		int index = g_pBlock[y][x]->getIndex();
		//		if (index == 9 || index == 10) setSound(Ball_SG_Block);
		//		//__________________________________________
		//		g_pBall[i]->setPos(pos.x, pos.y);
		//		g_pBall[i]->bounce(dir, g_pBlock[y][x]->body);
		//		g_pBlock[y][x]->damage();
		//		break;
		//	}
		//}

	}
	//Bossとの処理//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (DOH && g_pBall[0]) {
		if (g_pBall[0]->body && DOH->body) {
			XMFLOAT2 pos;
			float hit_near = 1.f;
			eDirection dir;
			if (g_pBall[0]->collisionRay(DOH->body, pos, hit_near, dir)) {
				g_pBall[0]->setPos(pos.x, pos.y);
				g_pBall[0]->bounce(dir, DOH->body);
				DOH->damage = true;
			}
		}
	}
	//________________________________________________________________________________________________________________
	//Bossの処理
	//________________________________________________________________________________________________________________
	if (DOH) {
		if (DOH->damage) {
			DOH->hp--;
			//一回当たると点数1000加算
			g_iScore += DOH->score;
			//__________________________
			// 音声
			setSound(Ball_Boss);
			//__________________________
		}
		if (DOH->hp <= 0) {
			if (DOH->body) {
				if (!DOH->death) {
					DOH->death = createSprite(Tex_Boss, BOSS_SIZE.x, BOSS_SIZE.y);
					DOH->death->setPos(BOSS_POS);
					disposeSprite(DOH->body);
					DOH->body = NULL;
					//__________________________
					// 音声
					setSound(Boss_Dead);
					//__________________________
					if (g_pBall[0])g_pBall[0]->disposeBall();
				}
			}
			DOH->damage = false;
		}

		//ボスの攻撃
		if (DOH && g_pVaus)if (DOH->body) {
			if (DOH->animindex >= 3 && DOH->animindex < BOSS_SHOOT) {
				DOH->laser_counter++;
				if (DOH->laser_counter > BOSS_LASER_RATE) {
					DOH->laser_counter = 0;
					for (int i = 0; i < 5; ++i)if (!DOH->laser[i]) {
						DOH->laser[i] = createSprite(Tex_Boss_Bullet, BOSS_BULLET_SIZE.x, BOSS_BULLET_SIZE.y);
						DOH->laser[i]->setPos(BOSS_MOUTH_POS);
						XMFLOAT4 vauspos = g_pVaus->getPos();
						float dis = vauspos.x - DOH->body->getPos().x;
						if (dis < -BOSS_ATK_POS)DOH->laser_vel[i] = { -1.f ,1.f };
						else if (dis < 0.f)DOH->laser_vel[i] = { -0.5f ,1.f };
						else if (dis < BOSS_ATK_POS)DOH->laser_vel[i] = { 0.5f,1.f };
						else DOH->laser_vel[i] = { 1.f,1.f };
						break;
					}
				}
			}
			//プレイヤーに当たった時の処理
			if (g_pVaus)if (g_pVaus->body)
				for (int i = 0; i < 5; ++i)if (DOH->laser[i]) {
					if (DOH->laser[i]->collision(g_pVaus->body)) {
						delete g_pVaus;
						g_pVaus = NULL;
						break;
					}
				}
		}
		//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
		//弾の処理
		//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
		for (int i = 0; i < 5; ++i)if (DOH->laser[i]) {
			XMFLOAT4 pos = DOH->laser[i]->getPos();
			pos.x += DOH->laser_vel[i].x * BOSS_BULLET_SPEED.x;
			pos.y += DOH->laser_vel[i].y * BOSS_BULLET_SPEED.y;
			//画面外にでると破棄
			if (pos.y < BORDER[3]) {
				disposeSprite(DOH->laser[i]);
				DOH->laser[i] = NULL;
			}
			if (DOH->laser[i]) DOH->laser[i]->setPos(pos);
		}
		//___________________________
		//アニメーション
		//___________________________
		//本体アニメーション
		DOH->animcounter++;
		if (DOH->body) {
			int animindex = 0;
			if (DOH->animcounter > ENEMY_ANIM) {
				DOH->animindex++;
				DOH->animcounter = 0;
			}
			if (DOH->animindex < 3)animindex = DOH->animindex;
			else if (DOH->animindex < BOSS_SHOOT)animindex = 3;
			else if (DOH->animindex < BOSS_CLOSE)animindex = BOSS_CLOSE - DOH->animindex;
			else if (DOH->animindex < BOSS_CD)animindex = 0;
			else DOH->animindex = 0;
			if (DOH->damage) {
				animindex += 4;
			}
			DOH->damage = false;
			DOH->body->setAnimation(animindex);
		}
		//死亡アニメーション
		if (DOH->death) {
			DOH->death->setAnimationRange(8, 29);
			if (DOH->animcounter > ENEMY_ANIM) {
				DOH->animcounter = 0;
				DOH->death->stepAnimation();
			}
			if (DOH->death->getAnimIndex() >= 29)g_GamePhase = eEnd;
		}
		//弾アニメーション
		static int boss_laser_cnt[3];
		for (int i = 0; i < 5; ++i)if (DOH->laser[i]) {
			boss_laser_cnt[i]++;
			if (boss_laser_cnt[i] > BOSS_LASER_ANIM) {
				boss_laser_cnt[i] = 0;
				DOH->laser[i]->stepAnimation();
			}
		}
	}
	//________________________________________________________________________________________________________________
	//Blockの処理
	//________________________________________________________________________________________________________________
	//ブロックのHPを確認して、０の場合消す
	//乱数を生成して、アイテムを出す
	//銀色のブロックはアイテム出さない
	if (g_iRound != MAX_ROUND) {
		int item = -1;
		for (int y = 0; y < BLOCK_COUNT_Y; ++y)
			for (int x = 0; x < BLOCK_COUNT_X; ++x) {
				if (g_pBlock[y][x] && g_pBlock[y][x]->getHP() <= 0) {
					if (!g_Item.body && g_pBlock[y][x]->canDrop()) {
						item = rand() % 100;
						if (item < ITEM_DROP_CHANCE) {
							int power = rand() % 7 + 1;
							g_Item.eIndex = static_cast<ePowerType>(power);
							g_Item.body = createSprite(Tex_Item, ITEM_SIZE.x, ITEM_SIZE.y);
							int animBegin = (g_Item.eIndex - 1) * 8 + 1;
							g_Item.body->setAnimationRange(animBegin, animBegin + 6);
							g_Item.body->setPos(g_pBlock[y][x]->getPos());
						}
					}
					//スコアに加算
					g_iScore += g_pBlock[y][x]->getScore();
					delete g_pBlock[y][x];
					g_pBlock[y][x] = NULL;
					//________________________________
					//音声
					setSound(Ball_Block);
					//________________________________
				}
			}
		//ブロックが存在するか確認
		//存在するブロックない場合は終了処理へ
		int blockalive = 0;
		for (int y = 0; y < BLOCK_COUNT_Y; ++y)
			for (int x = 0; x < BLOCK_COUNT_X; ++x) {
				if (g_pBlock[y][x] && g_pBlock[y][x]->getIndex() != 10)blockalive++;
			}
		if (blockalive <= 0) g_GamePhase = eEnd;
	}
	//アニメーション制御
	for (int y = 0; y < BLOCK_COUNT_Y; ++y)
		for (int x = 0; x < BLOCK_COUNT_X; ++x) {
			if (g_pBlock[y][x])g_pBlock[y][x]->damageAnim(BLOCK_ANIM);
		}
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//Itemの処理
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	if (g_Item.body) {
		g_Item.body->setPos(
			g_Item.body->getPos().x,
			g_Item.body->getPos().y - ITEM_DROP);
		//画面↓に出ると破棄
		if (g_Item.body->getPos().y < WINDOW_BOTTOM) {
			disposeSprite(g_Item.body);
			g_Item.body = NULL;
		}
	}
	if (g_Item.body && g_pVaus && g_pVaus->body) {
		if (g_Item.body->collision(g_pVaus->body)) {
			g_pVaus->setPower(g_Item.eIndex);
			disposeSprite(g_Item.body);
			g_Item.body = NULL;
		}
	}
	if (g_Item.body) {
		static int item_cnt = 0;
		item_cnt++;
		if (item_cnt > ITEM_ANIM) {
			item_cnt = 0;
			g_Item.body->stepAnimation();
		}
	}

	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//敵の処理
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	if (g_iRound != MAX_ROUND) {
		//乱数を出して、敵を生成
		int appear = rand() % 100;
		int dir = 1 - rand() % 2 * 2;
		static int cd = 0;
		cd++;
		if (appear >= ENEMY_APPEAR_PROB && cd > ENEMY_APPEAR_RATE) {
			for (int i = 0; i < 3; ++i) {
				if (!g_Enemy[i].body) {
					g_Enemy[i].body = createSprite(Tex_Enemy, ENEMY_SIZE.x, ENEMY_SIZE.y);
					int range = (g_iRound - 1) % 4 * 8;
					g_Enemy[i].body->setAnimationRange(range, range + 7);
					g_Enemy[i].body->setPos(ENEMY_POS.x * (float)dir, ENEMY_POS.y);
					g_Enemy[i].death = NULL;
					g_Enemy[i].dir = 4;
					g_Enemy[i].animindex = 0;
					g_Enemy[i].type = false;
					g_Enemy[i].dead = false;
					cd = 0;
					break;
				}
			}
		}
	}
	//＿＿＿＿＿＿＿＿＿＿＿＿
	//移動の処理
	//＿＿＿＿＿＿＿＿＿＿＿＿
	static float enemy_angle[3];
	static int enemy_counter[3];
	for (int i = 0; i < 3; ++i) {
		if (g_Enemy[i].body) {
			XMFLOAT4 pos = g_Enemy[i].body->getPos();
			if (g_Enemy[i].type == false) {
				if (g_Enemy[i].dir > 4)g_Enemy[i].dir = 1;
				switch (g_Enemy[i].dir) {
				case 1: g_Enemy[i].velocity = { -1.f , 0.f }; break;
				case 2: g_Enemy[i].velocity = { 0.f , 1.f }; break;
				case 3: g_Enemy[i].velocity = { 1.f , 0.f }; break;
				default: g_Enemy[i].velocity = { 0.f ,-1.f };
				}
			}
			else {
				enemy_counter[i]++;
				if (enemy_counter[i] > (1 * 60)) {
					g_Enemy[i].dir = (rand() % 18 + 18) * 10;
					enemy_counter[i] = 0;
				}
				if (enemy_angle[i] < DegtoRad((float)g_Enemy[i].dir))
					enemy_angle[i] += 0.05f;
				else enemy_angle[i] -= 0.05f;
				g_Enemy[i].velocity.x = cos(enemy_angle[i]);
				g_Enemy[i].velocity.y = sin(enemy_angle[i]);
			}
			pos.x += g_Enemy[i].velocity.x * ENEMY_SPEED;
			pos.y += g_Enemy[i].velocity.y * ENEMY_SPEED;
			g_Enemy[i].body->setPos(pos);
		}
	}
	//ブロック//--------------------------------------------
	//ブロックに当たると乱数で次の移動方向を決める
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		if (!g_Enemy[i].type) {
			XMFLOAT4 pos = g_Enemy[i].body->getPos();
			for (int y = 0; y < BLOCK_COUNT_Y; ++y)
				for (int x = 0; x < BLOCK_COUNT_X; ++x) {
					if (!g_pBlock[y][x])continue;
					if (g_Enemy[i].body->collision(g_pBlock[y][x]->body)) {
						eDirection coldir = g_Enemy[i].body->collisionTest(g_pBlock[y][x]->body);
						if (coldir == eLeft) 	pos.x = g_pBlock[y][x]->getPos().x + (BLOCK_SIZE.x + ENEMY_SIZE.x) / 2.f;
						else if (coldir == eUp) 	pos.y = g_pBlock[y][x]->getPos().y - (BLOCK_SIZE.y + ENEMY_SIZE.y) / 2.f;
						else if (coldir == eRight) 	pos.x = g_pBlock[y][x]->getPos().x - (BLOCK_SIZE.x + ENEMY_SIZE.x) / 2.f;
						else if (coldir == eDown) 	pos.y = g_pBlock[y][x]->getPos().y + (BLOCK_SIZE.y + ENEMY_SIZE.y) / 2.f;
						g_Enemy[i].dir = rand() % 4 + 1;
					}
					g_Enemy[i].body->setPos(pos);
				}
		}
		else {

		}
	}
	//下にブロックがないと下におりる
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		if (!g_Enemy[i].type) {
			bool godown = true;
			for (int b = 0; b < BLOCK_COUNT_Y * BLOCK_COUNT_X; ++b) {
				int y = b / BLOCK_COUNT_X;
				int x = b % BLOCK_COUNT_X;
				if (!g_pBlock[y][x])continue;
				if (g_Enemy[i].body->collisionBottom(g_pBlock[y][x]->body)) {
					godown = false;
					break;
				}
			}
			if (godown) g_Enemy[i].dir = 4;
		}
	}
	//ブロック一番下の座標を求めて
	//敵がその高さより低くなったら移動パターン変える
	float lowest = WINDOW_TOP;
	for (int b = 0; b < BLOCK_COUNT_Y * BLOCK_COUNT_X; ++b) {
		int y = b / BLOCK_COUNT_X;
		int x = b % BLOCK_COUNT_X;
		if (!g_pBlock[y][x])continue;
		if (lowest > g_pBlock[y][x]->getPos().y - BLOCK_SIZE.y * 2.f)
			lowest = g_pBlock[y][x]->getPos().y - BLOCK_SIZE.y * 2.f;
	}
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		if (g_Enemy[i].body->getPos().y < lowest)
			g_Enemy[i].type = true;
	}

	//境界線//------------------------------
	//境界線に当たった時乱数で次の方向を決める
	for (int i = 0; i < 3; ++i) {
		bool hit = false;
		if (!g_Enemy[i].body) continue;
		XMFLOAT4 pos = g_Enemy[i].body->getPos();
		//int dir = g_Enemy[i].dir;
		if (pos.x < BORDER[0] + ENEMY_SIZE.x / 2.f) {
			pos.x = BORDER[0] + ENEMY_SIZE.x / 2.f;
			hit = true;
		}
		if (pos.y > BORDER[1] - ENEMY_SIZE.y / 2.f && g_Enemy[i].dir != 4) {
			pos.y = BORDER[1] - ENEMY_SIZE.y / 2.f;
			hit = true;
		}
		if (pos.x > BORDER[2] - ENEMY_SIZE.x / 2.f) {
			pos.x = BORDER[2] - ENEMY_SIZE.x / 2.f;
			hit = true;
		}
		if (hit == true) {
			if (!g_Enemy[i].type) g_Enemy[i].dir = rand() % 4 + 1;
			else g_Enemy[i].dir += 180;

		}
		g_Enemy[i].body->setPos(pos);
	}
	//画面↓から出ると破棄
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		if (g_Enemy[i].body->getPos().y < BORDER[3]) {
			disposeSprite(g_Enemy[i].body);
			g_Enemy[i].body = NULL;
		}
	}
	//_____________________________________________
	//ボールに当たった処理
	//_____________________________________________
	for (int b = 0; b < BALL_COUNT; ++b) {
		if (!g_pBall[b] || !g_pBall[b]->body)continue;
		for (int i = 0; i < 3; ++i) {
			if (!g_Enemy[i].body) continue;
			if (g_Enemy[i].body->collision(g_pBall[b]->body)) {
				int angle = 0;
				do { angle = rand() % 34 + 1; } while (angle == 18);
				g_pBall[b]->setAngle(float(angle * 10));
				g_Enemy[i].dead = true;
			}
		}
	}
	//_____________________________________________
	//VausとLaserとの処理
	//_____________________________________________
	if (g_pVaus) {
		for (int i = 0; i < 3; ++i) {
			if (!g_Enemy[i].body) continue;
			if (g_pVaus->body) {
				if (g_pVaus->body->collision(g_Enemy[i].body))
					g_Enemy[i].dead = true;
			}
			for (int l = 0; l < 2; ++l) {
				if (!g_pVaus->laser[l])continue;
				if (g_Enemy[i].body->collision(g_pVaus->laser[l])) {
					g_Enemy[i].dead = true;
					disposeSprite(g_pVaus->laser[l]);
					g_pVaus->laser[l] = NULL;
				}
			}
		}
	}
	//_____________________________________________
	//死亡の処理
	//_____________________________________________
	//死亡だと画像消して、スコアを１００加算
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		if (g_Enemy[i].dead) {
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			//音声
			setSound(Enemy_Explode);
			//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
			//敵今の位置を取得し、その位置に爆発エフェクトを起こす
			XMFLOAT4 pos = g_Enemy[i].body->getPos();
			disposeSprite(g_Enemy[i].body);
			g_Enemy[i].body = NULL;
			g_iScore += 100;
			g_Enemy[i].death = createSprite(Tex_Enemy_Explosion, ENEMY_SIZE.x, ENEMY_SIZE.y);
			if (g_iRound % 4 == 3)g_Enemy[i].death->setAnimationRange(6, 11);
			else g_Enemy[i].death->setAnimationRange(0, 5);
			g_Enemy[i].death->setPos(pos);
			g_Enemy[i].animindex = 0;
		}
	}
	//_____________________________________________
	//アニメーション
	//_____________________________________________
	//生きている時のアニメーション
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].body) continue;
		g_Enemy[i].counter++;
		if (g_Enemy[i].counter > ENEMY_ANIM) {
			g_Enemy[i].counter = 0;
			g_Enemy[i].body->stepAnimation();
		}
	}
	//死亡アニメーション
	for (int i = 0; i < 3; ++i) {
		if (!g_Enemy[i].death) continue;
		g_Enemy[i].counter++;
		if (g_Enemy[i].counter > EXPLODE_ANIM) {
			g_Enemy[i].animindex++;
			g_Enemy[i].counter = 0;
			g_Enemy[i].death->stepAnimation();
		}
		if (g_Enemy[i].animindex > 5) {
			g_Enemy[i].animindex = 0;
			if (g_Enemy[i].death) {
				disposeSprite(g_Enemy[i].death);
				g_Enemy[i].death = NULL;
			}
		}
	}
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//スコアの処理
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	if (g_iHiScore < g_iScore) {
		g_iHiScore = g_iScore;
	}
	//スコアの調整
	if (g_iScore < 0) {
		g_iScore = 0;
	}
	if (g_iScore > 999999) {
		g_iScore = 999999;
	}
	ShowScore(g_pScore, g_iScore, g_iDigit, SCORE_POS, FONT_SIZE);
	ShowScore(g_pHiScore, g_iHiScore, g_iHiDigit, HISCORE_POS, FONT_SIZE);

	//______________________________________________
	//音声を流す
	if (g_pSound)playSound(g_pSound);
	//______________________________________________
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//描画
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//Header
	procHeader();
	//Vaus
	if (g_pVaus) {
		if (g_pVaus->body) renderSprite(g_pVaus->body);
		if (g_pVaus->shadow) renderSprite(g_pVaus->shadow);
		for (int i = 0; i < 2; ++i)
			if (g_pVaus->laser[i]) renderSprite(g_pVaus->laser[i]);
	}
	//HP
	for (int i = 0; i < MAXHP; ++i) {
		if (g_pHp[i]) renderSprite(g_pHp[i]);
	}
	//Ball
	for (int i = 0; i < BALL_COUNT; ++i)
		if (g_pBall[i]) {
			if (g_pBall[i]->body) renderSprite(g_pBall[i]->body);
			if (g_pBall[i]->shadow) renderSprite(g_pBall[i]->shadow);
		}
	//ステージ情報
	if (g_pRound[0])renderFont(g_pRound[0], "ROUND");
	if (g_pRound[1])renderFont(g_pRound[1], g_iRound);
	if (g_pRound[2])renderFont(g_pRound[2], "READY");

	//Item
	if (g_Item.body) renderSprite(g_Item.body);
	//Enemy
	for (int i = 0; i < 3; ++i) {
		if (g_Enemy[i].body)renderSprite(g_Enemy[i].body);
		if (g_Enemy[i].death)renderSprite(g_Enemy[i].death);
	}
	//BOSS
	if (DOH) {
		for (int i = 0; i < 5; ++i)
			if (DOH->laser[i])renderSprite(DOH->laser[i]);
		if (DOH->body)renderSprite(DOH->body);
		if (DOH->death)
			renderSprite(DOH->death);
	}
	//Block
	for (int y = 0; y < BLOCK_COUNT_Y; ++y)
		for (int x = 0; x < BLOCK_COUNT_X; ++x) if (g_pBlock[y][x]) {
			if (g_pBlock[y][x]->body) renderSprite(g_pBlock[y][x]->body);
		}
	for (int y = 0; y < BLOCK_COUNT_Y; ++y)
		for (int x = 0; x < BLOCK_COUNT_X; ++x) if (g_pBlock[y][x]) {
			if (g_pBlock[y][x]->shadow) renderSprite(g_pBlock[y][x]->shadow);
		}
	//Exit
	for (int i = 0; i < 2; ++i)
		if (g_pExit[i]) renderSprite(g_pExit[i]);
	//Break
	if (g_pBreak) renderSprite(g_pBreak);
	//Stage
	if (g_pStage) renderSprite(g_pStage);
}

/* 関数名　	：procPlayEnd()
 * 処理内容　：ゲーム画面の開始時に行う処理
 * 引数　　　：なし
 * 戻り値　　：なし
 */
void COriginalGameApp::procPlayEnd() {
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//次のフェーズを判断する
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//新しくステージを作るかを判断
	//Vaus死んでいるなら残機を減らして再開
	//残機もうない場合ゲームオーバーへ
	if (!g_pVaus) {
		g_iVausHp--;
		g_bNewRound = false;
	}
	else {
		g_iRound++;
		g_bNewRound = true;
	}

	if (g_iRound > MAX_ROUND) g_NextStatusFromGame = eEnding;
	else if (g_iVausHp >= 0)  g_NextStatusFromGame = ePlaying;
	else				      g_NextStatusFromGame = eEnding;

	//次はインゲームではないと
	//スコアを保存して、ゲームを初期化
	if (g_NextStatusFromGame != ePlaying) {
		Record temp;
		g_bNewRecord = false;
		temp.score = g_iScore;
		temp.name = "";
		temp.round = g_iRound;
		for (int i = 0; i < 5; ++i) {
			if (g_sRecord[i].score < temp.score) {
				int a = g_sRecord[i].score;
				int b = g_sRecord[i].round;
				string c = g_sRecord[i].name;
				g_sRecord[i].score = temp.score;
				g_sRecord[i].round = temp.round;
				g_sRecord[i].name = temp.name;
				temp.score = a;
				temp.round = b;
				temp.name = c;
				g_bNewRecord = true;
			}
		}
		g_sRecordNow = { g_iScore,g_iDigit,g_iRound,"" };
		g_bNewRound = true;
		g_iRound = 1;
		g_iVausHp = FULLHP;
	}

	if (g_bNewRound) {
		//新しいラウンドに入るならブロックを全部消す
		for (int y = 0; y < BLOCK_COUNT_Y; ++y)
			for (int x = 0; x < BLOCK_COUNT_X; ++x) {
				if (g_pBlock[y][x]) {
					delete g_pBlock[y][x];
					g_pBlock[y][x] = NULL;
				}
			}
	}
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//画面上の画像すべて破棄
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	if (g_pStage) {
		disposeSprite(g_pStage);
		g_pStage = NULL;
	}
	//Vaus
	if (g_pVaus) {
		delete g_pVaus;
		g_pVaus = NULL;
	}
	//Ball
	for (int i = 0; i < BALL_COUNT; ++i)
		if (g_pBall[i]) {
			delete g_pBall[i];
			g_pBall[i] = NULL;
		}
	//Item
	if (g_Item.body) {
		disposeSprite(g_Item.body);
		g_Item.body = NULL;
	}
	//HP
	for (int i = 0; i < MAXHP; ++i) {
		if (g_pHp[i]) {
			disposeSprite(g_pHp[i]);
			g_pHp[i] = NULL;
		}
	}
	//敵
	for (int i = 0; i < 3; ++i) {
		if (g_Enemy[i].body) {
			disposeSprite(g_Enemy[i].body);
			g_Enemy[i].body = NULL;
		}
		if (g_Enemy[i].death) {
			disposeSprite(g_Enemy[i].death);
			g_Enemy[i].death = NULL;
		}
	}
	//Break
	if (g_pBreak) {
		disposeSprite(g_pBreak);
		g_pBreak = NULL;
	}
	//Score
	if (g_pScore != NULL) {
		disposeFont(g_pScore);
		g_pScore = NULL;
	}
	//HiScore
	if (g_pHiScore != NULL) {
		disposeFont(g_pHiScore);
		g_pHiScore = NULL;
	}
	//BOSS
	if (DOH) {
		if (DOH->body)disposeSprite(DOH->body);
		for (int i = 0; i < 5; ++i)
			if (DOH->laser[i])disposeSprite(DOH->laser[i]);
		delete DOH;
		DOH = NULL;
	}
	//Exit
	for (int i = 0; i < 2; ++i)
		if (g_pExit[i]) {
			disposeSprite(g_pExit[i]);
			g_pExit[i] = NULL;
		}
	//ステージ情報
	for (int i = 0; i < 3; ++i)if (g_pRound[i]) {
		disposeFont(g_pRound[i]);
		g_pRound[i] = NULL;
	}
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//音声停止・破棄
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	if (g_pSound) {
		disposeSound(g_pSound);
		g_pSound = NULL;
	}
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	//初期化
	//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
	g_bBreak = false;
}

//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//関数名　	：StageBlock()
//処理内容　：ブロック処理
//引数　　　：なし
//戻り値　　：なし
//作成者　　：蝦名伸太郎
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
void COriginalGameApp::StageBlock() {
	string blocks[BLOCK_COUNT_Y][BLOCK_COUNT_X];
	string line;
	std::ifstream infile;
	if (g_iRound == 1)infile.open(Stage1, ios::in);
	if (g_iRound == 2)infile.open(Stage2, ios::in);
	if (g_iRound == 3)infile.open(Stage3, ios::in);
	if (g_iRound == 4)infile.open(Stage4, ios::in);
	if (g_iRound == 5)infile.open(Stage5, ios::in);
	if (g_iRound == 6)infile.open(Stage6, ios::in);
	if (g_iRound == 7)infile.open(Stage7, ios::in);
	if (g_iRound == 8)infile.open(Stage8, ios::in);
	if (g_iRound == 9)infile.open(Stage9, ios::in);
	if (g_iRound == 10)infile.open(Stage10, ios::in);
	if (g_iRound == 11)infile.open(Stage11, ios::in);
	if (g_iRound == 12)infile.open(Stage12, ios::in);
	if (g_iRound == 13)infile.open(Stage13, ios::in);
	if (g_iRound == 14)infile.open(Stage14, ios::in);
	if (g_iRound == 15)infile.open(Stage15, ios::in);
	if (g_iRound == 16)infile.open(Stage16, ios::in);
	if (g_iRound == 17)infile.open(Stage17, ios::in);
	if (g_iRound == 18)infile.open(Stage18, ios::in);
	if (g_iRound == 19)infile.open(Stage19, ios::in);
	if (g_iRound == 20)infile.open(Stage20, ios::in);
	if (g_iRound == 21)infile.open(Stage21, ios::in);
	if (g_iRound == 22)infile.open(Stage22, ios::in);
	if (g_iRound == 23)infile.open(Stage23, ios::in);
	if (g_iRound == 24)infile.open(Stage24, ios::in);
	if (g_iRound == 25)infile.open(Stage25, ios::in);
	if (g_iRound == 26)infile.open(Stage26, ios::in);
	if (g_iRound == 27)infile.open(Stage27, ios::in);
	if (g_iRound == 28)infile.open(Stage28, ios::in);
	if (g_iRound == 29)infile.open(Stage29, ios::in);
	if (g_iRound == 30)infile.open(Stage30, ios::in);
	if (g_iRound == 31)infile.open(Stage31, ios::in);
	if (g_iRound == 32)infile.open(Stage32, ios::in);

	for (int i = 0; i < BLOCK_COUNT_Y; i++) {
		getline(infile, line);
		istringstream readstr(line);
		for (int j = 0; j < BLOCK_COUNT_X; j++) {
			getline(readstr, blocks[i][j], ',');
		}
	}

	for (int y = 0; y < BLOCK_COUNT_Y; ++y)
		for (int x = 0; x < BLOCK_COUNT_X; ++x) {
			//新しいラウンドなら全てのブロックを再配置
			if (g_bNewRound) {
				if (g_pBlock[y][x]) delete g_pBlock[y][x];
				if (blocks[y][x] == "0") {
					g_pBlock[y][x] = NULL;
					continue;
				}
				g_pBlock[y][x] = new CBlock;
				g_pBlock[y][x]->body = createSprite(Tex_Block, BLOCK_SIZE.x, BLOCK_SIZE.y);
				g_pBlock[y][x]->shadow = createSprite(Tex_Block_Shadow, BLOCK_SIZE.x, BLOCK_SIZE.y);
				g_pBlock[y][x]->setInfo(blocks[y][x], g_iRound);
				g_pBlock[y][x]->setPos((BORDER[0] + BLOCK_SIZE.x / 2.f) + BLOCK_SIZE.x * x, 420.0f - BLOCK_SIZE.y * y);
				if (g_pBlock[y][x]->getIndex() == 0) {
					delete g_pBlock[y][x];
					g_pBlock[y][x] = NULL;
				}
			}
			//新しいラウンドでないと存在するブロックの情報初期化
			else {
				if (g_pBlock[y][x]) g_pBlock[y][x]->setInfo(blocks[y][x], g_iRound);
			}
		}
}