/* Vaus
 * 作成者 ：20cu0215　許弘毅、
 * 作成日 ：2021 / 09 / 29
 */
#include "CVaus.h"

 //初期化
CVaus::CVaus() :
	ePower(eCatch),
	eOldPower(ePower),
	fSpeed(20.f),
	iCounter(0),
	bStart(true)
{
	//弾画像初期化
	for (int i = 0; i < 2; ++i) {
		laser[i] = NULL;
	}
}

//デストラクタ
CVaus::~CVaus() {
	//解放しておく
	if (body) body->release();
	if (shadow)	shadow->release();
	for (int i = 0; i < 2; ++i)
		if (laser[i]) laser[i]->release();
}

//移動
void CVaus::move(BOOL _left, BOOL _right) {
	if (!body) return;
	if (_left || _right) {
		XMFLOAT4 pos = body->getPos();
		//入力によって位置を変える
		if (_right)	pos.x += fSpeed;
		if (_left)	pos.x -= fSpeed;
		//計算した位置の結果を反映
		setPos(pos);
	}
}

void CVaus::move(float _BallPos) {
	XMFLOAT4 pos = body->getPos();
	static float x = 0.f;
	static int random = 10;
	x += 0.1f;
	if (x > 2.f * PI) {
		x = 0.f;
		random = rand() % 20;
	}
	pos.x = _BallPos + float(random) * sin(x);
	setPos(pos);
}

void CVaus::border(float _left, float _right, bool _break) {
	if (!body) return;
	XMFLOAT4 pos = body->getPos();
	if (pos.x < _left + getSize().x / 2.f)
		pos.x = _left + getSize().x / 2.f;
	if (!_break)
		if (pos.x > _right - getSize().x / 2.f)
			pos.x = _right - getSize().x / 2.f;
	setPos(pos);
}

void CVaus::releaseBall(BOOL _press) {
	//前は解放ならキャッチに戻す
	if (ePower == eRelease) ePower = eCatch;
	if (ePower == eCatch && _press) {
		//入場の場合は発射したらパワーを消す
		if (bStart) {
			ePower = eNoPower;
			bStart = false;
		}
		else {
			ePower = eRelease;
		}
	}
}

bool CVaus::canShoot(const float _speed, const int _rate, BOOL _press) {
	for (int i = 0; i < 2; ++i)
		if (laser[i]) {
			XMFLOAT4 pos = laser[i]->getPos();
			pos.y += _speed;
			laser[i]->setPos(pos);
		}

	iCounter++;
	if (iCounter > _rate)iCounter = _rate;
	if (ePower != eLaser || !_press) {
		return false;
	}
	if (iCounter % _rate == 0) {
		iCounter = 0;
		return true;
	}
	else
		return false;
}

bool CVaus::powerChange() {
	if (ePower == eDisruption ||
		ePower == eSpeedDown ||
		ePower == ePlayerExtend ||
		ePower == eBreak)
		ePower = eNoPower;
	if (ePower == eOldPower) {
		return false;
	}
	else {
		eOldPower = ePower;
		return true;
	}
}

void CVaus::dispose() {
	if (body) {
		body->release();
		body = NULL;
	}
	if (shadow) {
		shadow->release();
		shadow = NULL;
	}
}

//void CVaus::setPos() {
//	if (body) body->setPos(f2Pos);
//	if (shadow) shadow->setPos(f2Pos.x + f2Size.x / 8.f, f2Pos.y - f2Size.y / 2.f);
//}
void CVaus::setPos(XMFLOAT2 _pos) {
	XMFLOAT2 size = body->getSize();
	if (body) body->setPos(_pos);
	if (shadow) shadow->setPos(_pos.x + size.x / 8.f, _pos.y - size.y / 2.f);
}

void CVaus::setPos(XMFLOAT4 _pos) {
	XMFLOAT2 pos = { _pos.x,_pos.y };
	setPos(pos);
}

void CVaus::setPos(float _posx, float _posy) {
	XMFLOAT2 pos = { _posx,_posy };
	setPos(pos);
}

