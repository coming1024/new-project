

#ifndef __HOMESCENE_H__//主界面
#define __HOMESCENE_H__

#include "ParentScene.h"
#include "cocos2d.h"

class HomeScene : public ParentScene
{
public:
    //游戏界面大小声明
    cocos2d::Size VisibleSize;

    //横纵轴初始值大小声明
    cocos2d::Vec2 Origin;


public:
    HomeScene();
    ~HomeScene();

    //创建场景
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeScene);

    //退出游戏
    void menuCloseCallback(cocos2d::Ref* pSender);

    //切换到HerosHome场景
    void GoToHerosHome(cocos2d::Ref* pSender);

    //切换到SettingScene
    void GoToSettingLayer(cocos2d::Ref* pSender);

    //切换到infoscene
    void GoToInfo(cocos2d::Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
