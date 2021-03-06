#if true



/*

	Program LevelEnv ¹Ø¿¨³¡¾°

	File version alpha 0.3

	TC202006192221

	ERR=ETH (P.Q.)

*/



#pragma once

#include "cocos2d.h"

#include <ctime>

#include "MapGenMerge.h"

#include "MapGenCocos.h"

#include"qishi.h"

#include"Chest.h"

#include"Prop.h"

#include "Monster.h"



class LevelEnv : public cocos2d::Scene

{

private:

	cocos2d::Size VisibleSize;

	cocos2d::Vec2 Origin;

	const char* Audio;

	const char* AudioSwitch;

	qishi* hero_qishi;

	Monster* monster1;

	Monster* monster2;

	void initDate();

	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	bool onTouchBegan(Touch* pTouch, Event* pEvent);

	void onTouchMoved(Touch* pTouch, Event* pEvent);

	void onTouchEnded(Touch* pTouch, Event* pEvent);

	void upDataHeroNature(float t);

	void upDataAddEnergy(float t);

	void monsterAndPlayerCollision(CCArray* monsterArray1);

	void monsterAndBulletCollision(CCArray* monsterArray1, CCArray* bulletArray2);

	void monsterAndWeaponCollision(CCArray* monsterArray1);

	bool isCollision(CCRect rect1, CCRect rect2);

	void playerAndWeaponCollision(CCArray* weaponArray1);

	void playerAndPropCollison(CCArray* propArray1);

	void playerAndChestCollison(CCArray* chestArray1);

public:

	LevelEnv();

	~LevelEnv();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelEnv);

	CCArray* weaponArray;

	CCArray* propArray;

	CCArray* chestArray;

	CCArray* monsterArray;///

	SpriteFrameCache* equipmentCache;

	SpriteFrameCache* bulletCache;

	SpriteFrameCache* propCache;

	SpriteFrameCache* chestCache;

	SpriteFrameCache* heroCache;

};



/*

	Program LevelEnv ¹Ø¿¨³¡¾°

	End

*/



#endif
