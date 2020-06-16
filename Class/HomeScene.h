

#ifndef __HOMESCENE_H__//������
#define __HOMESCENE_H__

#include "ParentScene.h"
#include "cocos2d.h"

class HomeScene : public ParentScene
{
public:
    //��Ϸ�����С����
    cocos2d::Size VisibleSize;

    //�������ʼֵ��С����
    cocos2d::Vec2 Origin;


public:
    HomeScene();
    ~HomeScene();

    //��������
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HomeScene);

    //�˳���Ϸ
    void menuCloseCallback(cocos2d::Ref* pSender);

    //�л���HerosHome����
    void GoToHerosHome(cocos2d::Ref* pSender);

    //�л���SettingScene
    void GoToSettingLayer(cocos2d::Ref* pSender);

    //�л���infoscene
    void GoToInfo(cocos2d::Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
