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
void hero::takeDamage(int num)
{
	this->_CurrentlifeNum -= num;
}
void hero::setDeath(bool isDied)
{
	_isDied = isDied;
}
bool hero::getDeath()
{
	return _isDied;
}
int hero::getCurrentLifeNum()
{
	return this->_CurrentlifeNum;
}
void hero::setCurrentLifeNum(int num)
{
	this->_CurrentlifeNum = num;
}
void hero::addCurrentLifeNum(int num)
{
	this->_CurrentlifeNum += num;
}
int hero::getTotalLifeNum()
{
	return this->_totalLifeNum;
}
void hero::setTotalLifeNum(int num)
{
	this->_totalLifeNum = num;
}
void hero::addTotalLifeNum(int num)
{
	this->_totalLifeNum += num;
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
void hero::addDefence(int num)
{
	this->_defence += num;
}
void hero::setATK(int commonATK)
{
	this->_commonATK = commonATK;
}
int hero::getATK()
{
	return this->_commonATK;
}
ProgressTimer* hero::getBloodProgress()
{
	return this->bloodProgress;
}