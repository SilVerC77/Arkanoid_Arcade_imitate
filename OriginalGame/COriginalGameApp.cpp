/**
 * @file COriginalGameApp.cpp
 * @brief アプリケーションのエントリ ポイントを定義します。
 */

#include "stdafx.h"
#include "COriginalGameApp.h"


COriginalGameApp::COriginalGameApp()
{
}


COriginalGameApp::~COriginalGameApp()
{
}

/**
 * @fn void COriginalGameApp::initCameraInfo()
 * @brief カメラの設定
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::initCameraInfo()
{
	float z = -(float)(min(WINDOW_HEIGHT, WINDOW_WIDTH) / 2) / tanf(XM_PI / 8.0f);
	m_vEyePt = XMFLOAT3{ 0.0f, 0.0f,		z };	//!< カメラ（視点）位置
	m_vLookatPt = XMFLOAT3{ 0.0f, 0.0f,     0.0f };	//!< 注視位置
	m_vUpVec = XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//!< 上方位置
	m_angle = (FLOAT)XM_PI / 4;					//!< 視野角
	m_aspect = ASPECT;							//!< アスペクト比
	m_near = 0.1f;								//!< 前方クリップ
	m_far = abs(z) + 100.0f;					//!< 後方クリップ
}

void COriginalGameApp::renderSprite(CPicture* object)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
#if 1
		XMFLOAT4 col;
		col.x = 1.0f;
		col.y = 1.0f;
		col.z = 1.0f;
		col.w = 1.0f;

		object->render(matView, matProj, 0Ui64, col);
#else
		object->render(matView, matProj);
#endif
	}
}
void COriginalGameApp::renderSprite(CPicture* object, XMFLOAT3 color)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		XMFLOAT4 col;
		col.x = color.x;
		col.y = color.y;
		col.z = color.z;

		object->render(matView, matProj, 0Ui64, col);
	}
}
void COriginalGameApp::renderSprite(CPicture* object, XMFLOAT4 color)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		XMFLOAT4 col;
		col.x = color.x;
		col.y = color.y;
		col.z = color.z;
		col.w = color.w;

		object->render(matView, matProj, 0Ui64, col);
	}
}
void COriginalGameApp::disposeSprite(CPicture* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

void COriginalGameApp::renderFont(CFont* object, int num_)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		object->render(matView, matProj, num_);
	}
}
void COriginalGameApp::disposeFont(CFont* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

/**
 * @fn bool COriginalGameApp::createSpaceship(void)
 * @brief スプライトの生成
 * @param	無し
 * @return	成功・失敗
 */
bool COriginalGameApp::createSpaceship(void)
{
#if 0
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL,
			{ 0.0f, -200.0f, 0.0f, 0.0f },	//!< スプライトの位置
			kCharSpriteSize,				//!< スプライトのサイズ
			kTexelPlayerBulletIndex);		//!< テクセルの配列のインデックス（アニメーションのため）
	}
	m_pPlayer->setHP(kMaxHP);                           // <!
	m_pPlayer->setDamage(FALSE);                        // <!
	m_pPlayer->setActive(TRUE);                         // <!
	m_pPlayer->setPos({ 0.0f, -200.0f, 0.0f, 0.0f });   // <!
	m_pPlayer->setState(eMoving);
	m_pPlayer->setScale(1.0f);
	m_pPlayer->resetExplosion();                        // <!
	m_pPlayer->resetAllBullets();                       // <!
	m_pPlayer->setAngleZ(0.0f);                         // <!

	XMFLOAT4 ePos[] = {
		{-120.0f + 0 + 48 * 0, 200.0f, 0.0f, 0.0f},
		{-120.0f + 0 + 48 * 1, 200.0f, 0.0f, 0.0f},
		{-120.0f + 0 + 48 * 2, 200.0f, 0.0f, 0.0f},
		{-120.0f + 0 + 48 * 3, 200.0f, 0.0f, 0.0f},
		{-120.0f + 0 + 48 * 4, 200.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 0, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 1, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 2, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 3, 160.0f, 0.0f, 0.0f}
	};
	for (size_t i = 0; i < _countof(m_pEnemies); i++)
	{
		if (m_pEnemies[i] == NULL)
		{
			m_pEnemies[i] = CEnemy::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL,
				ePos[i],                    //!< スプライトの位置
				kCharSpriteSize,			//!< スプライトのサイズ
				kTexelEnemyBulletIndex);	//!< テクセルの配列のインデックス（アニメーションのため）
		}
		m_pEnemies[i]->setHP(kMaxHP);       // !<
		m_pEnemies[i]->setDamage(FALSE);    // <!
		m_pEnemies[i]->setActive(TRUE);     // !<
		m_pEnemies[i]->setPos(ePos[i]);     // !<
		m_pEnemies[i]->setState(eMoving);
		m_pEnemies[i]->setScale(1.0f);
		m_pEnemies[i]->resetExplosion();     //!< 
		m_pEnemies[i]->resetAllBullets();    //!< 
	}
	m_pPlayerTex = CTexture::create(m_pDevice, Tex_Spaceship);	//!< テクセル
	m_pEnemyTex = CTexture::create(m_pDevice, Tex_Spaceship);	//!< テクセル
