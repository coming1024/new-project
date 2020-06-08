

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"



class HelloWorld : public cocos2d::Scene
{//游戏开始界面
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void stopMusic(cocos2d::Ref* pSender);
    void startGame(cocos2d::Ref* pSender);
    void Set(cocos2d::Ref* pSender);
    void gotoInfo(cocos2d::Ref* pSender);
    // implement the "static create()" method manually


};
/*
class HelloWorldLayers :public LayerMultiplex
{
public:
    int curLayerPos;
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(HelloWorldLayers);
   
};

class MainLayer :public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(MainLayer);

private:
    void gotoInfoLayer(cocos2d::Ref* pSender);
    void gotoSettingLayer(cocos2d::Ref* pSender);
};

class InfoLayer :public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(InfoLayer);
private:
    void backtoMainLayer(cocos2d::Ref* pSender);
};


class SettingLayer :public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(SettingLayer);
private:
    void backtoMainLayer(cocos2d::Ref* pSender);
};
*/
#endif // __HELLOWORLD_SCENE_H__
