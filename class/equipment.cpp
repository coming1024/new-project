#include "equipment.h"
bool equipment::operator==(const equipment& rhs)const
{
	if (_ATK == rhs._ATK && _speed == rhs._speed )
	{
		return true;
	}
	else
	{
		return false;
	}
}

equipment* equipment::create(int ATK, int speed, int type, SpriteFrameCache* cache, char* s,SpriteFrame* bullet)
{
	equipment* equip = new equipment();
	equip->initWithSpriteFrame(cache->getSpriteFrameByName(s));
	equip->_ATK = ATK;
	equip->_speed = speed;
	equip->_type = type;
	equip->_bullet = bullet;
	return equip;
}
equipment* equipment::create(int ATK, int speed, int type, SpriteFrameCache* cache, char* s, Vector<SpriteFrame*> vector_frame_jzxfw)
{
	equipment* equip = new equipment();
	equip->initWithSpriteFrame(cache->getSpriteFrameByName(s));
	equip->_ATK = ATK;
	equip->_speed = speed;
	equip->_type = type;
	equip->vector_frame = vector_frame_jzxfw;
	return equip;
}