#endif
	return true;
}

/**
 * @fn void COriginalGameApp::doOpenning()
 * @brief オープニング
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::doOpenning()
{
	procTitle();
}

/**
 * @fn void COriginalGameApp::doPlaying()
 * @brief プレー中
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::doPlaying()
{
#if 0
	// 【ステップ4】
	/**
	* プレイヤーのアニメーション
	*/
	m_frameCounter++;
	m_frameCounter = m_frameCounter > 99 ? 0 : m_frameCounter;

	m_pPlayer->stepAnimation(m_frameCounter % kTexelIntervalFrames == 0);

	m_pBack->scroll(-1.0f);
	m_pMiddle->scroll(-2.0f);
	m_pFront->scroll(-3.0f);
	/**
	* プレーヤーの制御
	*/
	if (m_pDirectInput->isKeyPressed(DIK_LEFT))		m_pPlayer->offsetPosInNormalRange({ -2.0f,  0.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_RIGHT))	m_pPlayer->offsetPosInNormalRange({ 2.0f,  0.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_UP))		m_pPlayer->offsetPosInNormalRange({ 0.0f,  2.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_DOWN))		m_pPlayer->offsetPosInNormalRange({ 0.0f, -2.0f, 0.0f, 0.0f });

	if (m_pDirectInput->isKeyPressed(DIK_V))		m_pPlayer->addAngleZ(-0.5);
	if (m_pDirectInput->isKeyPressed(DIK_N))		m_pPlayer->addAngleZ(0.5);
	if (m_pDirectInput->isPressedOnce(DIK_B))		m_pPlayer->shot();

	if (m_pDirectInput->isLeftButtonClicked())	    m_pPlayer->shot();

	/**
	* 【ステップ5】敵の操作
	*/
	auto    callback = [&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
		if (enemy_->getActive() == TRUE)
		{
			prepareFrame(enemy_, index_);
		}
		return TRUE; //!< 列挙を続行
	};
	if (isActiveEnemies() == FALSE)
	{
		m_gameStatus = eGameClear;
	}

	/**
	* プレーヤーの爆発が完了したらゲームオーバー.
	*/
	if (m_pPlayer->isExplosionCompleted())
	{
		m_gameStatus = eGameOver;
	}
#else
	procGame();

#endif
}


/**
 * @fn void COriginalGameApp::doGameClear()
 * @brief ゲームクリア
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::doGameClear()
{
	procClear();
}

/**
 * @fn void COriginalGameApp::doGameOver()
 * @brief ゲームオーバー
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::doGameOver()
{
	procOver();
}

/**
 * @fn void COriginalGameApp::doEnding()
 * @brief エンディング
 * @param	無し
 * @return	無し
 */
void COriginalGameApp::doEnding()
{
	procResult();
}

/**
 * @fn void COriginalGameApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
 * @brief レンダー
 * @param	matView_	ビュー行列
 * @param	matProj_	プロジェクション行列
 * @return				無し
 */
void COriginalGameApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
#if 0
	auto setUpEnemyTex = [&](ID3D11DeviceContext* pDeviceContext_) -> void {
		m_pEnemyTex->setup(pDeviceContext_);
	};
	auto callback = [&](CEnemy* enemy_, size_t index_) -> BOOL {
		enemy_->render(matView_, matProj_, setUpEnemyTex);
		return TRUE; //!< 列挙を続行	
	};
	auto setUpPlayerTex = [&](ID3D11DeviceContext* pDeviceContext_) -> void {
		m_pPlayerTex->setup(pDeviceContext_);
	};

	switch (m_gameStatus)
	{
	case eOpening:
		m_pTitle->render(matView_, matProj_);
		break;
	case ePlaying:
		// 引数描画する順番と結果を確認すること
		m_pPlayer->render(matView_, matProj_, setUpPlayerTex);

		m_pFront->render(matView_, matProj_);
		m_pMiddle->render(matView_, matProj_);
		m_pBack->render(matView_, matProj_);
		break;
	case eGameOver:
		m_pGameOver->render(matView_, matProj_);
		break;
	default:
		break;
	}
#endif
}


/**
* @fn void COriginalGameApp::release()
* @brief 解放
* @param	無し
* @return	無し
*/
void COriginalGameApp::release()
{
	super::release();
}
//_______________________________________________________________________________________________________
// 許弘毅　追加
//_______________________________________________________________________________________________________
void COriginalGameApp::procHeader()
{
	if (g_pHeader) {
		static int header_cnt = 0;
		header_cnt++;
		if (header_cnt > 20) {
			header_cnt = 0;
			g_pHeader->stepAnimation();
		}
		renderSprite(g_pHeader);
	}
}

void COriginalGameApp::renderFont(CFont* object, string _str) {
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();
	if (object != NULL)
	{
		object->render(matView, matProj, _str);
	}
}

