#pragma once
#ifndef __hero_h__
#define __hero_h__
#include<iostream>
#include"cocos2d.h"
#include<vector>
#include"equipment.h"
USING_NS_CC;
class hero :public cocos2d::Sprite
{
	CC_SYNTHESIZE(bool, _alreadyDead, AlreadyDead);
public:
	static hero* create(SpriteFrameCache* cache, char* s);
	virtual bool heroMove(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool heroStopMove(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool swithWeapon(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool getWeapon(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool commonAttack(Touch* pTouch, Event* pEvent);
	virtual bool stopcommonAttack(Touch* pTouch, Event* pEvent);
	virtual int getCurrentLifeNum();
	virtual void setCurrentLifeNum(int);
	virtual void addCurrentLifeNum(int);
	virtual int getTotalLifeNum();
	virtual void setTotalLifeNum(int);
	virtual void addTotalLifeNum(int);

	virtual void setDeath(bool);
	virtual bool getDeath();

	virtual void setLeftOrRight(bool);
	virtual bool getLeftOrRight();

	virtual void setIsUsingWeapon(bool);
	virtual bool getIsUsingWeapon();

	virtual void setDefence(int);
	virtual int getDefence();
	virtual void addDefence(int);

	virtual void setATK(int);
	virtual int getATK();

	virtual void takeDamage(int);

	virtual ProgressTimer* getBloodProgress();


	equipment* equipmentOne;
	equipment* equipmentTwo;
	equipment* nowEquipment;
	bool _isMoveing;
	bool _isDied;
protected:
	int _CurrentlifeNum;
	int _totalLifeNum;
	int _commonATK;//¹¥»÷Á¦
	int _defence;
	int type;
	bool _isUsingWeapon;
	bool _leftOrRight;
	Sprite* spriteBar;
	Sprite* spriteBlood;
	ProgressTimer* bloodProgress;

};
#endif
