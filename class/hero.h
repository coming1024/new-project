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
	virtual void reduceCurrentLifeNum(int);

	virtual void setDeath(bool);
	virtual bool getDeath();

	virtual void setLeftOrRight(bool);
	virtual bool getLeftOrRight();

	virtual void setIsUsingWeapon(bool);
	virtual bool getIsUsingWeapon();

	virtual void setCurrentDefence(int);
	virtual int getCurrentDefence();
	virtual void addCurrentDefence(int);
	virtual int getTotalDefence();
	virtual void setTotalDefence(int);
	virtual void reduceCurrentDefence(int);


	virtual void setATK(int);
	virtual int getATK();

	virtual int getCurrentEnergy();
	virtual void setCurrentEnergy(int);
	virtual void addCurrentEnergy(int);
	virtual int getTotalEnergy();
	virtual void setTotalEnergy(int);
	virtual void reduceCurrentEnergy(int);

	virtual void takeDamage(int);

	virtual ProgressTimer* getBloodProgress();
	virtual ProgressTimer* getEnergyProgress();
	virtual ProgressTimer* getDefenceProgress();

	equipment* equipmentOne;
	equipment* equipmentTwo;
	equipment* nowEquipment;
	bool _isMoveing;
	bool _isDied;
protected:
	int _CurrentlifeNum;
	int _totalLifeNum;
	int _commonATK;//¹¥»÷Á¦
	int _currentDefence;
	int _totalDefence;
	int _currentEnergy;
	int _totalEnergy;
	int type;
	bool _isUsingWeapon;
	bool _leftOrRight;
	Sprite* spriteBar1;
	Sprite* spriteBar2;
	Sprite* spriteBar3;
	Sprite* spriteBlood;
	Sprite* spriteEnergy;
	Sprite* spriteDefence;
	ProgressTimer* bloodProgress;
	ProgressTimer* energyProgress;
	ProgressTimer* defenceProgress;

};
#endif