//________________________________________________________________
//Ball
//________________________________________________________________
//コンストラクタ
//初期化
CBall::CBall(float _degree, float _speed, bool _fly) :
	f2OldPos({ 0.f,WINDOW_BOTTOM }),
	f2Dir({ 1.f,1.f }),
	fSpeed(_speed),
	fRad(_degree / 180.f * PI),
	fOffset(0.f),
	bfly(_fly),
	bDead(false)
{}

//デストラクタ
CBall::~CBall() {
	//解放しておく
	if (body) body->release();
	if (shadow) shadow->release();
}

void CBall::move(const float _limit) {
	if (!body) return;
	if (!bfly) return;
	//古い位置を記録
	f2OldPos = { getPos().x,getPos().y };
	XMFLOAT4 pos = getPos();
	//速度制限
	if (fSpeed > _limit) fSpeed = _limit;
	pos.x += fSpeed * cos(fRad) * f2Dir.x;
	pos.y += fSpeed * sin(fRad) * f2Dir.y;
	setPos(pos);
}

void CBall::setPos(XMFLOAT4 _pos) {
	setPos(_pos.x, _pos.y);
}
void CBall::setPos(float _x, float _y) {
	//f2OldPos = { getPos().x,getPos().y };
	if (body) body->setPos(_x, _y);
	if (shadow) shadow->setPos(_x + getSize().x / 5.f * 4.f, _y - getSize().y);
}

void CBall::setPos(CVaus* _vaus) {
	if (!_vaus) return;
	XMFLOAT4 pos = _vaus->getPos();
	pos.y += (_vaus->getSize().y + getSize().y) / 2.f;
	pos.x += fOffset;
	setPos(pos);
}

float CBall::getAngle(const char _unit)const {
	float x = getPos().x - f2OldPos.x;
	float y = getPos().y - f2OldPos.y;
	float rad = (float)atan2(y, x);
	if (_unit == 'd')
		return rad / PI * 180.f;
	return rad;
}

void CBall::border(float _left, float _top, float _right, float _bottom) {
	if (!body) return;
	XMFLOAT4 pos = body->getPos();
	XMFLOAT2 size = body->getSize();
	if (pos.x < _left + size.x / 2.f) {
		pos.x = _left + size.x / 2.f;
		pos.y -= (f2OldPos.x - pos.x) * tan(getAngle('r'));
		bounce(eLeft);
	}
	else if (pos.x > _right - size.x / 2.f) {
		pos.x = _right - size.x / 2.f;
		pos.y -= (f2OldPos.x - pos.x) * tan(getAngle('r'));
		bounce(eRight);
	}
	if (pos.y > _top - size.y / 2.f) {
		pos.y = _top - size.y / 2.f;
		pos.x -= (pos.y - f2OldPos.y) / tan(getAngle('r'));
		bounce(eUp);
	}
	else if (_bottom < WINDOW_TOP)
		if (pos.y < _bottom + size.y / 2.f) {
			pos.y = _bottom + size.y / 2.f;
			bounce(eDown);
		}
	setPos(pos);
}

void CBall::setAngle(float _degree) {
	//調整
	_degree = (float)((int)_degree % 360);
	//ラジアンに変換
	fRad = _degree / 180.f * PI;
	//方向初期化
	f2Dir = { 1.f,1.f };
}

