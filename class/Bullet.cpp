#include "Bullet.h"
bool Bullet::operator==(const Bullet& rhs)const
{
	return _ATK == rhs._ATK;
}
Bullet* Bullet::create(int atk, SpriteFrame* bullet)
{
	Bullet* _bullet = new Bullet();
	if (_bullet && _bullet->initWithSpriteFrame(bullet))
	{
		_bullet->_ATK = atk;
		_bullet->_bulletFrame = bullet;
		return _bullet;
	}
	CC_SAFE_DELETE(_bullet);
	return NULL;
}
Bullet* Bullet::clone()
{
	Bullet* bullet = new Bullet();
	bullet->_ATK = this->_ATK;
	bullet->initWithSpriteFrame(this->_bulletFrame);
	bullet->_bulletFrame = this->_bulletFrame;
	return bullet;
}
int Bullet::getATK()
{
	return _ATK;
}