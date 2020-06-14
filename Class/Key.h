#ifndef __KEY_H__
#define __KEY_H__

#include "cocos2d.h"
#include"hero.h"
#include"qishi.h"
USING_NS_CC;

class Key : public cocos2d::Layer
{
public:
    //static cocos2d::Layer* createLayer();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Key);
    virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    virtual bool isCollision(CCRect rect1,CCRect rect2);
    virtual void monsterAndPlayerCollision(CCArray* monsterArray);
    virtual void monsterAndBulletCollision(CCArray* monsterArray, CCArray* bulletArray);
    virtual void monsterAndWeaponCollision(CCArray* monsterArray);
    virtual void playerAndWeaponCollision(CCArray* weaponArray);
    virtual void upDataMAPC(float t);
    virtual void upDataMABC(float t);
    virtual void upDataMAWC(float t);
    virtual void upDataDeath(float t);
    qishi* hero_qishi;
    void addMonster(float t);
    CCArray* Monster;
    void initDate();
    SpriteFrameCache* equipmentCache;
    SpriteFrameCache* bulletCache;
    CCArray* weaponArray;

};

#endif // __HELLOWORLD_SCENE_H__