bool CBall::collisionRay(CPicture* _target, XMFLOAT2& _contact, float& hit_near, eDirection& _direction) {
	//ボール移動の軌跡に当たったかを判定
	//当たり判定の対象の各軸の値
	//ボール自体のサイズの半分をターゲットに加算
	float t_left = _target->getPos().x - (_target->getSize().x + getSize().x) / 2.f;
	float t_right = _target->getPos().x + (_target->getSize().x + getSize().x) / 2.f;
	float t_top = _target->getPos().y + (_target->getSize().y + getSize().y) / 2.f;
	float t_bottom = _target->getPos().y - (_target->getSize().y + getSize().y) / 2.f;
	//前のフレームのボールの位置からレイを飛ばして、レイと各軸との距離を求める
	XMFLOAT2 dir = { getPos().x - f2OldPos.x,getPos().y - f2OldPos.y };
	XMFLOAT2 c_near;
	c_near.x = (t_left - f2OldPos.x) / dir.x;
	c_near.y = (t_bottom - f2OldPos.y) / dir.y;
	XMFLOAT2 c_far;
	c_far.x = (t_right - f2OldPos.x) / dir.x;
	c_far.y = (t_top - f2OldPos.y) / dir.y;

	if (isnan(c_far.y) || isnan(c_far.x))return false;
	if (isnan(c_near.y) || isnan(c_near.x))return false;

	if (c_near.x > c_far.x) swap(c_near.x, c_far.x);
	if (c_near.y > c_far.y) swap(c_near.y, c_far.y);

	if (c_near.x > c_far.y || c_near.y > c_far.x)return false;

	hit_near = max(c_near.x, c_near.y);
	float hit_far = min(c_far.x, c_far.y);

	if (hit_near < 0.f || hit_near>1.f)return false;

	//移動距離のどこで当たったか計算
	_contact.x = f2OldPos.x + hit_near * dir.x;
	_contact.y = f2OldPos.y + hit_near * dir.y;

	/*if (c_near.x == c_near.y) _direction = eCorner;
	else */
	if (c_near.x > c_near.y)
		if (dir.x < 0.f) _direction = eLeft;
		else			 _direction = eRight;
	else
		if (dir.y < 0.f) _direction = eDown;
		else			 _direction = eUp;
	return true;
}

void CBall::bounce(eDirection _dir, CPicture* _target) {
	if (!body)return;
	if (_dir == eLeft || _dir == eRight) f2Dir.x *= -1;
	else if (_dir == eUp || _dir == eDown)    f2Dir.y *= -1;
	//当たった時速度を増やす
	fSpeed += 0.5f;
	if (!_target)return;
	XMFLOAT2 pos = { getPos().x,getPos().y };
	XMFLOAT2 push = {
		(getSize().x + _target->getSize().x) / 2.f,		//X
		(getSize().y + _target->getSize().y) / 2.f };	//Y
	if (_dir == eLeft)  pos.x = _target->getPos().x + push.x;
	else if (_dir == eRight) pos.x = _target->getPos().x - push.x;
	else if (_dir == eUp)    pos.y = _target->getPos().y - push.y;
	else if (_dir == eDown)  pos.y = _target->getPos().y + push.y;
	setPos(pos.x, pos.y);
}

void CBall::bounce(CVaus* _vaus) {
	if (!body || !_vaus)return;
	eDirection targetdir;
	XMFLOAT2 pos;
	float hit_near = 1.f;
	if (!bfly) {
		if (_vaus->getPower() == eCatch)
			setPos(_vaus);
		else
			bfly = true;
		return;//-------------------------------------------------------要確認
	}
	//else if (!body->collision(_vaus->body))return;
	else if (!collisionRay(_vaus->body, pos, hit_near, targetdir)) return;
	//当たった時の処理ーーーーーーーーーー
	//ずれた距離を管理
	fOffset = getPos().x - _vaus->getPos().x;
	setPos(_vaus);
	if (_vaus->getPower() == eCatch)
		bfly = false;
	else {
		if (fOffset > _vaus->getSize().x / 2.f)
			fOffset = _vaus->getSize().x / 2.f;
		float dir = 1.f;		//方向を管理
		if (fOffset < 0.f) {
			fOffset *= -1;		//絶対値
			dir = -1.f;
		}
		//ずれた距離によって反射の角度変える
		float area = _vaus->getSize().x / 6.f;
		if (fOffset < area)			  setAngle(60.f);
		else if (fOffset < area * 2.f)setAngle(30.f);
		else						  setAngle(15.f);
		f2Dir.x = dir;		//方向を反映
	}
}

void CBall::disposeBall() {
	if (body) {
		body->release();
		body = NULL;
	}
	if (shadow) {
		shadow->release();
		shadow = NULL;
	}
}


