#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"

#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"

class HerosHome :public cocos2d::Scene
{
public:
    //游戏界面大小声明
    cocos2d::Size VisibleSize;

    //横纵轴初始值大小声明
    cocos2d::Vec2 Origin;

public:


    HerosHome();
    ~HerosHome();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HerosHome);

    qishi* hero_qishi;
    Sprite* InfoBoard;


    void BackToHomeScene(cocos2d::Ref* pSender);
    void GoToGameScene(cocos2d::Ref* pSender);
    void InfoBTN(cocos2d::Ref* pSender);

    void upDataHeroNature(float t);
    void upDataAddEnergy(float t);

    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchMoved(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);
};



#endif 