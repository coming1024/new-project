#include "equipment.h"
bool equipment::operator==(const equipment& rhs)const
{
	if (_ATK == rhs._ATK && _speed == rhs._speed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

equipment* equipment::create(int ATK, int speed, int type, bool isContinue, SpriteFrameCache* cache, char* s, Bullet* bullet)
{
	equipment* equip = new equipment();
	if (equip && equip->initWithSpriteFrame(cache->getSpriteFrameByName(s)))
	{
		equip->_ATK = ATK;
		equip->_speed = speed;
		equip->_type = type;
		equip->_bullet = bullet;
		equip->_isContinue = isContinue;
		return equip;
	}
	CC_SAFE_DELETE(equip);
	return NULL;
}
equipment* equipment::create(int ATK, int speed, int type, bool isContinue, SpriteFrameCache* cache, char* s, Vector<SpriteFrame*> vector_frame_jzxfw, int w, int h)
{
	equipment* equip = new equipment();
	equip->initWithSpriteFrame(cache->getSpriteFrameByName(s));
	equip->_width = w;
	equip->_hight = h;
	equip->_ATK = ATK;
	equip->_speed = speed;
	equip->_type = type;
	equip->_isContinue = isContinue;
	equip->vector_frame = vector_frame_jzxfw;
	return equip;
}

int equipment::getWidth()
{
	return _width;
}
int equipment::getHight()
{
	return _hight;
}
bool equipment::getType()
{
	return this->_type;
}
int equipment::getSpeed()
{
	return this->_speed;
}
int equipment::getATK()
{
	return this->_ATK;
}
bool equipment::getIsContinue()
{
	return _isContinue;
}