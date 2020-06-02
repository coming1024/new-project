#pragma once
#ifndef __hero_h__
#define __hero_h__
#include<iostream>
#include"cocos2d.h"
#include<vector>
#include"buff.h"
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
	virtual bool commonAttack(Touch* pTouch, Event* pEvent);
	virtual bool stopcommonAttack(Touch* pTouch, Event* pEvent);
	virtual bool take_buff(Buff* buff);
	virtual bool clear_buff();
	virtual void die();
	virtual void take_damage();
	virtual void die_animation();
	equipment* equipmentOne;
	equipment* equipmentTwo;
	equipment* nowEquipment;
	bool _isMoveing;
	std::vector<cocos2d::Sprite*> _pt_bullets;
	unsigned int numBullet;
protected:
	int _life_num;
	int _commonATK;//¹¥»÷Á¦
	int _defence;
	Vector<Buff*> _allbuffs;
	int type;
	bool _isAttack;

};
#endif
