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
	if (this->getCurrentDefence() > 0)
	{
		this->reduceCurrentDefence(1);
	}
	else
	{
		this->reduceCurrentLifeNum(1);
	}
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
	if ((this->_CurrentlifeNum += num) > this->_totalLifeNum)
	{
		this->_CurrentlifeNum = this->_totalLifeNum;
	}
	else
	{
		this->_CurrentlifeNum += num;
	}
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
void hero::reduceCurrentLifeNum(int num)
{
	this->_CurrentlifeNum -= num;
}

int hero::getCurrentEnergy()
{
	return this->_currentEnergy;
}
void hero::setCurrentEnergy(int num)
{
	this->_currentEnergy = num;
}
void hero::addCurrentEnergy(int num)
{
	if ((this->_currentEnergy + num) > this->_totalEnergy)
	{
		this->_currentEnergy = this->_totalEnergy;
	}
	else
	{
		this->_currentEnergy += num;
	}
}
int hero::getTotalEnergy()
{
	return this->_totalEnergy;
}
void hero::setTotalEnergy(int num)
{
	this->_totalEnergy = num;
}
void hero::reduceCurrentEnergy(int num)
{
	this->_currentEnergy -= num;
}

int hero::getCurrentDefence()
{
	return this->_currentDefence;
}
void hero::setCurrentDefence(int num)
{
	this->_currentDefence = num;
}
void hero::addCurrentDefence(int num)
{
	if ((this->_currentDefence += num) > this->_totalDefence)
	{
		this->_currentDefence = this->_totalDefence;
	}
	else
	{
		this->_currentDefence += num;
	}
}
int hero::getTotalDefence()
{
	return this->_totalDefence;
}
void hero::setTotalDefence(int num)
{
	this->_totalDefence = num;
}
void hero::reduceCurrentDefence(int num)
{
	this->_currentDefence -= num;
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
ProgressTimer* hero::getEnergyProgress()
{
	return this->energyProgress;
}
ProgressTimer* hero::getDefenceProgress()
{
	return this->defenceProgress;
}