CPicture* COriginalGameApp::createSprite(LPCWSTR path_, const XMFLOAT2 _size,const XMFLOAT2 _pos){
	CPicture* object = createSprite(path_, _size.x, _size.y);
	object->setPos(_pos);
	return object;
}

void COriginalGameApp::setSound(const char* _sfx) {
	if (g_pSound) disposeSound(g_pSound);
	g_pSound = createSound(_sfx);
}


float COriginalGameApp::DegtoRad(float _degree) {
	const double PI = 3.14159265359;
	double radian = (double)_degree * PI / 180.0;
	return (float)radian;
}
float COriginalGameApp::calLength(XMFLOAT2 _a, XMFLOAT2 _b) {
	float x = _a.x - _b.x;
	float y = _a.y - _b.y;
	return sqrt(x * x + y * y);
}
float COriginalGameApp::calLength(XMFLOAT4 _a, XMFLOAT4 _b)
{
	float x = _a.x - _b.x;
	float y = _a.y - _b.y;
	return sqrt(x * x + y * y);
}
void COriginalGameApp::drawRect(const string _color, const XMFLOAT2 _pos, const XMFLOAT2 _size) {
	CPicture* rect = NULL;
	if (_color == "blue") rect = createSprite(Tex_Blue, _size.x, _size.y);
	else  rect = createSprite(Tex_Green, _size.x, _size.y);
	rect->setPos(_pos);
	renderSprite(rect);
	disposeSprite(rect);
}
void COriginalGameApp::drawLine(const string _color, XMFLOAT4 _start, XMFLOAT4 _end) {
	float length = calLength(_start, _end);
	float rad = atan2(_end.y - _start.y, _end.x - _start.x);
	float degree = rad / PI * 180.f;
	CPicture* line = NULL;
	if (_color == "blue") line = createSprite(Tex_Blue, length, 2.f);
	else  line = createSprite(Tex_Green, length, 2.f);
	XMFLOAT2 offset;
	offset.x = (_end.x + _start.x) / 2.f;
	offset.y = (_end.y + _start.y) / 2.f;
	line->setAngleZ(degree);
	line->setPos(offset.x, offset.y);
	renderSprite(line);
	disposeSprite(line);
}
void COriginalGameApp::drawLine(const string _color, XMFLOAT4 _start, float _length, float _degree) {
	CPicture* line = NULL;
	if (_color == "blue") line = createSprite(Tex_Blue, _length, 2.f);
	else  line = createSprite(Tex_Green, _length, 2.f);
	float rad = DegtoRad(_degree);
	float x = _length * cos(rad);
	float y = _length * sin(rad);
	line->setPos(_start.x + x / 2.f, _start.y + y / 2.f);
	line->setAngleZ(_degree);
	renderSprite(line);
	disposeSprite(line);
}
void COriginalGameApp::ShowScore(CFont*& _font, const int& _score, int& _digit, const XMFLOAT2 _pos, const XMFLOAT2 _size) {
	int number = _score;
	int digit = 0;
	while (number > 0) {
		number /= 10;
		digit++;
	}
	if (digit < 2)digit = 2;
	if (_digit != digit) {
		_digit = digit;
		if (_font) {
			disposeFont(_font);
			_font = NULL;
		}
	}
	if (!_font)	_font = createFont(Tex_Number, _digit, _size.x, _size.y);
	_font->setPos(_pos.x - (_size.x * _digit), _pos.y);

	if (_font) renderFont(_font, _score);
}
//＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿_______________________________＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿

//_______________________________________________________________________________________________________
// 作成者：細田弥卯（2021_09_29）
//_______________________________________________________________________________________________________
/**
* @fn void COriginalGameApp::release()
* @brief サウンドの作成
* @param	filePath_	wavファイルへのパス
* @param	loop_	音声をループさせるなら、true
* @return	作成した音声を管理するポインタ
*/
CSound* COriginalGameApp::createSound(const char* filePath_, const bool loop_)
{
	CSound* object = NULL;

	// wavファイルの作成
	if (!object)
	{
		object = CSound::Create(m_pXaudio2, filePath_, loop_);
	}

	return object;
}

/**
* @fn void COriginalGameApp::release()
* @brief サウンドの作成
* @param	filePath_	wavファイルへのパス
* @param	loop_	音声をループさせるなら、true
* @return	作成した音声を管理するポインタ
*/
void COriginalGameApp::playSound(CSound* const objects)
{
	// 作成されていなければ戻す
	if (!objects) { return; }
	objects->PlaySourcevoice();
}

/**
* @fn void COriginalGameApp::release()
* @brief サウンドの作成
* @param	filePath_	wavファイルへのパス
* @param	loop_	音声をループさせるなら、true
* @return	作成した音声を管理するポインタ
*/
void COriginalGameApp::disposeSound(CSound* const objects)
{
	// 作成されていなければ戻す
	if (!objects) { return; }
	objects->DeleteSourcevoice();
	delete objects;
}