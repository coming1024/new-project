

#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"
//英雄创建
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class HerosHome :public cocos2d::Scene
{
public:
     //游戏界面大小声明
    cocos2d::Size VisibleSize;

    //横纵轴初始值大小声明
    cocos2d::Vec2 Origin;

    //背景音乐
    const char* BGM;

    //背景音乐音量
    float BGMvolume;

    //背景音乐是否播放
    bool BGMisPlay;

public:
    HerosHome();
    ~HerosHome();

    //场景初始化
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HerosHome);
    
    //英雄创建
    static qishi* hero_qishi;


    //返回主界面
    void BackToHomeScene(cocos2d::Ref* pSender);

    //进入游戏界面
    void GoToGameScene(cocos2d::Ref* pSender);

    //返回背景音乐音量大小
    float GetBGMvolume();

    //改变背景音乐音量大小
    void SetBGMvolume(float NewVolume);

    //返回背景音乐是否播放
    bool GetBGMisPlay();

    //改变背景音乐播放状态
    void SetBGMisPlay(bool isPlay);
};


#endif 


