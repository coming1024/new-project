

#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"
#include "ParentScene.h"
//英雄创建
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class HerosHome :public ParentScene
{//英雄选择界面

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
};


#endif 


