#include "hero.h"
USING_NS_CC;
hero* hero::create(SpriteFrameCache* cache, char* s)
{
	hero* player = new hero();
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	if (player && player->initWithSpriteFrame(cache->spriteFrameByName(s)))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}
bool hero::commonAttack(Touch* pTouch, Event* pEvent)
{
	return true;
}
bool hero::stopcommonAttack(Touch* pTouch, Event* pEvent)
{
	return true;
}
bool hero::heroMove(EventKeyboard::KeyCode keycode, Event* event)
{
	return true;
}
bool hero::heroStopMove(EventKeyboard::KeyCode keycode, Event* event)
{
	return true;
}
bool hero::swithWeapon(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_J)
	{
		auto fadeout = FadeOut::create(0.2f);
		auto fadein = FadeIn::create(0.2f);
		nowEquipment->runAction(fadeout);
		if (nowEquipment == equipmentOne)
		{
			nowEquipment = equipmentTwo;
		}
		else
		{
			nowEquipment = equipmentOne;
		}
		nowEquipment->runAction(fadein);
	}
	return true;
}
bool hero::getWeapon(EventKeyboard::KeyCode keycode, Event* event)
{
	return true;
}
bool hero::take_buff(Buff* buff)
{
	return true;
}
bool hero::clear_buff()
{
	return true;
}
void hero::takeDamage(int num)
{
	this->_lifeNum -= num;
}
void hero::setDeath(bool isDied)
{
	_isDied = isDied;
}
bool hero::getDeath()
{
	return _isDied;
}
int hero::getLifeNum()
{
	return this->_lifeNum;
}
bool hero::setLifeNum(int num)
{
	this->_lifeNum = num;
	return true;
}
void hero::setLeftOrRight(bool orient)
{
	this->_leftOrRight = orient;
}
bool hero::getLeftOrRight()
{
	return _leftOrRight;
}
void hero::setIsUsingWeapon(bool isUsingWeapon)
{
	this->_isUsingWeapon = isUsingWeapon;
}
bool hero::getIsUsingWeapon()
{
	return this->_isUsingWeapon;
}
void hero::setDefence(int defence)
{
	this->_defence = defence;
}
int hero::getDefence()
{
	return _defence;
}